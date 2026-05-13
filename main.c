#include <stdio.h>
#include <string.h>
#include "netpbm.h"
#include "convert.h"


void clean_path(char path[]){
	
	int pathlength, i;
	
	pathlength = strlen(path);
	
	if (pathlength > 0 && path[pathlength - 1] == '\n'){
		path[pathlength - 1] = '\0';
		pathlength--;
	}
	
	if (pathlength > 1 && path[0] == '"' && path[pathlength - 1] == '"'){
		path[pathlength - 1] = '\0';
		pathlength--;
		
		for (i = 0; path[i] != '\0'; i++){
			path[i] = path[i + 1];
		}
	}
	
}


void print_conversion_result(int success){
	
	if (success){
		printf("\nConversion completed successfully.\n");
	}else{
		printf("\nConversion failed while reading pixel data.\n");
	}
	
}


int main(){
	
	char inputpath[300], outputpath[300];
	FILE* input;
	FILE* output;
	int imgtype, width, height, max, conversiontype;
	char choice;	// The user might write anything. Filtering later
	
	printf("Figproc by T.T.\n");
	printf("-----------------\n\n");
	
	conversiontype = 0;
	
	printf("Please enter the input image path:\nTip: In Windows explorer, try Shift + Right Click -> Copy as Path.\n\n");

	fgets(inputpath, 300, stdin);
	
	clean_path(inputpath);
	
	input = fopen(inputpath, "rb");
	
	if (input == NULL){
		printf("\nCould not open input file.\n");
		return 1;
	}
	
	imgtype = read_magic_number(input);
	
	if (imgtype != 0){
		if (!read_image_header(input, imgtype, &width, &height, &max)){
			printf("\nCould not read image header.\n");
			fclose(input);
			return 1;
		}
	}
	
	fclose(input);


	printf("\nDetected image type:\n");
	printf("%s\n", get_image_type_name(imgtype));

	if (imgtype == 0){
		printf("\nThis does not appear to be a valid Netpbm image.\n");
		return 1;
	}

	printf("\nImage information:\n");
	printf("Width: %d\n", width);
	printf("Height: %d\n", height);
	printf("Max value: %d\n", max);


	if (imgtype == 1 || imgtype == 4){
		printf("\nThis image is already black and white.\nNo conversion is needed.\n");
	}else if (imgtype == 2 || imgtype == 5){

		printf("\nThis image is grayscale.\nAvailable conversion:\n1. Convert to black and white\n0. Exit\n\nPlease enter your choice: ");

		scanf(" %c", &choice);
		
		if (choice != '0' && choice != '1'){
		    printf("\nInvalid choice. Goodbye.\n");
		    return 1;
		}
		
		if (choice == '1'){
		    conversiontype = 2;
		    printf("\nBlack and white conversion selected.\n");
		}else{
		    printf("\nExiting program.\n");
		}

	}else if (imgtype == 3 || imgtype == 6){

		printf("\nThis image is color.\nAvailable conversions:\n1. Convert to grayscale\n2. Convert to black and white\n0. Exit\n\nPlease enter your choice: ");

		scanf(" %c", &choice);
		
		if (choice != '0' && choice != '1' && choice != '2'){
		    printf("\nInvalid choice. Goodbye.\n");
		    return 1;
		}
		
		if (choice == '1'){
		    conversiontype = 1;
		    printf("\nGrayscale conversion selected.\n");
		}else if (choice == '2'){
		    conversiontype = 2;
		    printf("\nBlack and white conversion selected.\n");
		}else{
		    printf("\nExiting program.\n");
		}

	}


	if (conversiontype != 0){
		getchar();
		
		printf("\nPlease enter the output image path:\n");
		fgets(outputpath, 300, stdin);

		clean_path(outputpath);

		output = fopen(outputpath, "wb");
		
		if (output == NULL){
			printf("\nCould not create output file.\n");
			return 1;
		}
		
		input = fopen(inputpath, "rb");
		
		if (input == NULL){
			printf("\nCould not reopen input file.\n");
			fclose(output);
			return 1;
		}
		
		read_magic_number(input);
		
		if (!read_image_header(input, imgtype, &width, &height, &max)){
			printf("\nCould not read image header before conversion.\n");
			fclose(input);
			fclose(output);
			return 1;
		}
		
		if (imgtype == 2 && conversiontype == 2){
			print_conversion_result(convert_p2_to_p1(input, output, width, height, max));
		}else if (imgtype == 5 && conversiontype == 2){
			print_conversion_result(convert_p5_to_p4(input, output, width, height, max));
		}else if (imgtype == 3 && conversiontype == 1){
			print_conversion_result(convert_p3_to_p2(input, output, width, height, max));
		}else if (imgtype == 3 && conversiontype == 2){
			print_conversion_result(convert_p3_to_p1(input, output, width, height, max));
		}else if (imgtype == 6 && conversiontype == 1){
			print_conversion_result(convert_p6_to_p5(input, output, width, height, max));
		}else if (imgtype == 6 && conversiontype == 2){
			print_conversion_result(convert_p6_to_p4(input, output, width, height, max));
		}else{
			printf("\nThis conversion is not implemented yet.\n");
		}
		
		fclose(input);
		fclose(output);

	}

	return 0;

}

