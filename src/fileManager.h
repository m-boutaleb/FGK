#ifndef ASD20192020TPG6_TREE_H
#define ASD20192020TPG6_TREE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decoding.h"
#include "bufferManager.h"
#define MAXCHARFILE 100

int readData(unsigned char *byteDaLeggere);
void initializeFile(const char *CD,const char* inFileName, const char* outFileName);
void writeData(const unsigned char byte);
int isEOF();
long int getFileSizeWithoutLastByte();
long int ftellInputFile();
long int getInputFileSize();
int checkEndOfFile();

#endif //ASD20192020TPG6_TREE_H
