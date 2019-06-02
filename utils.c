#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char digits[10][7][7] =
{
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 1, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0}
	}
};

bmp_image readImage(char imageName[256])
{
    bmp_image image;
    FILE *imageFile;
    int i, padding;

    image = initImage(image);
    strcpy(image.name, imageName);

    // read fileheader and infoheader
	imageFile = fopen(image.name, "rb");
	fseek(imageFile, 0, SEEK_SET);
	fread(&image.header, 14, 1, imageFile);
	fread(&image.info, 40, 1, imageFile);
	padding = image.info.bmWidth%4;

	// allocate memory for the bitmaps
	image.bitmap = calloc(image.info.bmHeight, sizeof(pixel *));
	for (i = 0; i < image.info.bmHeight; i++) {
		image.bitmap[i] = calloc(image.info.bmWidth, sizeof(pixel) + 1);
	}

	// read bitmap flipped
	fseek(imageFile, image.header.bmOffset, SEEK_SET);
	for (i = image.info.bmHeight - 1; i >= 0; i--)
	{
        // read a row
		fread(image.bitmap[i], sizeof(pixel), image.info.bmWidth, imageFile);

		// skip padding
		fseek(imageFile, padding, SEEK_CUR);
	}
	fclose(imageFile);

	return image;
}

bmp_image initImage(bmp_image image)
{
    image.header.fileMarker1    = 'B';
    image.header.fileMarker2    = 'M';
    image.header.unused1        = 0;
    image.header.unused2        = 0;
    image.header.bmOffset       = 54;

    image.info.Size             = 40;
    image.info.planes           = 1;
    image.info.bitPix           = 24;
    image.info.bmCompression    = 0;
    image.info.xPixPerMeter     = 0;
    image.info.yPixPerMeter     = 0;
    image.info.colorsUsed       = 0;
    image.info.colorsImportant  = 0;

    image.bitmap = NULL;

    return image;
}

bmp_image copyImage(bmp_image image)
{
    int i, j;
    bmp_image copy;

    copy = initImage(copy);

    copy.header.fileSize    = image.header.fileSize;
    copy.header.bmOffset    = image.header.bmOffset;

    copy.info.Size          = image.info.Size;
    copy.info.bmWidth       = image.info.bmWidth;
    copy.info.bmHeight      = image.info.bmHeight;
    copy.info.bmSize        = image.info.bmSize;

    // allocate memory for the copy
    copy.bitmap = calloc(copy.info.bmHeight, sizeof(pixel *));
    for (i = 0; i < copy.info.bmHeight; i++)
    {
        copy.bitmap[i] = calloc(copy.info.bmWidth, sizeof(pixel) + 1);
    }

    // copy the bitmap
    for (i = 0; i < copy.info.bmHeight; i++)
    {
        for (j = 0; j < copy.info.bmWidth; j++)
        {
            copy.bitmap[i][j] = image.bitmap[i][j];
        }
    }

    return copy;
}

void writeImage(bmp_image image)
{
    int i, j, k, padding;
    FILE *outputFile;

    padding = image.info.bmWidth%4;
    outputFile = fopen(image.name, "wb");

    // write the header
    fwrite(&image.header.fileMarker1, sizeof(unsigned char), 1, outputFile);
    fwrite(&image.header.fileMarker2, sizeof(unsigned char), 1, outputFile);
    fwrite(&image.header.fileSize, sizeof(unsigned int), 1, outputFile);
    fwrite(&image.header.unused1, sizeof(unsigned short), 1, outputFile);
    fwrite(&image.header.unused2, sizeof(unsigned short), 1, outputFile);
    fwrite(&image.header.bmOffset, sizeof(unsigned int), 1, outputFile);

    // write the infoheader
    fwrite(&image.info.Size, sizeof(unsigned int), 1, outputFile);
    fwrite(&image.info.bmWidth, sizeof(signed int), 1, outputFile);
    fwrite(&image.info.bmHeight, sizeof(signed int), 1, outputFile);
    fwrite(&image.info.planes, sizeof(unsigned short), 1, outputFile);
    fwrite(&image.info.bitPix, sizeof(unsigned short), 1, outputFile);
    fwrite(&image.info.bmCompression, sizeof(unsigned int), 1, outputFile);
    fwrite(&image.info.bmSize, sizeof(unsigned int), 1, outputFile);
    fwrite(&image.info.xPixPerMeter, sizeof(int), 1, outputFile);
    fwrite(&image.info.yPixPerMeter, sizeof(int), 1, outputFile);
    fwrite(&image.info.colorsUsed, sizeof(unsigned int), 1, outputFile);
    fwrite(&image.info.colorsImportant, sizeof(unsigned int), 1, outputFile);

    // write bitmap flipped
    for (i = image.info.bmHeight - 1; i >= 0; i--)
    {
        // write a row
        for (j = 0; j < image.info.bmWidth; j++)
        {
            fwrite(&image.bitmap[i][j].B, sizeof(unsigned char), 1, outputFile);
            fwrite(&image.bitmap[i][j].G, sizeof(unsigned char), 1, outputFile);
            fwrite(&image.bitmap[i][j].R, sizeof(unsigned char), 1, outputFile);
        }

        // add padding
        for (k = 0; k < padding; k++) {
			fwrite("\0", sizeof(unsigned char), 1, outputFile);
		}
    }

    fclose(outputFile);
}

