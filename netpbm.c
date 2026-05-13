#include "netpbm.h"

const char* get_image_type_name(int imgtype){
	
	if (imgtype == 1){
		return "P1 - ASCII black and white image";
	}else if (imgtype == 2){
		return "P2 - ASCII grayscale image";
	}else if (imgtype == 3){
		return "P3 - ASCII color image";
	}else if (imgtype == 4){
		return "P4 - binary black and white image";
	}else if (imgtype == 5){
		return "P5 - binary grayscale image";
	}else if (imgtype == 6){
		return "P6 - binary color image";
	}else{
		return "Unknown or invalid Netpbm image type";
	}
	
}

int read_magic_number(FILE* input){
	
	int c;
	int imgtype;
	
	c = fgetc(input);
	
	if (c != 'P'){
		return 0;
	}
	
	c = fgetc(input);
	
	if (c >= '1' && c <= '6'){
		imgtype = c - 48;
		return imgtype;
	}
	
	return 0;
	
}

int read_number(FILE* input, int* number){
	
	int c;
	*number = 0;
	
	c = fgetc(input);
	
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
		c = fgetc(input);
	}

	while (c == '#'){
		while (c != '\n' && c != EOF){
			c = fgetc(input);
		}
		
		c = fgetc(input);
		
		while (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
			c = fgetc(input);
		}
	}

	if (c < '0' || c > '9'){
		return 0;
	}

	while (c >= '0' && c <= '9'){
		*number = (*number * 10) + (c - 48);
		c = fgetc(input);
	}
	
	if (c != EOF){
		ungetc(c, input);
	}

	return 1;
	
}

int read_image_header(FILE* input, int imgtype, int* width, int* height, int* max){
	
	if (!read_number(input, width)){
		return 0;
	}
	
	if (!read_number(input, height)){
		return 0;
	}
	
	if (imgtype == 1 || imgtype == 4){
		*max = 1;
	}else{
		if (!read_number(input, max)){
			return 0;
		}
	}
	
	return 1;
	
}

void move_to_image_data(FILE* input){
	
	int c;
	
	c = fgetc(input);
	
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
		c = fgetc(input);
	}
	
	while (c == '#'){
		while (c != '\n' && c != EOF){
			c = fgetc(input);
		}
		
		c = fgetc(input);
		
		while (c == ' ' || c == '\t' || c == '\n' || c == '\r'){
			c = fgetc(input);
		}
	}
	
	if (c != EOF){
		ungetc(c, input);
	}
	
}
