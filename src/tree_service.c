#include "tree_service.h"
#include "buffer_service.h"

#define NULL_CHARACTER (int)NULL

/**
 * @Node data structure used to generate a tree
 * @right_child right node
 * @left_child left node
 * @parent parent node
 * @frequency frequency of the character
 * @order order of the node
 */
struct node{
    Node *right_child;
    Node *left_child;
    Node *parent;
    ui order, frequency;
    uc character;
};

/**
 * @byte a char represented in ASCII
 * @nodePointer del byte che punta al nodo di dove si trova il nodo con quel byte/simbolo
 */
struct character{
    uc byte;
    Node *nodePointer;
};

/**
 * Check if a node is a leaf or not
 * @param node to check
 * @return true if it's a leaf node otherwise 0
 */
static ui is_leaf(Node *node);

/**
 * Find the node to swap
 * @param node_with_max_value
 * @param root of the tree
 * @return the possible node to swap
 */
static Node *find_node_to_swap(Node *node_with_max_value, Node *root);

/**
 * @param node to verify
 * @return true if the node has a parent
 */
static ui is_root(Node *node);

/**
 * This method will swap two nodes
 * @param first_node
 * @param second_node
 */
static void swap_nodes(Node *first_node, Node *second_node);

void swap_nodes(Node *first_node, Node *second_node){
    ui tempOrder=first_node->order;
    first_node->order=second_node->order;
    second_node->order=tempOrder;

    if(first_node->parent->left_child == first_node)
        first_node->parent->left_child = second_node;
    else
        first_node->parent->right_child=second_node;

    if(second_node->parent->left_child == second_node)
        second_node->parent->left_child=first_node;
    else
        second_node->parent->right_child=first_node;

    Node *temp_parent=first_node->parent;
    first_node->parent=second_node->parent;
    second_node->parent=temp_parent;
}

Node *find_node_to_swap(Node *node_with_max_value, Node *root) {
    Node *possible_node=node_with_max_value;
    if(root->frequency > possible_node->frequency && !is_leaf(root)){
        Node *greatestLeftNode= find_node_to_swap(possible_node, root->left_child);
        if(greatestLeftNode)
            possible_node=greatestLeftNode;
        Node *greatestRightNode= find_node_to_swap(possible_node, root->right_child);
        if(greatestRightNode)
            possible_node=greatestRightNode;
    }else if(root->frequency == possible_node->frequency && root->order > possible_node->order)
        possible_node=root;
    return (possible_node != node_with_max_value) ? possible_node : NULL;
}

ui is_leaf(Node *node){
    return node->right_child==NULL && node->left_child ==NULL;
}

uc get_character(Node *node){
    return (node)? node->character: NULL_CHARACTER;
}

ui get_null_node_or_match(Node **curr_node){
    ui endOfFile = 0;
    while (!is_leaf(*curr_node) && !endOfFile) {
        us bit = read_bit();
        if (bit == 0)
            *curr_node = (*curr_node)->left_child;
        else if (bit == 1)
            *curr_node = (*curr_node)->right_child;
        else
            endOfFile = 1;
    }
    return endOfFile;
}

ui is_null_node(Node *node){
    return node->character == NULL_CHARACTER && node->frequency == 0 && node->left_child == NULL && node->right_child == NULL;
}

ui is_root(Node *node){
    return node->character == NULL_CHARACTER && node->parent == NULL;
}

void check_siblings_property(Node *current_node, Node *root){
    while(!is_root(current_node)){
        Node *nodeToSwap= find_node_to_swap(current_node, root);
        if(nodeToSwap && current_node->parent != nodeToSwap)
            swap_nodes(current_node, nodeToSwap);
        current_node->frequency++;
        current_node=current_node->parent;
    }
    current_node->frequency++;
}

Node *initialize_tree(){
    Node *root=malloc(sizeof(Node));
    root->frequency=0;
    root->character=NULL_CHARACTER;
    root->order= MAX_NUMBER_OF_NODES;
    root->left_child=NULL;
    root->right_child=NULL;
    root->parent=NULL;
    return root;
}

Node *get_node_by_character(uc character, Character **characters){
    Character *characterInArray=characters[(ui)character];
    return characterInArray?characterInArray->nodePointer:NULL;
}

Node *allocate_new_character(const uc character, Node **nullNode, Character **characters){
    Node *left_node= new_node(*nullNode, NULL_CHARACTER, 0, (*nullNode)->order - 2);
    Node *right_node= new_node(*nullNode, character, 1, (*nullNode)->order - 1);

    Node *prevNullNode=*nullNode;
    (*nullNode)->right_child=right_node;
    (*nullNode)->left_child=left_node;

    ui characterIndex = (ui)character;
    characters[characterIndex] = malloc(sizeof(Character));
    characters[characterIndex]->byte = character;
    characters[characterIndex]->nodePointer = right_node;

    *nullNode=left_node;
    return prevNullNode;
}


ui *match_path(Node *node, ui *size){
    Node *current = node;
    ui *code = malloc(sizeof(ui) * MAX_NUMBER_OF_NODES); /* worst case */

    ui i = 0;
    while (!is_root(current)) {
        Node *parent = current->parent;
        code[i] = (parent->left_child == current) ? 0 : 1;
        current = current->parent;
        i++;
    }

    *size = i;
    return code;
}

Node *new_node(Node *parent, uc symbol, ui frequency, ui order){
    Node *node = malloc(sizeof(Node));
    node->parent = parent;
    node->left_child = NULL;
    node->right_child = NULL;
    node->character = symbol;
    node->frequency = frequency;
    node->order = order;
    return node;
}
