#include "structs.h"

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char digits[10][7][7];

bmp_image readImage(char imageName[256]);
bmp_image copyImage(bmp_image image);
bmp_image initImage(bmp_image image);
void writeImage(bmp_image image);

void printFileHeader(bmp_image *image);
void printInfoHeader(bmp_image *image);

int match(point p, bmp_image *image, char digit[7][7]);
void eraseDigit(point p, bmp_image *image);
void copyDigit(point dest, point src, bmp_image *image);

point Point(int i, int j);
void printPoint(point P);

pixel Pixel(unsigned char B, unsigned char G, unsigned char R);
void printPixel(pixel P);
char pixelWhite(pixel P);
void setPixel(pixel *p, unsigned char B, unsigned char G, unsigned char R);

#endif // UTILS_H_INCLUDED
