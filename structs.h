#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#pragma pack(1)

typedef struct
{
    unsigned int y;
    unsigned int x;
} point;

typedef struct
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
} pixel;

typedef struct
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   fileSize;    /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   bmOffset;    /* Offset to the start of image data */
} bmp_fileheader;

typedef struct
{
    unsigned int   Size; 		/* Size of the info header - 40 bytes */
    signed int     bmWidth; 	/* Width of the image */
    signed int     bmHeight; 	/* Height of the image */
    unsigned short planes;
    unsigned short bitPix;
    unsigned int   bmCompression;
    unsigned int   bmSize; 		/* Size of the image data */
    int            xPixPerMeter;
    int            yPixPerMeter;
    unsigned int   colorsUsed;
    unsigned int   colorsImportant;
} bmp_infoheader;

typedef struct
{
    char name[256];
    bmp_fileheader header;
    bmp_infoheader info;
    pixel **bitmap;
} bmp_image;

#pragma pack()

#endif // STRUCTS_H_INCLUDED

