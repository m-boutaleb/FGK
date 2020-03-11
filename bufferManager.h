#ifndef ASD20192020TPG6_BUFFERMANAGER_H
#define ASD20192020TPG6_BUFFERMANAGER_H
#include "fileManager.h"
void fillBufferIfEmpty();
int getBufferSize();
void initializeBufferSize();
void addNewByteToBuffer(unsigned char byte);
char readByte();
void reverseCode(int *codePath, int i);
int readBit();
void writeRemainingBits();
void addPathToBuffer(int *code,int codeSize);
void increaseCompletionBar();
void initializeCompletionBar();
#endif //ASD20192020TPG6_BUFFERMANAGER_H
