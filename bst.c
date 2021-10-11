#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct treeNode{
	int data;
	struct treeNode * left;
	struct treeNode * right;
};

struct bst{
	struct treeNode * root;
	int size;

};


struct bst * createbst(){
	struct bst * bstp = (struct bst *) malloc(sizeof(struct treeNode));
	bstp->root = NULL;
	bstp->size = 0;

	return bstp;
}


struct treeNode * createTreeNode(int data){
	struct treeNode * newNode = (struct treeNode *) malloc(sizeof(struct treeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}

struct treeNode * searchEntry(struct treeNode * root,int value){
	// search has ended and value found
	// insertion should be denied since no duplicates
	// are allowed in bst
	if(root->data==value)
		return root;

	if(root->data > value){
		if(root->left==NULL)
			return root;
		else
			return searchEntry(root->left, value);
	}

	if(root->data < value){
		if(root->right==NULL)
			return root;
		else
			return searchEntry(root->right, value);
	}

}

void insert(struct bst * tp, int value){
	struct treeNode * newNode = createTreeNode(value);

	// if the tree is empy set as root
	if(tp->root == NULL)
		tp->root = newNode;

	// find insertion point fit for value
	// if the value is already in tree do nothing
	struct treeNode * candidate = searchEntry(tp->root, value);
	if(candidate->data == value)
		return;

	// if value is smaller add to left
	if(candidate->data > value)
		candidate->left = createTreeNode(value);

	// if value is larger add to right
	if(candidate->data < value)
		candidate->right = createTreeNode(value);
}

struct treeNode * search(struct bst * tp, int value){
	  struct treeNode * candidate = searchEntry(tp->root, value);

	  if(candidate->data == value)
		  return candidate;
	  else
		  return NULL;

}

// this is an auxiliary function for search and insert
// in search we will use the function to search for 
// a candidate for searched value
// in insert it's going to give a candidate for insertion
// point

void printTabs(int tabs){
	for(int i=0; i<tabs; i++)
		printf("\t");
}

void printTree(struct treeNode * root, int tabs){
	struct queue * q = initQueue();
	enq(q, root);
	struct treeNode * current;

	while(q->size > 0){
		current = deq(q);



	}

}

// failed recursive version
/*
void printTree(struct node * root, int tabs){
	printTabs(tabs);
	printf("%d\n", root->data);
	printTabs(tabs-1);
	printf("/");
	printTabs(2);
	printf("\\");
	printf("\n");

	if(root->left != NULL)
		printTree(root->left, tabs-1);

	if(root->right != NULL)
		printTree(root->right, tabs+1);
}
*/


int main(){
	struct bst * tp = createbst();
	insert(tp, 10);
	insert(tp, 9);
	insert(tp, 11);
	insert(tp, 12);
	insert(tp, 8);
	//struct node * s = search(tp, 3);
	printTree(tp->root, 4);
	return 0;


}
