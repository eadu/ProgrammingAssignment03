#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		fprintf(stderr,"Error: Usage ./proj3 input_file output_file1 output_file2 output_file3");
		return EXIT_FAILURE;
	}
	FILE *inptr;
	inptr = fopen(argv[1], "r");
	if(inptr == NULL)
	{
		fprintf(stderr, "Error: Cannot open %s", argv[1]);
		return EXIT_FAILURE;
	}
	Node *tree;
	tree = Load_Binary_File(inptr);
	fclose(inptr);
	FILE *outptr1;
	outptr1 = fopen(argv[2], "w");
	if(outptr1 == NULL)
	{
		fprintf(stderr, "Error: Cannot open %s", argv[2]);
		return EXIT_FAILURE;
	}
	printPostorder(tree, outptr1);
	fclose(outptr1);
	outptr1 = fopen(argv[3], "w");
	
	
	//packing
	tree = getDimensions(tree);
	saveDimensions(tree, outptr1);
	fclose(outptr1);
	outptr1 = fopen(argv[4], "w");
	tree = getCoordinates(tree);
	saveCoordinates(tree, outptr1);
	
	fclose(outptr1);
	destroyTree(tree);

	return EXIT_SUCCESS;
}
