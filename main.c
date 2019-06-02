//Sima Iustin,315 CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main()
{
    FILE *inputFile, *outputFile;
    bmp_image image, imageColored, imageEdit, imageBonus;
    char imageName[256], bonusImageName[256], name[256], *pch;
    char bonusName[256], task1Name[256], task2Name[256], task3Name[256];
    int i, j, k, B, G, R, digitsRemove[10] = {0};
    int captchaDigits[100], digitsFound, matchResult, ok;
    point p, captchaDigitsCoord[100], captchaDigitsCoordCopy[100];

	inputFile = fopen("input.txt", "r");
	fscanf(inputFile, "%s", imageName);
	fscanf(inputFile, "%d%d%d", &B, &G, &R);
	while (fscanf(inputFile, "%d", &i)) digitsRemove[i] = 1;
	fscanf(inputFile, "%s", bonusImageName);
	fclose(inputFile);

	pch = strchr(imageName, '.');
	memset(name, 0, 256);
	memset(task1Name, 0, 256);
	memset(task2Name, 0, 256);
	memset(task3Name, 0, 256);
	memset(bonusName, 0, 256);
	memcpy(name, imageName, pch - imageName);
	strcat(task1Name, name);
	strcat(task1Name, "_task1.bmp");
	strcat(task2Name, name);
	strcat(task2Name, "_task2.txt");
	strcat(task3Name, name);
	strcat(task3Name, "_task3.bmp");
	pch = strchr(bonusImageName, '.');
	memset(name, 0, 256);
	memcpy(name, bonusImageName, pch - bonusImageName);
	strcat(bonusName, name);
	strcat(bonusName, "_bonus.txt");

	image 			= initImage(image);
	imageColored 	= initImage(imageColored);
	imageEdit 		= initImage(imageEdit);
	imageBonus 		= initImage(imageBonus);

	image = readImage(imageName);

	imageColored = copyImage(image);
	strcpy(imageColored.name, task1Name);

	for (i = 0; i < imageColored.info.bmHeight; i++)
	{
		for (j = 0; j < imageColored.info.bmWidth; j++)
		{
			if (!pixelWhite(imageColored.bitmap[i][j]))
			{
				setPixel(&imageColored.bitmap[i][j], B, G, R);
			}
		}
	}

	writeImage(imageColored);

	digitsFound = 0;

	for (j = 0; j < image.info.bmWidth - 4; j++)
	{
		for (i = 0; i < image.info.bmHeight - 4; i++)
		{
            ok = 0;

			for (k = 9; k >= 0; k--)
			{
				p.x = j;
				p.y = i;

				if (match(p, &image, digits[k]) == 1)
				{
					captchaDigits[digitsFound] = k;
					captchaDigitsCoord[digitsFound] = p;
					ok = 1;
					break;
				}
			}

			if (ok == 1)
			{
                digitsFound++;
                break;
			}
		}
	}

	outputFile = fopen(task2Name, "w");
	for (i = 0; i < digitsFound; i++)
	{
		fprintf(outputFile, "%d", captchaDigits[i]);
	}
	fclose(outputFile);

	imageEdit = copyImage(image);
	strcpy(imageEdit.name, task3Name);

    memcpy(captchaDigitsCoordCopy, captchaDigitsCoord, sizeof(int) * 100);
    for (i = 0; i < digitsFound; i++)
    {
        if (digitsRemove[captchaDigits[i]] == 1)
        {
            eraseDigit(captchaDigitsCoord[i], &imageEdit);

            for (j = i + 1; j < digitsFound; j++)
            {
                captchaDigits[j - 1] = captchaDigits[j];
                captchaDigitsCoord[j - 1] = captchaDigitsCoord[j];
            }
            digitsFound--;
            i--;
        }
    }

    for (i = 0; i < digitsFound; i++)
    {
        if (memcmp(&captchaDigitsCoord[i], &captchaDigitsCoordCopy[i], sizeof(point)))
        {
            copyDigit(captchaDigitsCoordCopy[i], captchaDigitsCoord[i], &imageEdit);

            eraseDigit(captchaDigitsCoord[i], &imageEdit);
        }
    }

    writeImage(imageEdit);
    imageBonus = readImage(bonusImageName);
    digitsFound = 0;
    memset(captchaDigits, 0, sizeof(int) * 100);

	for (j = 0; j < imageBonus.info.bmWidth - 4; j++)
	{
		for (i = 0; i < imageBonus.info.bmHeight - 4; i++)
		{
            ok = 0;

			for (k = 9; k >= 0; k--)
			{
				p.x = j;
				p.y = i;
                matchResult = match(p, &imageBonus, digits[k]);

				if (matchResult == 1)
				{
					captchaDigits[digitsFound] = k;
					ok = 1;
					break;
				}
				else if (matchResult == 2)
				{
                    captchaDigits[digitsFound] = k;
                    ok = 1;
				}
			}

			if (ok == 1)
			{
                digitsFound++;
                break;
			}
		}
	}

	outputFile = fopen(bonusName, "w");
	for (i = 0; i < digitsFound; i++)
	{
		fprintf(outputFile, "%d", captchaDigits[i]);
	}
	fclose(outputFile);

	for (i = 0; i < image.info.bmHeight; i++)
	{
		free(image.bitmap[i]);
		free(imageColored.bitmap[i]);
		free(imageEdit.bitmap[i]);
	}
	free(image.bitmap);
	free(imageColored.bitmap);
	free(imageEdit.bitmap);

	for (i = 0; i < imageBonus.info.bmHeight; i++)
	{
        free(imageBonus.bitmap[i]);
	}
	free(imageBonus.bitmap);

    return 0;
}
