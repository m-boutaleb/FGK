#include "fileManager.h"
#include "encoding.h"

static void closeFiles();
static void encoding();
static void decoding();
static void printCompressionRatio();

static FILE *INFILE;
static FILE *OUTFILE;
static long int infileSize;
static long int outfileSize;
static long int inFileSizeWithoutLastByte;
static unsigned char bitsToReadAtTheEnd;

/**
 * @param inFileName stampa il nome dell'input file
 * @param outFileName stampa il nome dell'output file
 */
static void initializeFGK(const char *inFileName, const char *outFileName){
    printf("\n**********************FGK**********************\n\n");
    printf("Authors: Mohamed Boutaleb - Chiara Locatelli\n");
    printf("Input file name: %s\n",inFileName);
    printf("Output file name: %s\n",outFileName);
}

/**
 * Stampa a schermo la dimensione del file di input
 */
static void inputFileInfo(){
    fseek(INFILE,0, SEEK_END);
    infileSize=ftell(INFILE);
    printf("\nSize of input file: %li bytes\n", infileSize);
    rewind(INFILE);
}

/**
 * Stampa a schermo la dimensione del file di output
 */
static void outputFileInfo(){
    fseek(OUTFILE,0, SEEK_END);
    outfileSize=ftell(OUTFILE);
    printf("\n\nSize of output file: %li bytes\n", outfileSize);
}

/**
 * @inFileName nome del file di input
 * @outFileName nome del file di output
 * @CD CD sta per comprimi o decomprimi
 * Questa funzione richiama la stampa su schermo dei nomi dei file e
 * le loro dimensioni, inoltre richiama la funzione di encode() e decode()
**/
void initializeFile(const char *CD,const char* inFileName, const char* outFileName){
    initializeFGK(inFileName, outFileName);
    char percorso[MAXCHARFILE]="./";
    if((INFILE=fopen(strcat(percorso, inFileName),"rb+"))==NULL) {
        printf("\nSomething gone wrong with the input file. Make\nsure '%s' exists and is in the right directory!\n", inFileName);
        closeFiles();
        exit(1);
    }
    percorso[2]='\0';
    if((OUTFILE=fopen(strcat(percorso, outFileName), "wb+"))==NULL){
        printf("\nSomething gone wrong with the output file: %s!", outFileName);
        closeFiles();
        exit(1);
    }

    inputFileInfo();

    if(!strcmp(CD, "-c")|| !strcmp(CD, "-C"))
        encoding();
    else if(!strcmp(CD, "-d")|| !strcmp(CD, "-D"))
        decoding();
    else{
        printf("Non hai specificato se vuoi comprimere o decomprimere il file!");
        exit(1);
    }
    outputFileInfo();
    if(!strcmp(CD, "-C")|| !strcmp(CD, "-c"))
        printCompressionRatio();
    closeFiles();
}


/**
 * @param byteToWrite Prende in parametro il singolo byte e lo scrive nel
 * file di output binario
 */
void writeData(const unsigned char byteToWrite) {
    fwrite(&byteToWrite,sizeof(unsigned char), 1, OUTFILE);
}


/**
 * Chiude i file di input e output
 */
static void closeFiles(){
    printf("\n**********************FGK**********************\n");
    fclose(INFILE);
    fclose(OUTFILE);
}

/**
 * @param byteDaLeggere byte dove mettere il byte letto
 * @return se -1 allora il file è stato letto tutto
 */
int readData(unsigned char *byteDaLeggere){
    return fread(byteDaLeggere, sizeof(unsigned char), 1, INFILE);
}
/**
 * @param readHowManyBitsAtTheEnd legge e sa
 * @return la dimensione del file di input
 */
static void setFileSizeWithoutLastByteAndBitsToRead() {
    fseek(INFILE, -1, SEEK_END);
    inFileSizeWithoutLastByte= ftell(INFILE);
    readData(&bitsToReadAtTheEnd);
    rewind(INFILE);
}

long int ftellInputFile(){
    return ftell(INFILE);
}


/**
 * questo funzione fa un check per vedere se il numero di bit da leggere alla fine del penultimo byte è diverso da 8
 * se lo è allora controlla se la posizione corrente di lettura del file è uguale alla dimensione del file senza l'ultimo
 * byte e la dimensione del buffer ha superato il numero di bit da leggere alla fine
 * e infine controlla per sicurezza che non la posizione corrente del file non abbia superato la dimensione del file senza
 * l''ultimo byte oppure che siamo alla fine del file
 * @return
 */
int checkEndOfFile(){
    if (bitsToReadAtTheEnd != 8)
        if (ftellInputFile() == inFileSizeWithoutLastByte && bitsToReadAtTheEnd <= (8 - getBufferSize()))
            return 1;
    if (ftellInputFile() > inFileSizeWithoutLastByte || isEOF())
        return 1;
    return 0;
}


/**
 * @return se siamo alla fine del file ritorna vero altrimenti no
 */
int isEOF(){
    return feof(INFILE);
}


/**
 * Stampa le dimensioni dei file di input e output e chiama la funzione di decodifica di lettura blocco
 */
static void decoding() {
    setFileSizeWithoutLastByteAndBitsToRead();
    decode();
}


/**
 * Metodo che stampa a schermo la percentuale di file compressa
 */
void printCompressionRatio(){
    float ratio=(float)outfileSize/infileSize*100;
    printf("Compressing ratio: %.2f ",100.0-ratio);
    printf("%%\n");
}


/**
 * Richiama semplicemente la funzione codifica contenuta nel file encoding
 */
static void encoding(){
    encode();
}

/**
 * @return  le dimensioni del file di input
 */
long int getInputFileSize(){
    return infileSize;
}

/**
 * @return le dimensioni del file senza l'ultimo byte
 */
long int getFileSizeWithoutLastByte(){
    return inFileSizeWithoutLastByte;
}
