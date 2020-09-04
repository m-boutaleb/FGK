#ifndef PROJECT_ENCODING_SERVICE_H
#define PROJECT_ENCODING_SERVICE_H
#include "utils.h"

#ifndef EXTERN
#define EXTERN extern
#endif

/**
 * Method that decodes the input file and invokes the method to initialize the files
 * @param input_file_name
 * @param output_file_name
 */
EXTERN void encode(const uc *input_file_name, const uc *output_file_name);

#undef encoding_IMPORT
#undef EXTERN
#endif //PROJECT_ENCODING_SERVICE_H
