// CHALLENGE 11 (Image segmentation).
//
// In addition to the C standard library, there are many other support libraries
// out there that provide very different features. Among those are a lot that do
// image processing of some kind. Try to find a suitable such image-processing
// library that is written in or interfaced to C and that allows you to treat
// grayscale images as two-dimensional matrices of base type unsigned char. The
// goal of this challenge is to perform a segmentation of such an image: to
// group the pixels (the unsigned char elements of the matrix) into connected
// regions that are “similar” in some sense or another. Such a segmentation
// forms a partition of the set of pixels, much as we saw in challenge 4.
//
// Therefore, you should use a Union-Find structure to represent regions, one
// per pixel at the start. Can you implement a statistics function that computes
// a statistic for all regions? This should be another array (the third array in
// the game) that for each root holds the number of pixels and the sum of all
// values.
//
// Can you implement a merge criterion for regions? Test whether the
// mean values of two regions are not too far apart: say, no more than five gray
// values.
//
// Can you implement a line-by-line merge strategy that, for each pixel
// on a line of the image, tests whether its region should be merged to the left
// and/or to the top?
//
// Can you iterate line by line until there are no more
// changes: that is, such that the resulting regions/sets all test negatively
// with their respective neighboring regions?
//
// Now that you have a complete function for image segmentation, try it on
// images with assorted subjects and sizes, and also vary your merge criterion
// with different values for the the mean distance instead of five.

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offset;
} BitmapHeader;

typedef struct {
  unsigned int size;
  int width;
  int height;
  unsigned short planes;
  unsigned short bitsPerPixel;
  unsigned int compression;
  unsigned int imageSize;
  int xResolution;
  int yResolution;
  unsigned int colorsUsed;
  unsigned int colorsImportant;
} BitmapInfoHeader;

int main() {

  FILE *img = fopen("sample.bmp", "rb");
  FILE *out_img = fopen("sample_gray.bmp", "wb");

  BitmapHeader header;
  BitmapInfoHeader info_header;

  fread(&header, sizeof(header), 1, img);           // Read the header
  fread(&info_header, sizeof(info_header), 1, img); // Read the header

  int width = info_header.width;
  int height = info_header.height;
  int bytes_per_pixel = info_header.bitsPerPixel;

  printf("width: %d, height: %d, bytes per pixel: %d\n", width, height,
         bytes_per_pixel);

  unsigned char *img_data =
      (unsigned char *)malloc(width * height * bytes_per_pixel);

  fseek(img, header.offset, SEEK_SET); // Skip to the start of the image data
  fread(img_data, width * height * bytes_per_pixel, 1, img); // Read the image

  // Print the img_data
  for (int i = 0; i < width * height * bytes_per_pixel; i++) {
    printf("%d ", img_data[i]);
  }
}
