#include "decoding.h"

/**
 * Si crea prima un array di Character di dimensione 256 dove a loro volta a ogni posizione p (che corrrisponde anche
 * alla codifica ASCII) di questo array contiene uno struct Character che punta al nodo avente quel carattere. Così facendo possiamo
 * risalire al suo percorso(bottom-top) e invertire il percorso.
 */
void decode() {
    //in caso il file sia vuoto allora come output stampo lo stesso file vuoto
    if(getInputFileSize()==0)
        return;

    Node *root = initializeTree();
    Node *nullNode = root;
    Character **characters = calloc(MAXASCIICHARS, sizeof(Character*)); /* initializing with 0s */
    initializeCompletionBar();

    while (!isEOF()) {
        Node *currNode = root;
        if(getNullNodeOrMatch(&currNode))
            break;
        unsigned char c;
        if (isNullNode(currNode)) {
            c = readByte();
            currNode = newCharacter(c, &nullNode, characters);
        } else
            c = getCharacter(currNode);
        writeData(c);
        checkSiblingsProperty(currNode, root);
    }
}
