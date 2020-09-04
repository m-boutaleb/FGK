#ifndef PROJECT_TREE_SERVICE_H
#define PROJECT_TREE_SERVICE_H
#include "utils.h"

#ifndef EXTERN
#define EXTERN extern
#endif

// Max characters in ASCII code
#define MAX_ASCII_CHARS 256
#define MAX_NUMBER_OF_NODES MAX_ASCII_CHARS*2

typedef struct character Character;
typedef struct node Node;

/**
 * This method is used to create a new node
 * @param parent of the new node
 * @param symbol associated with the new node
 * @param frequency frequency of the node
 * @param order order of the new node
 * @return new node
 */
EXTERN Node *new_node(Node *parent, uc symbol, ui frequency, ui order);
/**
 * This method replaces the null node with the new character by creating the new null node
 * @param character to replace witht he null node
 * @param nullNode pointer to the null node
 * @param characters and pointers to them
 * @return the new null node
 */
EXTERN Node *allocate_new_character(uc character, Node **nullNode, Character **characters);
/**
 * Will check whether the path leads to a null node
 * @param curr_node root node
 * @return the null node or the match
 */
EXTERN ui get_null_node_or_match(Node **curr_node);
/**
 * Check whether the tree is respecting the sibling's property
 * @param current_node the node where to start
 * @param root of the tree
 */
EXTERN void check_siblings_property(Node *current_node, Node *root);
/**
 * Creates the root of the tree that initially correspond to the null node
 * @return the root created
 */
EXTERN Node *initialize_tree();
/**
 * Get the node given a character
 * @param character in the node
 * @param characters array of pointers to the node
 * @return the node of the character
 */
EXTERN Node *get_node_by_character(uc character, Character **characters);
/**
 * Calculate the path of the node until the root
 * @param node of the match character
 * @param size of the path
 * @return an array of int containing the reversed path
 */
EXTERN ui *match_path(Node *node, ui *size);
/**
 * Check whether a node correspond to a null node
 * @param node to check
 * @return true if is a null node otherwise false
 */
EXTERN ui is_null_node(Node *node);
/**
 * Get the character from a node
 * @param node containing the character
 * @return the character
 */
EXTERN uc get_character(Node *node);

#endif
