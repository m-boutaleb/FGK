#include "tree.h"

/**
 * @Node struttura usata per generare l'albero
 * @rightChild nodo di destra
 * @leftChild nodo di sinistra
 * @parent nodo padre del nodo
 * @frequency la frequenza del carattere
 * @order l'ordine del nodo più sta in alto più sarà alto
 */
struct node{
    Node *rightChild;
    Node *leftChild;
    Node *parent;
    int order;
    int frequency;
    unsigned char character;
};


/**
 * @byte in codifica ASCII
 * @nodePointer del byte che punta al nodo di dove si trova il nodo con quel byte/simbolo
 */
struct character{
    unsigned char byte;
    Node *nodePointer;
};


static Node *findNodeToSwap(Node *pNode, Node *root);


/**
 * @param node
 * @return il simbolo di quel nodo
 */
unsigned char getCharacter(Node *node){
    return (node)?node->character:NULLCHARACTER;
}

/**
 * @param currNode nodo corrente che alla prima chiamata corrisponde al root dove leggendo bit per volta cambia fino
 * ad arrivare al nodo foglio(che può essere il rootNode oppure un match)
 * @return il nodo che il percorso ci ha portato che può essere un NullNodo(si tratta del NYT) oppure del nodo di match
 */
int getNullNodeOrMatch(Node **currNode){
    int endOfFile = 0;
    while (!isLeaf(*currNode) && !endOfFile) {
        int bit = readBit();
        if (bit == 0)
            *currNode = getLeftChild(*currNode);
        else if (bit == 1)
            *currNode = getRightChild(*currNode);
        else
            endOfFile = 1;
    }
    return endOfFile;
}


/**
 * @param node
 * @return la frequenza del nodo
 */
int getFrequency(Node *node){
    return (node)?node->frequency:NULLCHARACTER;
}


/**
 * @param node
 * @return ritorna l'ordine del nodo
 */
int getOrder(Node *node){
    return (node)?node->order:NULLCHARACTER;
}


/**
 * @param node
 * @return ritorna il nodo sinistro del node se esiste altrimenti NULL
 */
Node *getLeftChild(Node *node){
    return (node)?(node->leftChild):NULL;
}


/**
 * @param node
 * @return ritorna il nodo destro del node se esiste altrimenti NULL
 */
Node * getRightChild(Node *node){
    return (node)?(node->rightChild):NULL;
}


/**
 * @param node
 * @return ritorna il nodo padre del node se esiste altrimenti NULL
 */
Node * getParent(Node *node){
    return (node)?node->parent:NULL;
}

/**
 * @param node
 * @return se il nodo non ha frequenza e non ha un un simbolo valido allora è un nodo nullo
 */
int isNullNode(Node *node){
    return node->character==NULLCHARACTER && node->frequency==0 && node->leftChild==NULL && node->rightChild==NULL;
}

/**
 * @param node
 * @return se un nodo non ha figli allora è una foglia
 */
int isLeaf(Node *node){
    return node->rightChild==NULL && node->leftChild ==NULL;
}

/**
 * @param node
 * @return se il nodo ha un padre, se ce l'ha allora non è il nodo radice altrimenti si
 */
int isRoot(Node *node){
    return node->character==NULLCHARACTER && node->parent==NULL;
}

/**
 *
 * @param n1 primo nodo
 * @param n2 secondo nodo
 * swappa i nodi vengono swappati ma il loro ordine di chi sta in alto rimane invariato
 */
void swapNodes(Node *n1, Node *n2){
    int tempOrder=n1->order;
    n1->order=n2->order;
    n2->order=tempOrder;

    if(n1->parent->leftChild==n1)
        n1->parent->leftChild = n2;
    else
        n1->parent->rightChild=n2;

    if(n2->parent->leftChild==n2)
        n2->parent->leftChild=n1;
    else
        n2->parent->rightChild=n1;

    Node *tempParent=n1->parent;
    n1->parent=n2->parent;
    n2->parent=tempParent;
}

/**
 * @param currentNode il vecchio nodo nullo su cui è stato aggiunto un carattere oppure nel caso
 * di un match il nodo che è stato incrementato
 * @param root radice dell'albero
 * questo codice effettua un controllo della sibling's property trovando prima il nodo che non rispetta la regola
 * poi swappa e infine aggiorna anche le frequenze dei singoli nodi iterativamente fino a che non raggiunge il nodo nullo
 */
