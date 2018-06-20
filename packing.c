/**********************************Programming Assignment 3*************************************/
#include <stdio.h>
#include <stdlib.h>
#include "packing.h"
/*************************************Load_Binary_File********************************************
 *************************************************************************************************
 *This function takes in a file and construct a binary reading by reading the file line by line.**
 ***After a line is read, I check to see if the read in line is a non leaf node or a leaf node.***
 ********************A node is constructed based on what it is.***********************************
 ************************************************************************************************/
Node *Load_Binary_File(FILE *filename)
{
	char line[(sizeof(long double) * 2) + sizeof(long int) + 3] = {0};
	Node *node;
	node = (Node *)malloc(sizeof(Node));
	if(node == NULL)
	{
		fprintf(stderr, "Could not mallac node for tree");
		return NULL;
	}
	fgets(line, sizeof(line), filename);
	
	if(line[0] != 'V' && line[0] != 'H')
	{	
		int data;
		char par1;
		double xdim;
		char comma;
		double ydim;
		char par2;
		sscanf(line, "%d%c%le%c%le%c", &data, &par1, &xdim, &comma, &ydim, &par2);
		node -> data = data;
		node -> xdim = xdim;
		node -> ydim = ydim;
		node -> xcoord = 0;
		node -> ycoord = 0;
		node -> left = NULL;
		node -> right = NULL;
		return node;
	}
	else
	{
		char data;
		sscanf(line, "%c", &data);
		
		node -> data =  data;
		node -> xdim = 0;
		node -> ydim = 0;
		node -> xcoord = 0;
		node -> ycoord = 0;
		node -> left = Load_Binary_File(filename);
		node -> right = Load_Binary_File(filename);
	}
	return node;
}
/*destroyTree: This function frees the allocated memory associated with the constructed binary tree.*/
void destroyTree(Node *node)
{
	if(node == NULL)
	{
		return;
	}
	destroyTree(node -> left);
	destroyTree(node -> right);
	free(node);
}
/***********************************printPostorder***************************************
 ****This function prints a constructed binary tree into a file in postorder fashion*****
 ****************************************************************************************/
void printPostorder(Node *node, FILE *outptr1)
{
	if(node == NULL)
	{
		return;
	}
	printPostorder(node -> left, outptr1);
	printPostorder(node -> right, outptr1);
	if(node -> xdim == 0 && node -> ydim == 0)
	{
		fprintf(outptr1, "%c\n", node -> data);
	}
	else 
	{
		fprintf(outptr1, "%d(%le,%le)\n", node -> data, node -> xdim, node -> ydim);
	}
}
/******Get Dimensions: This funciton calculates the dimensions of each node based on *****
************the dimensions of the children nodes******************************************/
Node *getDimensions(Node *node)
{
	if(node -> left == NULL && node -> right == NULL)
	{
		return node;
	}
	Node *leftNode;
	Node *rightNode;
	leftNode = getDimensions(node -> left);
	rightNode = getDimensions(node -> right);
	if(node -> data == 'V')
	{
		node -> xdim = leftNode -> xdim + rightNode -> xdim;
		if(leftNode -> ydim >= rightNode -> ydim)
		{
			node -> ydim = leftNode -> ydim;
		}
		else
		{
			node -> ydim = rightNode -> ydim;
		}
	}
	else
	{
		node -> ydim = leftNode -> ydim + rightNode -> ydim;
		if(leftNode -> xdim >= rightNode -> xdim)
		{
			node -> xdim = leftNode -> xdim;
		}
		else
		{
			node -> xdim = rightNode -> xdim;
		}
	}
	return node;
}
/********Save Dimensions: Writes the dimensions into a file*********************************/
void saveDimensions(Node *node, FILE *outptr2)
{
	if(node -> left == NULL && node -> right == NULL)
	{
		fprintf(outptr2, "%d(%le,%le)\n", node -> data, node -> xdim, node -> ydim);
		return;
	}
	else 
	{
		fprintf(outptr2, "%c(%le,%le)\n", node -> data, node -> xdim, node -> ydim);
	}
	saveDimensions(node -> left, outptr2);
	saveDimensions(node -> right, outptr2);
}
/********Get coordinates: This function calculates the coordinates of each node.************/
Node *getCoordinates(Node *node)
{
	if(node -> left == NULL && node -> right == NULL)
	{
		return node;
	}
	if(node -> data == 'H')
	{
		node -> left -> xcoord = node -> xcoord;
		node -> left -> ycoord = node -> right -> ydim + node -> ycoord;
		node -> right -> xcoord = node -> xcoord;
		node -> right -> ycoord = node -> ycoord;
	}
	if(node -> data == 'V')
	{
		node -> left -> xcoord = node -> xcoord;
		node -> left -> ycoord = node -> ycoord;
		node -> right -> xcoord = node -> left -> xdim + node -> xcoord;
		node -> right -> ycoord = node -> ycoord;
	}
	getCoordinates(node -> left);
	getCoordinates(node -> right);
	return node;
}
/*******SaveCoordinates: this function writes the calculated coordinates to the output********/
void saveCoordinates(Node *node, FILE *outptr3)
{	
	if(node -> left == NULL && node -> right == NULL)
	{
		fprintf(outptr3, "%d(%le,%le)\n", node -> data, node -> xcoord, node -> ycoord);
		return;
	}
	saveCoordinates(node -> left, outptr3);
	saveCoordinates(node -> right, outptr3);
}
