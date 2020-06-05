#include "encoding.h"


void encode() {
    if(getInputFileSize()==0)
        return;
    Node *root = initializeTree();
    Node *nullNode = root;

    Character **characters = calloc(MAXASCIICHARS, sizeof(Character*)); /* initializing with 0s */

    initializeCompletionBar();
    initializeBufferSize();
    unsigned char currByte;
    while (readData(&currByte) > 0) {
        Node *characterTree = getNodeFromCharacter(currByte, characters);

        increaseCompletionBar();

        if (characterTree) {
            int codeSize;
            int *symbolCode = codeOfNode(characterTree, &codeSize);
            addPathToBuffer(symbolCode, codeSize);

            checkSiblingsProperty(characterTree, root);
            free(symbolCode);
        } else {
            int codeSize;

            int *nullCode = codeOfNode(nullNode, &codeSize);
            addPathToBuffer(nullCode, codeSize);
            addNewByteToBuffer(currByte);

            Node *newNode = newCharacter(currByte, &nullNode, characters);
            checkSiblingsProperty(newNode, root);
            free(nullCode);
        }
    }

    writeRemainingBits();
}