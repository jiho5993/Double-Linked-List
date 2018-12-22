#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
	char val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;//----------------
	int size;
} DLL;

Node *newnode(char n)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->val = n;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

DLL *newDLL() {
	DLL *temp = (DLL *)malloc(sizeof(DLL));
	temp->head = NULL;
	temp->tail = NULL;//----------
	temp->size = 0;
	return temp;
}