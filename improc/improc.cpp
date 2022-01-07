#include<stdio.h>
#include<stdlib.h>
#include "bitmap.h"
#include "improc.hpp"

enum ImagePrintMode { CHARS, NUMS };  //the enumerator as required 
template<class T>
void string_to_string(Image<T>* image, ImagePrintMode print_mode){   //the function that prints the contects of the image in two formats
	int h = image->h;
	if(print_mode == CHARS){
		for(int x = 0; x < h; x++){
			for(int y = 0; y < h; y++){
				printf("%c", image->matrix->matrixdata->matrix[x][y]);
			}
			printf("\n");
		}
	}else if(print_mode == NUMS){
		for(int x = 0; x < h; x++){
			for(int y = 0; y < h; y++){
				printf("%d ", image->matrix->matrixdata->matrix[x][y]);
			}
			printf("\n");
		}
	}
}
Image<byte>* load_bitmap(const char* filepath, BITMAPINFO** bmp_info) {   //the function that returns the image object which is having the details of the image
	try{
		BITMAPFILEHEADER header;
    	byte* bitmapBytes = LoadDIBitmap(filepath, bmp_info, &header);
		if (!bitmapBytes) {
       		throw 1;
    	}
    	const size_t h = (size_t) (*bmp_info)->bmiHeader.biHeight;
	    const size_t w = (size_t) (*bmp_info)->bmiHeader.biWidth;
	    const size_t bits_per_pixel = (*bmp_info)->bmiHeader.biBitCount;
		Image<byte>* image = new Image<byte>(h, w, NULL, header, 0);
	    size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;
	
	    printf("Successfully loaded a %lux%lu image - %s.\n\n", h, w, filepath);
	    size_t i;
	    image->matrix->matrixdata->matrix = new byte*[h];
	    for (i = 0; i < h; i++) {
	        image->matrix->matrixdata->matrix[i] = new byte[w];
	    }
	    byte* reader = bitmapBytes;
	    size_t j;
	    for (i = 0; i < h; ++i) {
	        for (j = 0; j < w; ++j) {
	            image->matrix->matrixdata->matrix[h - i - 1][j] = *reader;
	            ++reader;
	        }
	        reader += row_size - w;
	    }
	    free(bitmapBytes);
	    return image;
	}catch(int exp){
		printf("Error when reading the input file!");
		exit(-1);
	}
}

template<class T>
int save_bitmap(const char* filepath, Image<T>* image) {   //function to save the given image

    const size_t h = (size_t) image->bmp_info->bmiHeader.biWidth;
    const size_t w = (size_t) image->bmp_info->bmiHeader.biHeight;
    const size_t bits_per_pixel = image->bmp_info->bmiHeader.biBitCount;
    const size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;

    byte* bitmapBytes = (byte*) malloc(sizeof(byte) * image->bmp_info->bmiHeader.biSizeImage);
    byte* writer = bitmapBytes;

    const size_t padding = row_size - w;
	size_t i, j;
    for (i = 0; i < h; ++i) {
        for ( j = 0; j < w; j++) {
            *writer++ = image->matrix->matrixdata->matrix[h - i - 1][j];
        }
        for ( j = 0; j < padding; j++) {
            *writer++ = 0;
        }
    }
	try{
		int status = SaveDIBitmap(filepath, image->bmp_info, bitmapBytes);
	    free(bitmapBytes);
	    printf("Successfully saved a %lux%lu image - %s.\n\n", h, w, filepath);
	    return status;
	}catch(int exp){
		printf("Error when saving the file!");
		exit(-1);
	}
}

Matrix<double> get_average_mask(double n){    // function that gives the average mask matrix
	double val = 1/(n*n);
	Matrix<double> Mask((int)n, (int)n, val);
	return Mask;
}

template<class T>
Image<T>* filter(Image<T>* image, Matrix<double>& mask){    //function that returns the filtered image after average masking as required
	int i, j, k, l;
	int h = image->h;
	int n = mask.r;
    int k_ = (n-1)/2;
    for(i = 0; i < h; i++){
    	for(j = 0; j < h; j++){
    		double hold = 0;
    		for(k = -k_; k < k_; k++){
    			int a = 0;
    			for(l = -k_; l < k_; l++){
    				int b = 0;
    				if(k+i >= 0 && l+j >= 0 && k+i < h && l+j < h){
    					hold += ((double)image->matrix->matrixdata->matrix[i+k][j+l] * mask.matrixdata->matrix[a][b]);
					}
					b++;
				}
				a++;
			}
			image->matrix->matrixdata->matrix[i][j] = (int)hold;
		}
	}
	return image;
}

template<class T>
Image<T>* transform(Image<T>* image, int func){   // function that returns the transformed image i.e. inverted pixels or masked
	if(func == 1){
		//inverse
		int h = image->h;
	    int i, j;
	    for(i = 0; i < h; i++){
	    	for(j = 0; j < h; j++){
	    		image->matrix->matrixdata->matrix[i][j] = 255 - image->matrix->matrixdata->matrix[i][j];
			}
		}
		return image;
	}else if(func == 2){
		//avg masking
		double n = 7;  //letting a value for n
		Matrix<double> mask = get_average_mask(n);
		return filter(image, mask);
	}
}

