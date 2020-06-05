#include "fileManager.h"

/**
 * Abbiamo generato il makefile che si occupa di creare e compilare tutti i file oggetto e di creare il file
 * FGK.exe. Per eseguire dunque l'algoritmo(dopo aver eseguito il makefile) basta digitare su linea di comando:
 * ./FGK.exe -c/-d <inputFile> <outputFile>
 * Altrimenti si può compilare il programma con la seguente linea di codice:
 * gcc -w -o FGK FGK.C fileManager.c tree.c encoding.c decoding.c bitManager.c
 * Per eseguire: ./FGK.exe -c(oppure -d per decomprimere) <inputFile> <outputFile>
 */
 int main(int argc, char *argv[]){
    if(argc!=4) {
        printf("Specifica un file(esistente) da comprimere/decomprimere e il suo file di output!");
        exit(1);
    }
    initializeFile(argv[1], argv[2], argv[3]);
    return 0;
}