void printFileHeader(bmp_image *image)
{
	printf("%c%c", image->header.fileMarker1, image->header.fileMarker2);
	printf("%d\n", image->header.fileSize);
	printf("%d %d\n", image->header.unused1, image->header.unused2);
	printf("%d\n", image->header.bmOffset);
}

void printInfoHeader(bmp_image *image)
{
	printf("%d %dx%d\n", image->info.Size, image->info.bmWidth, image->info.bmHeight);
    printf("%d %d %d\n", image->info.planes, image->info.bitPix, image->info.bmCompression);
    printf("%d\n", image->info.bmSize);
	printf("%d %d %d %d\n", image->info.xPixPerMeter, image->info.yPixPerMeter, image->info.colorsUsed, image->info.colorsImportant);
}

int match(point p, bmp_image *image, char digit[7][7])
{
	int i, j, matchedPixels;

	matchedPixels = 0;

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
            // check for the image boundaries
			if (i + p.y - 1 >= 0 && i + p.y - 1 < image->info.bmHeight &&
				j + p.x - 1 >= 0 && j + p.x - 1 < image->info.bmWidth)
			{
                // check for the digit boundaries
                if ((i == 0 || i == 6 || j == 0 || j == 6) &&
                    !pixelWhite(image->bitmap[i + p.y - 1][j + p.x - 1]))
                {
                    return 0;
                }

                // check for matched pixel
				if (!pixelWhite(image->bitmap[i + p.y - 1][j + p.x - 1]) == digit[i][j])
				{
					matchedPixels++;
				}
			}
			else
			{
				matchedPixels++;
			}
		}
	}

    // full match
	if (matchedPixels == 49)
	{
		return 1;
	}
	// partial match
	else if (matchedPixels == 48)
	{
		return 2;
	}
	return 0;
}

void eraseDigit(point p, bmp_image *image)
{
    int i, j;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            setPixel(&(image->bitmap[i + p.y][j + p.x]), 255, 255, 255);
        }
    }
}

void copyDigit(point dest, point src, bmp_image *image)
{
    int i, j;

    // copy a digit from a point to another
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            setPixel(&(image->bitmap[i + dest.y][j + dest.x]),
                        image->bitmap[i + src.y][j + src.x].B,
                        image->bitmap[i + src.y][j + src.x].G,
                        image->bitmap[i + src.y][j + src.x].R);
        }
    }
}

point Point(int y, int x)
{
    point P;

    P.y = y;
    P.x = x;

    return P;
}

void printPoint(point P)
{
    printf("[%d %d]", P.y, P.x);
}

pixel Pixel(unsigned char B, unsigned char G, unsigned char R)
{
    pixel P;

    P.B = B;
    P.G = G;
    P.R = R;

    return P;
}

void printPixel(pixel P)
{
    printf("[%d %d %d]", P.B, P.G, P.R);
}

char pixelWhite(pixel P)
{
	return (P.B == 255 || P.G == 255 || P.R == 255);
}

void setPixel(pixel *p, unsigned char B, unsigned char G, unsigned char R)
{
	p->B = B;
	p->G = G;
	p->R = R;
}
