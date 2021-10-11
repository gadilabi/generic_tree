#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"
#include "bst_generic.h"

struct bst * createbst(int dataType, int cmpCB(void * vp1, void * vp2), void printCB(void * value)){
	struct bst * bstp = (struct bst *) malloc(sizeof(struct bst));
	bstp->root = NULL;
	bstp->dataType = dataType;
	bstp->size = 0;
	bstp->cmpCB = cmpCB;
	bstp->printCB = printCB;

	return bstp;
}


struct treeNode * createTreeNode(struct bst * tp, void * dp){
	struct treeNode * newNode = (struct treeNode *) malloc(sizeof(struct treeNode));
	newNode->data = malloc(tp->dataType);
	memcpy(newNode->data, dp, tp->dataType);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}

struct treeNode * searchEntry(struct treeNode * root,void * value, int cmpCallback(void * v1, void * v2)){
	// search has ended and value found
	// insertion should be denied since no duplicates
	// are allowed in bst
	if(cmpCallback(value, root->data)==0)
		return root;

	if(cmpCallback(root->data, value) > 0){
		if(root->left==NULL)
			return root;
		else
			return searchEntry(root->left, value, cmpCallback);
	}

	if(cmpCallback(root->data, value) < 0){
		if(root->right==NULL)
			return root;
		else
			return searchEntry(root->right, value, cmpCallback);
	}
	 return NULL;

}

void treeInsert(struct bst * tp, void * value){
	struct treeNode * newNode = createTreeNode(tp, value);

	// if the tree is empy set as root
	if(tp->root == NULL){
		tp->root = newNode;
		return;
	}

	// find i nsertion point fit for value
	struct treeNode * candidate = searchEntry(tp->root, value, tp->cmpCB);

	// if the value is already in tree do nothing
	if(tp->cmpCB(candidate->data, value)==0)
		return;

	// if value is smaller add to left
	if(tp->cmpCB(candidate->data, value)>0)
		candidate->left = createTreeNode(tp, value);

	// if value is larger add to right
	if(tp->cmpCB(candidate->data, value)<0)
		candidate->right = createTreeNode(tp, value);

	// inc tree size
	tp->size++;
}

struct treeNode * search(struct bst * tp, void * value){
	  struct treeNode * candidate = searchEntry(tp->root, value, tp->cmpCB);

	  if(tp->cmpCB(candidate->data, value)==0)
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

/*

void printTree(struct bst * tp, struct treeNode * root, int tabs){
	struct queue * q = initQueue(sizeof(struct treeNode));
	struct queue * tabq = initQueue(sizeof(int));
	enq(q, root);
	struct treeNode * current;

	// count iterations
	int counter = 1;

	// iterations per level of tree
	int nodesPerLevel[tp->size];
	nodesPerLevel[0] = 1;

	// number of tabs away from center for first
	// node on the next level
	int mostLeft = 0;

	int isMostLeft = true;

	// the tree level
	int level = 0; 

	// is node first in level?
	bool isFirst = false; 
	
	//traverse tree breadth first
	while(q->size > 0){

		// get node of queue
		current = (struct treeNode *) deq(q);

		// advance a level in tree?
		if(counter>=nodesPerLevel[level]){
			level++;
			nodesPerLevel[level] = counter;
			counter = 0;
			isFirst = true;
		}

		if(level > 0 && isFirst) // first node not the root
			printTabs(tabs - nodesPerLevel[level-1]);
		else if(level>0) // any node which is not root
			printTabs(2);
		else //root
			printTabs(tabs);

		// print data
		tp->printCB(current->data);

		// deflag
		isFirst = false;

		// enq children
		if(current->left != NULL){
			enq(q, current->left);
			counter++;
		}

		if(current->right != NULL){
			enq(q, current->right);
			counter++;
		}


	}

}
*/
int getTreeHeight(struct treeNode * root){
	
	if(root==NULL)
		return 0;

	if(isLeaf(root))
		return 1;

	return 1+ max(getTreeHeight(root->left), getTreeHeight(root->right));

}

struct treeNodeDescription * createDesc(int indentation, void * data){
	struct treeNodeDescription * tdp = malloc(sizeof(struct treeNodeDescription));

	tdp->indentation = indentation;
	tdp->data = data;

	return tdp;

}

void getDescriptions(struct treeNode * root, struct queue * treeArray[], int level, int indentation){
	enq(treeArray[level], createDesc(indentation, root->data));
	if(root->left != NULL)
		getDescriptions(root->left, treeArray, level+1, indentation-1);

	if(root->right != NULL)
		getDescriptions(root->right, treeArray, level+1, indentation+1);


}

void printTree(struct bst * tp){

	// get height of tree
	int height = getTreeHeight(tp->root);
	
	// create an array with numRows=height
	struct queue * treeArray[height];
	
	// populate array with queues each reps a level of the tree
	for(int i=0; i<height; i++){
		treeArray[i] = initQueue(sizeof(struct treeNodeDescription));
	}
	
	// traverse tree recursively and populate the array
	// with a treeNodeDescription
	getDescriptions(tp->root,treeArray, 0, 0);
	
	void * current;
	int value;
	int baseIndent = 3;
	int currentIndent;
	int formerIndent;
	int netIndent;
	int qCounter = 0;

	// travers array and print the tree
	for(int i=0; i<height; i++){
		formerIndent = 0;
		qCounter = 0;
		while(treeArray[i]->size > 0){
			current = deq(treeArray[i]);
			value = * (int *) ((struct treeNodeDescription *) current)->data; 

			currentIndent =  ((struct treeNodeDescription *) current)->indentation; 

			if(qCounter==0){
				netIndent = baseIndent + currentIndent;
			}else{
				netIndent = currentIndent - formerIndent;
			}

			printTabs(netIndent);
			printf("%d", value);
			formerIndent = currentIndent;
			qCounter++;

		}
		printf("\n");
		
		

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
void printTreeValue(struct bst * tp, struct treeNode * root)
{
	tp->printCB(root->data);
	if(root->left != NULL)
		printTreeValue(tp, root->left);

	if(root->right != NULL)
		printTreeValue(tp, root->right);

}

bool isLeaf(struct treeNode * node){
	if(node->left==NULL && node->right==NULL)
		return true;
	else
		return false;
}

int max(int a, int b){
	if(a>b)
		return a;
	else 
		return b;

}


void printNumber(void * num){
	printf("%d\n", * (int *) num);
}

int cmpInt(void * vp1, void * vp2){
	int v1 = * (int *) vp1;
	int v2 = * (int *) vp2;

	if(v1>v2) return 1;
	if(v1==v2) return 0;
	if(v1<v2) return -1;

	return 0;


}

int main(){
	struct bst * tp = createbst(sizeof(int), cmpInt, printNumber);

	int a[] = {10,12,15,14,3,17,1,2};
	for(int i=0; i<8; i++){
		treeInsert(tp, &a[i]);
	}
	printTree(tp);
	//printTree(tp, tp->root, 4);
	//printf("%d",sizeof( deq(q)));
	//printf("%d", * (int *) tp->root->data );
	//struct node * s = search(tp, 3);
	//printTreeValue(tp, tp->root);
	return 0;


}
