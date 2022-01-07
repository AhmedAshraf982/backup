#include "improc.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

byte** load_bitmap(const char* filepath, BITMAPINFO **BitmapInfo) {
	try{
		BITMAPFILEHEADER header;
    	byte* bitmapBytes = LoadDIBitmap(filepath, BitmapInfo, &header);
		if (!bitmapBytes) {
        // Error when reading the input file.
        	 throw 1;
    	}
    	const size_t h = (size_t) (*BitmapInfo)->bmiHeader.biHeight;
	    const size_t w = (size_t) (*BitmapInfo)->bmiHeader.biWidth;
	    const size_t bits_per_pixel = (*BitmapInfo)->bmiHeader.biBitCount;
	
	    /* see: https://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage */
	    size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;
	
	    printf("Successfully loaded a %lux%lu image - %s.\n\n", h, w, filepath);

	    byte** image_array = (byte**) malloc(sizeof(byte*) * h);
	    size_t i;
	    for (i = 0; i < h; i++) {
	        image_array[i] = (byte*) malloc(sizeof(byte) * w);
	        memset(image_array[i], 0, w);
	    }
	
	    byte* reader = bitmapBytes;
	
	    // The order of the pixels in BMP file is as follows: from left to right, from bottom to top (first pixel is from
	    // lower left corner of the picture).
	    size_t j;
	    for (i = 0; i < h; ++i) {
	        /* Copy values of pixels in an image row. */
	        for (j = 0; j < w; ++j) {
	            image_array[h - i - 1][j] = *reader;
	            ++reader;
	        }
	
	        /* Skip padding bytes. */
	        reader += row_size - w;
	    }
	
	    free(bitmapBytes);
	
	    return image_array;
	}catch(int a){
		printf("Error when reading the input file!");
		exit(-1);
	}
}

int save_bitmap(const char* filepath, byte** image, BITMAPINFO* BitmapInfo) {

    const size_t h = (size_t) BitmapInfo->bmiHeader.biWidth;
    const size_t w = (size_t) BitmapInfo->bmiHeader.biHeight;
    const size_t bits_per_pixel = BitmapInfo->bmiHeader.biBitCount;
    const size_t row_size = (bits_per_pixel * w + 31) / 32 * 4;

    byte* bitmapBytes = (byte*) malloc(sizeof(byte) * BitmapInfo->bmiHeader.biSizeImage);
    byte* writer = bitmapBytes;
	
    const size_t padding = row_size - w;
	size_t i, j;
    for (i = 0; i < h; ++i) {
        for ( j = 0; j < w; j++) {
            *writer++ = image[h - i - 1][j];
        }
        for ( j = 0; j < padding; j++) {
            *writer++ = 0;
        }
    }

    int status = SaveDIBitmap(filepath, BitmapInfo, bitmapBytes);
    free(bitmapBytes);
    printf("Successfully saved a %lux%lu image - %s.\n\n", h, w, filepath);
    return status;
}
