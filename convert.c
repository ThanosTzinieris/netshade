#include "convert.h"
#include "netpbm.h"

int convert_p3_to_p2(FILE* input, FILE* output, int width, int height, int max){
	
	int M, R, G, B, pixel;
	
	fprintf(output, "P2\n");
	fprintf(output, "%d %d\n", width, height);
	fprintf(output, "%d\n", max);
	
	for (M = 0; M < height * width; M++){
		
		R = G = B = 0;
		
		if (!read_number(input, &R)){
			return 0;
		}
		
		if (!read_number(input, &G)){
			return 0;
		}
		
		if (!read_number(input, &B)){
			return 0;
		}
		
		pixel = (299 * R + 587 * G + 114 * B) / 1000;
		
		fprintf(output, "%d", pixel);
		
		if ((M + 1) % width == 0){
			fprintf(output, "\n");
		}else{
			fprintf(output, " ");
		}
		
	}
	
	return 1;
	
}

int convert_p3_to_p1(FILE* input, FILE* output, int width, int height, int max){
	
	int M;
	int R, G, B, pixel;
	
	fprintf(output, "P1\n");
	fprintf(output, "%d %d\n", width, height);
	
	for (M = 0; M < height * width; M++){
		
		R = G = B = 0;
		
		if (!read_number(input, &R)){
			return 0;
		}
		
		if (!read_number(input, &G)){
			return 0;
		}
		
		if (!read_number(input, &B)){
			return 0;
		}
		
		pixel = (299 * R + 587 * G + 114 * B) / 1000;
		
		if (pixel >= (max + 1) / 2){
			fprintf(output, "0");
		}else{
			fprintf(output, "1");
		}
		
		if ((M + 1) % width == 0){
			fprintf(output, "\n");
		}else{
			fprintf(output, " ");
		}
		
	}
	
	return 1;
	
}

int convert_p2_to_p1(FILE* input, FILE* output, int width, int height, int max){
	
	int M;
	int pixel;
	
	fprintf(output, "P1\n");
	fprintf(output, "%d %d\n", width, height);
	
	for (M = 0; M < height * width; M++){
		
		if (!read_number(input, &pixel)){
			return 0;
		}
		
		if (pixel >= (max + 1) / 2){
			fprintf(output, "0");
		}else{
			fprintf(output, "1");
		}
		
		if ((M + 1) % width == 0){
			fprintf(output, "\n");
		}else{
			fprintf(output, " ");
		}
		
	}
	
	return 1;
	
}

int convert_p6_to_p5(FILE* input, FILE* output, int width, int height, int max){
	
	int M;
	int R, G, B, pixel;
	
	fprintf(output, "P5\n");
	fprintf(output, "%d %d\n", width, height);
	fprintf(output, "%d\n", max);
	
	move_to_image_data(input);
	
	for (M = 0; M < height * width; M++){
		
		R = fgetc(input);
		G = fgetc(input);
		B = fgetc(input);
		
		if (R == EOF || G == EOF || B == EOF){
			return 0;
		}
		
		pixel = (299 * R + 587 * G + 114 * B) / 1000;
		
		fputc(pixel, output);
		
	}
	
	return 1;
	
}

int convert_p6_to_p4(FILE* input, FILE* output, int width, int height, int max){
	
	int M, N;
	int R, G, B, pixel;
	int byte, bitcount;
	
	fprintf(output, "P4\n");
	fprintf(output, "%d %d\n", width, height);
	
	move_to_image_data(input);
	
	for (M = 0; M < height; M++){
		
		byte = 0;
		bitcount = 0;
		
		for (N = 0; N < width; N++){
			
			R = fgetc(input);
			G = fgetc(input);
			B = fgetc(input);
			
			if (R == EOF || G == EOF || B == EOF){
				return 0;
			}
			
			pixel = (299 * R + 587 * G + 114 * B) / 1000;
			
			if (pixel >= (max + 1) / 2){
				pixel = 0;
			}else{
				pixel = 1;
			}
			
			byte = (byte << 1) | pixel;
			bitcount++;
			
			if (bitcount == 8){
				fputc(byte, output);
				byte = 0;
				bitcount = 0;
			}
			
		}
		
		if (bitcount > 0){
			byte = byte << (8 - bitcount);
			fputc(byte, output);
		}
		
	}
	
	return 1;
	
}

int convert_p5_to_p4(FILE* input, FILE* output, int width, int height, int max){
	
	int M, N;
	int pixel;
	int byte, bitcount;
	
	fprintf(output, "P4\n");
	fprintf(output, "%d %d\n", width, height);
	
	move_to_image_data(input);
	
	for (M = 0; M < height; M++){
		
		byte = 0;
		bitcount = 0;
		
		for (N = 0; N < width; N++){
			
			pixel = fgetc(input);
			
			if (pixel == EOF){
				return 0;
			}
			
			if (pixel >= (max + 1) / 2){
				pixel = 0;
			}else{
				pixel = 1;
			}
			
			byte = (byte << 1) | pixel;
			bitcount++;
			
			if (bitcount == 8){
				fputc(byte, output);
				byte = 0;
				bitcount = 0;
			}
			
		}
		
		if (bitcount > 0){
			byte = byte << (8 - bitcount);
			fputc(byte, output);
		}
		
	}
	
	return 1;
	
}