void checkSiblingsProperty(Node *currentNode, Node *root){
    while(!isRoot(currentNode)){
        Node *nodeToSwap=findNodeToSwap(currentNode, root);
        if(nodeToSwap && currentNode->parent!=nodeToSwap)
            swapNodes(currentNode, nodeToSwap);
        currentNode->frequency++;
        currentNode=currentNode->parent;
    }
    currentNode->frequency++;
}

/**
 * semplicemente crea il nodo radice
 * @return il nodo radice
 */
Node *initializeTree(){
    Node *root=malloc(sizeof(Node));
    root->frequency=0;
    root->character=NULLCHARACTER;
    root->order=MAXNUMBERNODE;
    root->leftChild=NULL;
    root->rightChild=NULL;
    root->parent=NULL;
    return root;
}

/**
 * @param character il simbolo da cercare
 * @param characters l'array di simboli
 * @return cerca nell'array il carattere cercato usato il numero della sua codifica ASCII e se questo carattere esiste allora ritorna
 * il nodo a cui punta
 */
Node *getNodeFromCharacter(unsigned char character, Character **characters){
    Character *characterInArray=characters[(unsigned int)character];
    return characterInArray?characterInArray->nodePointer:NULL;
}


/**
 * @param character da aggiungere nell'albero
 * @param nullNode il nodo nullo
 * @param characters l'array di simboli che devono puntare al nodo che contiene quel carattere
 * @return il vecchio nodo nullo
 */
Node *newCharacter(unsigned char character, Node **nullNode, Character **characters){
    Node *leftNode=newNode(*nullNode, NULLCHARACTER, 0, (*nullNode)->order-2);
    Node *rightNode=newNode(*nullNode, character, 1, (*nullNode)->order-1);

    Node *prevNullNode=*nullNode;
    (*nullNode)->rightChild=rightNode;
    (*nullNode)->leftChild=leftNode;

    unsigned int characterIndex = (unsigned int)character;
    characters[characterIndex] = malloc(sizeof(Character));
    characters[characterIndex]->byte = character;
    characters[characterIndex]->nodePointer = rightNode;

    *nullNode=leftNode;
    return prevNullNode;
}


/**
 * @param nodeWithMaxValue nodo su cui è stata apportata la modifica
 * @param root il nodo radice
 * @return il nodo che ha un ordine superiore ma una frequenza minore sia orizzontalmente che verticalmente
 */
static Node *findNodeToSwap(Node *nodeWithMaxValue, Node *root) {
    Node *possibleNode=nodeWithMaxValue;
    if(root->frequency  > possibleNode->frequency && !isLeaf(root)){
        Node *greatestLeftNode=findNodeToSwap(possibleNode, root->leftChild);
        if(greatestLeftNode)
            possibleNode=greatestLeftNode;
        Node *greatestRightNode=findNodeToSwap(possibleNode, root->rightChild);
        if(greatestRightNode)
            possibleNode=greatestRightNode;
    }else if(root->frequency == possibleNode->frequency && root->order > possibleNode->order)
        possibleNode=root;
    return (possibleNode!=nodeWithMaxValue)?possibleNode:NULL;
}


/**
 * @param node su cui bisogna calcolare il suo percorso
 * @param size la lunghezza del suo percorso
 * @return l'array del percorso
 */
int *codeOfNode(Node *node, int *size){
    Node *current = node;
    int *code = malloc(sizeof(int) * MAXNUMBERNODE); /* worst case */

    int i = 0;
    while (!isRoot(current)) {
        Node *parent = current->parent;
        code[i] = (parent->leftChild == current) ? 0 : 1;
        current = current->parent;
        i++;
    }
    reverseCode(code, i);

    *size = i;
    return code;
}


/**
 * @param parent nodo padre del nuovo nodo da creare
 * @param character il carattere da aggiungere al nodo
 * @param frequency frequenza del nuovo nodo
 * @param order il suo ordine
 * @return il nuovo nodo creato
 */
Node *newNode( Node *parent,unsigned char character, int frequency, int order){
    Node *node = malloc(sizeof(Node));
    node->parent = parent;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->character = character;
    node->frequency = frequency;
    node->order = order;
    return node;
}
