#ifndef NETPBM_H
#define NETPBM_H

#include <stdio.h>

const char* get_image_type_name(int imgtype);

int read_magic_number(FILE* input);

int read_number(FILE* input, int* number);

int read_image_header(FILE* input, int imgtype, int* width, int* height, int* max);

void move_to_image_data(FILE* input);

#endif
