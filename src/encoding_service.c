#include "encoding_service.h"
#include "data_repository.h"
#include "tree_service.h"
#include "buffer_service.h"
#include "completion_bar_service.h"


void encode(const uc* input_file_name, const uc* output_file_name) {
    initialize_files(input_file_name, output_file_name);
	if(!get_input_file_size())
		goto close_files;
    Node *root = initialize_tree();
    Node *null_node = root;

    Character **characters = calloc(MAX_ASCII_CHARS, sizeof(Character*)); /* initializing with 0s */

    uc currByte;

    while (read_byte_update_c_bar(&currByte)) {
        Node *character_match = get_node_by_character(currByte, characters);

        ui codeSize;

        if (character_match) {
            ui *match_route = match_path(character_match, &codeSize);
            add_path_to_buffer(match_route, codeSize);

            check_siblings_property(character_match, root);
            free(match_route);
        } else {
            ui *null_path = match_path(null_node, &codeSize);
            add_path_to_buffer(null_path, codeSize);
            add_byte_to_buffer(currByte);

            Node *new_node = allocate_new_character(currByte, &null_node, characters);
            check_siblings_property(new_node, root);
            free(null_path);
        }
    }

    write_remaining_bits();
    close_files:
    close_files_complete_c_bar();
}
