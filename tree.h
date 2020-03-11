#ifndef ASD20192020TPG6_ALBERO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufferManager.h"
#define ASD20192020TPG6_ALBERO_H
#define MAXASCIICHARS 256
#define MAXNUMBERNODE MAXASCIICHARS*2
#define NULLCHARACTER (int)NULL
typedef struct character Character;
typedef struct node Node;

Node *newNode( Node *parent,unsigned char symbol, int frequency, int order);
Node *newCharacter(unsigned char symbol, Node **nullNode, Character **characters);
int isLeaf(Node *node);
int isRoot(Node *node);
int isRootNode(Node *node);
void swapNodes(Node *n1, Node *n2);
int getNullNodeOrMatch(Node **currNode);
void checkSiblingsProperty(Node *currentNode, Node *root);
Node *initializeTree();
Node *getNodeFromCharacter(unsigned char symbol, Character **characters);
int *codeOfNode(Node *node, int *size);
int isNullNode(Node *node);
unsigned char getCharacter(Node *node);
int getFrequency(Node *node);
int getOrder(Node *node);
Node *getLeftChild(Node *node);
Node * getRightChild(Node *node);
Node * getParent(Node *node);

#endif