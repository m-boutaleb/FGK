#include "decoding_service.h"
#include "tree_service.h"
#include "buffer_service.h"
#include "completion_bar_service.h"

/**
 * Si crea prima un array di Character di dimensione 256 dove a loro volta a ogni posizione p (che corrrisponde anche
 * alla codifica ASCII) di questo array contiene uno struct Character che punta al nodo avente quel carattere. Così facendo possiamo
 * risalire al suo percorso(bottom-top) e invertire il percorso.
 */
void decode(const uc* input_file_name, const uc* output_file_name) {
    initialize_files(input_file_name, output_file_name);
	if(!get_input_file_size())
		goto close_files;
    Node *root = initialize_tree();
    Node *null_node = root;
    Character **characters = calloc(MAX_ASCII_CHARS, sizeof(Character*));
    reset_buffer();
    while (!is_EOF(get_buffer_size())) {
        Node *curr_node = root;
        if(get_null_node_or_match(&curr_node))
            break;
        uc new_byte;
        if (is_null_node(curr_node)) {
            new_byte = read_buffer_byte();
            curr_node = allocate_new_character(new_byte, &null_node, characters);
        } else
            new_byte = get_character(curr_node);
        write_byte(&new_byte);
        check_siblings_property(curr_node, root);
    }
    close_files:
    close_files_complete_c_bar();
}
