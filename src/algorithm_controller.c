#define algorithm_IMPORT
#include <string.h>
#include "algorithm_controller.h"
#include "encoding_service.h"
#include "decoding_service.h"

void initialize_algorithm(const uc *option, const uc* input_file_name, const uc* output_file_name){
    if(!strcmp("-D", option)||!strcmp("-d", option))
        decode(input_file_name, output_file_name);
    else if(!strcmp("-c", option)||!strcmp("-C", option))
        encode(input_file_name, output_file_name);
    else {
        log_error("Invalid option. Please use '-c' or '-d' to compress or decompress data respectively");
        exit(ERROR_OPTION);
    }
}
