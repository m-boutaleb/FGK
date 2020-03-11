#include "bufferManager.h"

static unsigned char BUFFER=0;
static int BUFFERSIZE=0;
float every;
int i;


void initializeBufferSize(){
    BUFFERSIZE=8;
}

/**
 * funzione che inizializza la barra di completamento per generare gli asterischi
 */
void initializeCompletionBar(){
    every=(float)getInputFileSize()/100000000000;
    i=0;
    printf("\nDecoding: ");
}

/**
 * ogni volta che la variabile i raggiunge la soglia di every allora viene stampato un asterisco
 */
void increaseCompletionBar(){
    if(i++>every) {
        printf("*");
        every=every+every;
    }
}

/**
 * riempe il buffer se questo risulta vuoto
 */
void fillBufferIfEmpty(){
    if (BUFFERSIZE == 0) {
        BUFFERSIZE = 8;
        readData(&BUFFER);
        increaseCompletionBar();
    }
}

/**
 * @param codePath l'array di 0 e 1 che devono essere invertiti
 * @param codeSize la lunghezza del percorso da invertire
 */
void reverseCode(int *codePath, int codeSize) {
    if (codePath != NULL) {
        int *start = codePath;
        int *end = codePath + (codeSize - 1);

        while (start < end) {
            int temp = *start;
            *start = *end;
            *end = temp;
            start++;
            end--;
        }
    }
}

/**
 * @param buffer ciò che bisogna scrivere nel file
 * @param bufferSize quanta capacità di bit possiede ancora il buffer
 * Scrive la quantita di bit che deve non essere letta alla fine
 */
void writeRemainingBits() {
    if (BUFFERSIZE < 8)
        writeData(BUFFER);

    BUFFER=(BUFFERSIZE==8)?8:8-BUFFERSIZE;
    writeData(BUFFER);
}

/**
 * @return il bit contenuto nel buffer
 */
static int readBitFromBuffer(){
    return (BUFFER >> BUFFERSIZE) & 1;
}

/**
 * @return il byte letto
 */
char readByte() {
    char result = 0;

    int j, bit;
    for (j = 0; j < 8; j++) {
        bit = readBit();
        bit = bit << (7-j);
        result |= bit;
    }

    return result;
}

/**
 * @return un bit alla volta però prima fa un check per vedere se il buffer è pieno oppure vuoto
 */
int readBit() {
    fillBufferIfEmpty();
    if(checkEndOfFile())
        return -1;
    BUFFERSIZE--;
    return readBitFromBuffer();
}

/**
 * @param byte da aggiungere al buffer
 * @return il buffer con gli shift necessari
 */
void addNewByteToBuffer(unsigned char byte) {
    unsigned char currBuffer = BUFFER;

    int bitsToWrite = BUFFERSIZE;
    int shifter = 8 - bitsToWrite;
    unsigned char tempByte = ((unsigned char) byte) >> shifter;
    currBuffer = currBuffer | tempByte;

    writeData(currBuffer);

    currBuffer = byte << bitsToWrite;

    BUFFER=(BUFFERSIZE == 8) ? 0 : currBuffer;
}

/**
 * @return il numero di bit contenuti nel buffer
 */
int getBufferSize(){
    return BUFFERSIZE;
}

/**
 * @param code percorso dell'albero
 * @param codeSize lunghezza del percorso
 * @param buffer
 * @param bufferSize
 * @return il buffer contenente tutti i bit rimasti del percorso
 */
void addPathToBuffer(int *code,int codeSize){
    unsigned char currBuffer = BUFFER;

    int i;
    for (i = 0; i < codeSize; i++) {
        unsigned char bit = ((unsigned char) code[i]) << (BUFFERSIZE - 1);
        currBuffer = currBuffer | bit;

        BUFFERSIZE--;

        if (BUFFERSIZE == 0) {
            writeData(currBuffer);
            currBuffer = 0;
            BUFFERSIZE = 8;
        }
    }
    BUFFER=currBuffer;
}
