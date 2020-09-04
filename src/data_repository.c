#define data_repository_IMPORT
#include "data_repository.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CURRENT_PATH "./"
#define MAX_MESSAGE_LENGTH 100
// Size of about 1 MB to enhance all the readings and writings without
// without making too many requests to the operating system
#define MAX_BUFFER_SIZE (1<<20)

struct generaldata{
    FILE *INPUT_FILE, *OUTPUT_FILE; // Input and output files
    uc nr_of_bits, input_file_name[MAX_MESSAGE_LENGTH], output_file_name[MAX_MESSAGE_LENGTH]; // Names of the input and output files
    size_t input_file_size, output_file_size; // The size of the input and output file in bytes
    time_t start_time, end_time; // Value of the start time and end time
};

/**
 * Using these bigger buffers, computing time is optimized because the
 * requests to the os are less.
 */
static uc buffer_reader[MAX_BUFFER_SIZE];
static ui buffer_reader_size=0;
static uc buffer_writer[MAX_BUFFER_SIZE];
static ui buffer_writer_size=0;
static ul input_current_pos=0;


// Rapresents a general info such as the name of the input and output file
static GeneralData dataInfo;

/**
 * Methods that print some info to the terminal, such as the author the name
 * of the input and output files and the total time and collisions.
 */
static void print_info();
/**
 * Methods that close the input and output files
 */
static void close_files();


void close_files(){
    fclose(dataInfo.INPUT_FILE);fclose(dataInfo.OUTPUT_FILE);
}

void print_info(const uc* input_file_name, const uc* output_file_name){
    log("\n**********************FGK**********************\n");
    log("Author: Mohamed Boutaleb\n");
    log_param("Input file name: %s\n",input_file_name);
    log_param("Output file name: %s\n",output_file_name);
    dataInfo.start_time=time(NULL);
    strcpy(dataInfo.input_file_name, input_file_name);
    strcpy(dataInfo.output_file_name, output_file_name);

    fseek(dataInfo.INPUT_FILE, 0, SEEK_END);
    dataInfo.input_file_size=ftell(dataInfo.INPUT_FILE);

    fseek(dataInfo.INPUT_FILE, -1, SEEK_END);
    read_byte(&dataInfo.nr_of_bits);

    rewind(dataInfo.INPUT_FILE);

    log("Computing data...\n");
}

uc read_byte(uc* byte_to_read){
    if(input_current_pos==buffer_reader_size) {
        buffer_reader_size = fread(buffer_reader, sizeof(uc), MAX_BUFFER_SIZE, dataInfo.INPUT_FILE);
        input_current_pos=0;
        if (buffer_reader_size == 0)
            return 0;
    }

    *byte_to_read=buffer_reader[input_current_pos++];
    return 1;
}

size_t get_input_file_size(){
    return dataInfo.input_file_size;
}

uc write_byte(const uc* byte_to_write){
    static ul current_pos=0;
    if(current_pos==MAX_BUFFER_SIZE){
        fwrite(buffer_writer, sizeof(uc), current_pos, dataInfo.OUTPUT_FILE);
        current_pos=0;
    }
    buffer_writer[current_pos++]=*byte_to_write;
    buffer_writer_size=current_pos;
    return buffer_writer[buffer_writer_size];
}

void close_files_output_info(){
    dataInfo.end_time=time(NULL);

    log_param("\nSize of input file: %zu byte\n", dataInfo.input_file_size);

    // Write the remaining byte in the buffer writer
    if(buffer_writer_size)
        fwrite(buffer_writer, sizeof(uc), buffer_writer_size, dataInfo.OUTPUT_FILE);

    fseek(dataInfo.OUTPUT_FILE, 0, SEEK_END);
    dataInfo.output_file_size=ftell(dataInfo.OUTPUT_FILE);
    log_param("Size of output file: %zu byte\n", dataInfo.output_file_size);

    // Close files after calculating the compressing ratio of the output file
    close_files();

    double compressing_ratio=100.0-((double)dataInfo.output_file_size / (double)dataInfo.input_file_size * 100.0);
    log_param("Compressing ratio: %.2lf %%", (dataInfo.input_file_size == 0 ? 0 : compressing_ratio));

    dataInfo.end_time=time(NULL);
    log_param("\nTotal time: %ld s", (dataInfo.end_time - dataInfo.start_time));
    log("\n**********************FGK**********************\n");
}

void initialize_files(const uc *input_file_name, const uc * output_file_name){
    uc error_message[MAX_MESSAGE_LENGTH], file_name[MAX_MESSAGE_LENGTH]=CURRENT_PATH;
    if((dataInfo.INPUT_FILE=fopen(strcat(file_name, input_file_name), "rb+")) == NULL){
        sprintf(error_message, "Something gone wrong with the input file. Make sure that '%s' exists and is in the right directory", input_file_name);
        log_error(error_message);
        close_files();
        exit(ERROR_INPUT_OUTPUT_FILE);
    }
    file_name[2]='\0';
    if((dataInfo.OUTPUT_FILE=fopen(strcat(file_name, output_file_name), "wb+")) == NULL){
        sprintf(error_message, "Something gone wrong with the output file. Make sure that '%s' has a valid name", output_file_name);
        log_error(error_message);
        close_files();
        exit(ERROR_INPUT_OUTPUT_FILE);
    }
    print_info(input_file_name, output_file_name);
}

us is_EOF(const us buffer_size){
    if (dataInfo.nr_of_bits != 8)
        if (buffer_reader_size-1==input_current_pos && dataInfo.nr_of_bits <= (8 - buffer_size)&&feof(dataInfo.INPUT_FILE))
            return 1;
    if (buffer_reader_size==input_current_pos && feof(dataInfo.INPUT_FILE))
        return 1;
    return 0;
}
