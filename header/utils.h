#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t ui;
typedef uint64_t ul;
typedef uint8_t uc;
typedef uint16_t us;

#ifndef EXTERN
#define EXTERN extern
#endif

// Logger of a simple message
#define log(message) printf((message));
// Logger of a message with a parameter
#define log_param(message, param) printf((message), param);
// Logger in the stderr of a message error
#define log_error(message) fprintf(stderr, message);

// All the errors to output if something has gone wrong
enum{ERROR_ARGUMENTS=1, ERROR_INPUT_OUTPUT_FILE=(1<<1), ERROR_OPTION=(1|1<<1)}errors;


#endif //PROJECT_UTILS_H
