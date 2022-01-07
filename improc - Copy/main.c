#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include "bitmap.h"
#include "improc.h"

byte** load_bitmap(const char* filepath, BITMAPINFO **BitmapInfo) {
    BITMAPFILEHEADER header;
    byte* bitmapBytes = LoadDIBitmap(filepath, BitmapInfo, &header);

    if (!bitmapBytes) {
        // Error when reading the input file.
        exit(-1);
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

        /* Przepisz wartosci pikseli wiersza obrazu. */
        for ( j = 0; j < w; j++) {
            *writer++ = image[h - i - 1][j];
        }

        /* Ustaw bajty wyrownania. */
        for ( j = 0; j < padding; j++) {
            *writer++ = 0;
        }
    }

    int status = SaveDIBitmap(filepath, BitmapInfo, bitmapBytes);
    free(bitmapBytes);

    return status;
}
#ifndef WIN32
const uint16_t BF_TYPE = 0x4D42;

/*
 * Functions for reading and writing 16- and 32-bit little-endian integers.
 */

static uint8_t read_byte(FILE* fp);

static uint16_t read_word(FILE* fp);

static uint32_t read_dword(FILE* fp);

static int32_t read_long(FILE* fp);

static int write_byte(FILE* fp, uint8_t w);

static int write_word(FILE* fp, uint16_t w);

static int write_dword(FILE* fp, uint32_t dw);

static int write_long(FILE* fp, int32_t l);

#endif

