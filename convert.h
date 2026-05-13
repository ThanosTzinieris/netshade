#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>

int convert_p3_to_p2(FILE* input, FILE* output, int width, int height, int max);
int convert_p3_to_p1(FILE* input, FILE* output, int width, int height, int max);
int convert_p6_to_p5(FILE* input, FILE* output, int width, int height, int max);
int convert_p6_to_p4(FILE* input, FILE* output, int width, int height, int max);
int convert_p2_to_p1(FILE* input, FILE* output, int width, int height, int max);
int convert_p5_to_p4(FILE* input, FILE* output, int width, int height, int max);

#endif
