#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
	double xdim;
	double ydim;
	double xcoord;
	double ycoord;
	struct _Node *left;
	struct _Node *right;
}Node;

Node *Load_Binary_File(FILE *);
void destroyTree(Node *);
void printPostorder(Node *, FILE *);
Node *getDimensions(Node *node);
void saveDimensions(Node *node, FILE *outptr1);
Node *getCoordinates(Node *node);
void saveCoordinates(Node *node, FILE *outptr3);
