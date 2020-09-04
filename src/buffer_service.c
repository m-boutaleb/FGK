#include "buffer_service.h"
#include "completion_bar_service.h"

static uc buffer=0;
static us buffer_size=8;

/**
 * riempe il buffer se questo risulta vuoto
 */
ui fill_buffer_if_empty(){
    if (buffer_size == 0) {
        buffer_size = 8;
        return read_byte_update_c_bar(&buffer);
    }
    return 1;
}

void reset_buffer(){
    buffer_size=0;
}

us get_buffer_size(){return buffer_size;}

/**
 * @param buffer ciò che bisogna scrivere nel file
 * @param bufferSize quanta capacità di bit possiede ancora il buffer
 * Scrive la quantita di bit che deve non essere letta alla fine
 */
void write_remaining_bits() {
    if (buffer_size < 8)
        write_byte(&buffer);

    buffer= (buffer_size == 8) ? 8 : 8 - buffer_size;
    write_byte(&buffer);
}

/**
 * @return il bit contenuto nel buffer
 */
static us read_buffer_bit(){
    return (buffer >> buffer_size) & 1;
}

/**
 * @return il byte letto
 */
uc read_buffer_byte() {
    uc result = 0;

    us j, bit;
    for (j = 0; j < 8; j++) {
        bit = read_bit();
        bit = bit << (7-j);
        result |= bit;
    }

    return result;
}

/**
 * @return un bit alla volta però prima fa un check per vedere se il buffer è pieno oppure vuoto
 */
us read_bit() {
    us is_EOF=fill_buffer_if_empty();
    if(!is_EOF)
        return -1;
    buffer_size--;
    return read_buffer_bit();
}

/**
 * @param byte to add to the buffer
 * @return il buffer con gli shift necessari
 */
void add_byte_to_buffer(uc byte) {
    uc currBuffer = buffer;

    us bitsToWrite = buffer_size;
    us shifter = 8 - bitsToWrite;
    uc tempByte = byte >> shifter;
    currBuffer = currBuffer | tempByte;

    write_byte(&currBuffer);

    currBuffer = byte << bitsToWrite;

    buffer= (buffer_size == 8) ? 0 : currBuffer;
}

/**
 * @param code percorso dell'albero
 * @param code_size lunghezza del percorso
 * @param buffer
 * @param bufferSize
 * @return il buffer contenente tutti i bit rimasti del percorso
 */
void add_path_to_buffer(ui *code, ui code_size){
    uc curr_buffer = buffer;

    for (int i = code_size - 1; code_size && i >= 0; i--) {
        uc bit = code[i] << (buffer_size - 1);
        curr_buffer = curr_buffer | bit;

        buffer_size--;

        if (buffer_size == 0) {
            write_byte(&curr_buffer);
            curr_buffer = 0;
            buffer_size = 8;
        }
    }
    buffer=curr_buffer;
}
