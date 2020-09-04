#ifndef ASD20192020TPG6_BUFFERMANAGER_H
#define ASD20192020TPG6_BUFFERMANAGER_H
#include "data_repository.h"
void add_byte_to_buffer(unsigned char byte);
us read_bit();
void write_remaining_bits();
void add_path_to_buffer(ui *code, ui code_size);
uc read_buffer_byte();
void reset_buffer();
us get_buffer_size();
#endif //ASD20192020TPG6_BUFFERMANAGER_H