int write_file_header(FILE* fp, uint32_t infosize, uint32_t bitsize) {
    /* Size of file */
    uint32_t size = (uint32_t) (sizeof(BITMAPFILEHEADER) + infosize + bitsize);

    /* Write the file header, bitmap information, and bitmap pixel data... */
#ifdef WIN32
    BITMAPFILEHEADER header;       /* File header */
    header.bfType = "MB";
    header.bfSize = size;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = (uint32_t) (sizeof(BITMAPFILEHEADER) + infosize);
    return (fwrite(&header, 1, sizeof(BITMAPFILEHEADER), fp) < sizeof(BITMAPFILEHEADER)) ? EXIT_FAILURE : EXIT_SUCCESS;
#else
    int result = 0;
    result += write_word(fp, BF_TYPE);        /* bfType */
    result += write_dword(fp, size);          /* bfSize */
    result += write_word(fp, 0);              /* bfReserved1 */
    result += write_word(fp, 0);              /* bfReserved2 */
    result += write_dword(fp, (18 + infosize)); /* bfOffBits */
    return (result != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
#endif
}

int write_bmp_header(FILE* fp, BITMAPINFO* info, uint32_t infosize) {
#ifdef WIN32
    return (fwrite(info, 1, infosize, fp) < infosize) ? EXIT_FAILURE : EXIT_SUCCESS;
#else
    int result = 0;

    result += write_dword(fp, info->bmiHeader.biSize);
    result += write_long(fp, info->bmiHeader.biWidth);
    result += write_long(fp, info->bmiHeader.biHeight);
    result += write_word(fp, info->bmiHeader.biPlanes);
    result += write_word(fp, info->bmiHeader.biBitCount);
    result += write_dword(fp, info->bmiHeader.biCompression);
    result += write_dword(fp, info->bmiHeader.biSizeImage);
    result += write_long(fp, info->bmiHeader.biXPelsPerMeter);
    result += write_long(fp, info->bmiHeader.biYPelsPerMeter);
    result += write_dword(fp, info->bmiHeader.biClrUsed);
    result += write_dword(fp, info->bmiHeader.biClrImportant);

    result += write_byte(fp, 255U);
    result += write_byte(fp, 255U);
    result += write_byte(fp, 255U);
    result += write_byte(fp, 0U);

    if (result != 0) {
        return EXIT_FAILURE;
    }

    if (infosize > 40) {
        if (fwrite(info->bmiColors, infosize - 40, 1, fp) < 1) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
#endif
}

int
SaveDIBitmap(const char* filename, BITMAPINFO* info, byte* bits) {
    FILE* fp;           // Open file pointer
    uint32_t infosize;  // Size of bitmap info
    uint32_t bitsize;   // Size of bitmap pixels

    /* Try opening the file; use "wb" mode to write this *binary* file. */
    if ((fp = fopen(filename, "wb")) == NULL)
        return EXIT_FAILURE;

    /* Figure out the bitmap size */
    if (info->bmiHeader.biSizeImage == 0) {
        bitsize = (uint32_t) ((info->bmiHeader.biWidth * info->bmiHeader.biBitCount + 7) / 8 * abs(info->bmiHeader.biHeight));
    } else {
        bitsize = info->bmiHeader.biSizeImage;
    }

    /* Figure out the header size */
    infosize = sizeof(BITMAPINFOHEADER);

    bool should_break = false;
    if (info->bmiHeader.biCompression == BI_BITFIELDS) {
        infosize += 12; /* Add 3 RGB doubleword masks */
        if (info->bmiHeader.biClrUsed == 0) {
            should_break = true;
        }
    } else if (info->bmiHeader.biCompression == BI_BITFIELDS) {
        if (info->bmiHeader.biBitCount > 8 &&
            info->bmiHeader.biClrUsed == 0) {
            should_break = true;
        }
    }

    if (!should_break) {
        if (info->bmiHeader.biClrUsed == 0)
            infosize += (1U << info->bmiHeader.biBitCount) * 4;
        else
            infosize += info->bmiHeader.biClrUsed * 4;
    }

    if (write_file_header(fp, infosize, bitsize) == EXIT_FAILURE) {
        /* Couldn't write the file header - return... */
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (write_bmp_header(fp, info, infosize) == EXIT_FAILURE) {
        /* Couldn't write the bitmap header - return... */
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fwrite(bits, 1, bitsize, fp) < bitsize) {
        /* Couldn't write the bitmap - return... */
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

byte* LoadDIBitmap(const char* filename, BITMAPINFO** info, BITMAPFILEHEADER* header)
{
    FILE* fp;          /* Open file pointer */
    byte* bits;        /* Bitmap pixel bits */
    uint32_t bitsize;      /* Size of bitmap */
    uint32_t infosize;     /* Size of header information */

    /* Try opening the file; use "rb" mode to read this *binary* file. */
    if ((fp = fopen(filename, "rb")) == NULL){
    	return (NULL);
	}
    /* Read the file header and any following bitmap information... */
#ifdef WIN32
    if (fread(header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
        /* Couldn't read the file header - return NULL... */
        fclose(fp);
        return (NULL);
    }
#else
    header->bfType = read_word(fp);
    header->bfSize = read_dword(fp);
    header->bfReserved1 = read_word(fp);
    header->bfReserved2 = read_word(fp);
    header->bfOffBits = read_dword(fp);
#endif
	
    /* Check for BM reversed... */
#ifdef WIN32
    if (header->bfType != "MB")
#else
        if (header->bfType != BF_TYPE)
#endif
//    {
        /* Not a bitmap file - return NULL... */
//        fclose(fp);
//        return (NULL);
//    }

#ifdef WIN32

    infosize = (uint32_t) (header->bfOffBits - sizeof(BITMAPFILEHEADER));
    if ((*info = (BITMAPINFO*) malloc(infosize)) == NULL)
#else
        infosize = header->bfOffBits - 18;
        if ((*info = (BITMAPINFO*) malloc(sizeof(BITMAPINFO))) == NULL)
#endif
    {
        /* Couldn't allocate memory for bitmap info - return NULL... */
        fclose(fp);
        return (NULL);
    }

#ifdef WIN32
    bool was_error_when_reading_bitmap_header = (fread(*info, 1, infosize, fp) < infosize);
#else
    (*info)->bmiHeader.biSize = read_dword(fp);
    (*info)->bmiHeader.biWidth = read_long(fp);
    (*info)->bmiHeader.biHeight = read_long(fp);
    (*info)->bmiHeader.biPlanes = (uint8_t) read_word(fp);
    (*info)->bmiHeader.biBitCount = (uint8_t) read_word(fp);
    (*info)->bmiHeader.biCompression = (uint8_t) read_dword(fp);
    (*info)->bmiHeader.biSizeImage = read_dword(fp);
    (*info)->bmiHeader.biXPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biYPelsPerMeter = read_long(fp);
    (*info)->bmiHeader.biClrUsed = read_dword(fp);
    (*info)->bmiHeader.biClrImportant = read_dword(fp);

    bool was_error_when_reading_bitmap_header = false;
    if (infosize > 40) {
        was_error_when_reading_bitmap_header = (fread((*info)->bmiColors, infosize - 40, 1, fp) < 1);
    }
#endif
    if (was_error_when_reading_bitmap_header) {
        /* Couldn't read the bitmap header - return NULL... */
        free(*info);
        fclose(fp);
        return (NULL);
    }

    /* Now that we have all the header info read in, allocate memory for *
     * the bitmap and read *it* in...                                    */
    if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0) {
        bitsize = (uint32_t) (((*info)->bmiHeader.biWidth *
                               (*info)->bmiHeader.biBitCount + 7) / 8 *
                              abs((*info)->bmiHeader.biHeight));
    }

    if ((bits = (byte*) malloc(bitsize)) == NULL) {
        /* Couldn't allocate memory - return NULL! */
        free(*info);
        fclose(fp);
        return (NULL);
    }

#ifndef WIN32
    fseek(fp, 4, SEEK_CUR);  // skip bytes: 255 255 255 0
#endif

    if (fread(bits, 1, bitsize, fp) < bitsize) {
        /* Couldn't read bitmap - free memory and return NULL! */
        free(*info);
        free(bits);
        fclose(fp);
        return (NULL);
    }

#ifdef WIN32
//    // Manually set the color map.
//    (*info)->bmiHeader.biClrUsed = 256;
//    (*info)->bmiHeader.biClrImportant = 256;
//    for (size_t c = 0; c < 256; ++c) {
//        RGBQUAD color = {c, c, c, 0};
//        (*info)->bmiColors[c] = color;
//    }
#else
    //    /* Swap red and blue */
    //    length = ((*info)->bmiHeader.biWidth * 3 + 3) & ~3;
    //    for (y = 0; y < (*info)->bmiHeader.biHeight; y ++)
    //        for (ptr = bits + y * length, x = (*info)->bmiHeader.biWidth;
    //             x > 0;
    //             x --, ptr += 3)
    //        {
    //            temp   = ptr[0];
    //            ptr[0] = ptr[2];
    //            ptr[2] = temp;
    //        }
#endif

    fclose(fp);
    return (bits);
}

#ifndef WIN32

static uint8_t read_byte(FILE* fp) {
    return (uint8_t) getc(fp);
}

static uint16_t read_word(FILE* fp) {
    uint8_t b0 = read_byte(fp);
    uint8_t b1 = read_byte(fp);

    return (uint16_t) ((uint16_t) (b1 << 8U) | b0);
}

static uint32_t read_dword(FILE* fp) {
    uint8_t b0 = read_byte(fp);
    uint8_t b1 = read_byte(fp);
    uint8_t b2 = read_byte(fp);
    uint8_t b3 = read_byte(fp);

    return (uint32_t) (
            (uint32_t) (b3 << 24U)
            | (uint32_t) (b2 << 16U)
            | (uint32_t) (b1 << 8U)
            | b0
    );
}

static int32_t read_long(FILE* fp) {
    uint8_t b0 = read_byte(fp);
    uint8_t b1 = read_byte(fp);
    uint8_t b2 = read_byte(fp);
    uint8_t b3 = read_byte(fp);

    return (int32_t) (
            (uint32_t) (b3 << 24U)
            | (uint32_t) (b2 << 16U)
            | (uint32_t) (b1 << 8U)
            | b0
    );
}

/* O - 0 on success, -1 on error */
static int write_byte(FILE* fp, uint8_t w) {
    return (putc(w, fp) == EOF);
}

static int write_word(FILE* fp, uint16_t w) {
    write_byte(fp, (uint8_t) w);
    return write_byte(fp, (uint8_t) (w >> 8U));
}

static int write_dword(FILE* fp, uint32_t dw) {
    write_byte(fp, (uint8_t) dw);
    write_byte(fp, (uint8_t) (dw >> 8U));
    write_byte(fp, (uint8_t) (dw >> 16U));
    return write_byte(fp, (uint8_t) (dw >> 24U));
}

static int write_long(FILE* fp, int32_t l) {
    uint32_t ul = (uint32_t) l;
    write_byte(fp, (uint8_t) ul);
    write_byte(fp, (uint8_t) (ul >> 8U));
    write_byte(fp, (uint8_t) (ul >> 16U));
    return write_byte(fp, (uint8_t) (ul >> 24U));
}

#endif /* !WIN32 */
int inversePixels(char* input, char* output){
	BITMAPINFO* bitmap_info = NULL;
    byte** image_array = load_bitmap(input, &bitmap_info);
	
    int h = bitmap_info->bmiHeader.biHeight;
    int i, j;
    for(i = 0; i < h; i++){
    	for(j = 0; j < h; j++){
    		image_array[i][j] = 255 - image_array[i][j];
		}
	}
    save_bitmap(output, image_array, bitmap_info);

    if (image_array) {
    	int i;
        for (i = 0; i < h; i++) {
            free(image_array[i]);
        }

        free(image_array);
        image_array = NULL;
    }

    if (bitmap_info) {
        free(bitmap_info);
    }

    return EXIT_SUCCESS;
}
int maskedFilter(char* input, char* output, int n){
	//mask will be used
	BITMAPINFO* bitmap_info = NULL;
    byte** image_array = load_bitmap(input, &bitmap_info);
    int h = bitmap_info->bmiHeader.biHeight;
    int i, j, k, l;
    int k_ = (n-1)/2;
    for(i = 0; i < h; i++){
    	for(j = 0; j < h; j++){
    		int hold = 0;
    		int flag = 0;
    		for(k = -k_; k < k_; k++){
    			for(l = -k_; l < k_; l++){
    				if(k+i >= 0 && l+j >= 0 && k+i < h && l+j < h){
    					hold += image_array[i+k][j+l];
					}else{
						hold = 0;
						flag = 1;
						break;
					}
				}
				if(flag){
					break;
				}
			}
			image_array[i][j] = hold;
		}
	}
	save_bitmap(output, image_array, bitmap_info);

    if (image_array) {
    	int i;
        for (i = 0; i < h; i++) {
            free(image_array[i]);
        }

        free(image_array);
        image_array = NULL;
    }

    if (bitmap_info) {
        free(bitmap_info);
    }

    return EXIT_SUCCESS;
}
int averageFilter(char* input, char* output, int n){
	BITMAPINFO* bitmap_info = NULL;
    byte** image_array = load_bitmap(input, &bitmap_info);
    int h = bitmap_info->bmiHeader.biHeight;
    int i, j, k, l;
    int den = n*n;
    int k_ = (n-1)/2;
    for(i = 0; i < h; i++){
    	for(j = 0; j < h; j++){
    		int hold = 0;
    		for(k = -k_; k < k_; k++){
    			for(l = -k_; l < k_; l++){
    				if(k+i >= 0 && l+j >= 0 && k+i < h && l+j < h){
    					hold += image_array[i+k][j+l];
					}
				}
			}
			image_array[i][j] = hold/den;
		}
	}
	save_bitmap(output, image_array, bitmap_info);

    if (image_array) {
    	int i;
        for (i = 0; i < h; i++) {
            free(image_array[i]);
        }

        free(image_array);
        image_array = NULL;
    }

    if (bitmap_info) {
        free(bitmap_info);
    }

    return EXIT_SUCCESS;
}
int main(void) {
    // FIXME: Replace it with the absolute path to an existing image.
    const char* input_filepath = "C:/Users/Hp/Desktop/improc/imgs/lena_512.bmp";
    // FIXME: Replace it with the absolute path to an existing image.
    const char* output_filepath = "C:/Users/Hp/Desktop/improc/imgs/lena_512_out_masked.bmp";
	return maskedFilter(input_filepath, output_filepath, 71);
}
