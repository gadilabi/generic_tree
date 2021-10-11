struct treeNodeDescription{
	int indentation;
	void * data;

};

struct treeNode{
	void * data;
	struct treeNode * left;
	struct treeNode * right;
};

struct bst{
	struct treeNode * root;
	int size;
	int dataType;
	int (*cmpCB)(void * vp1, void * vp2);
	void (* printCB)(void * value);
};

struct bst * createbst(int dataType, int cmpCB(void * vp1, void * vp2), void printCB(void * value));
struct treeNode * createTreeNode(struct bst * tp, void * dp);
struct treeNode * searchEntry(struct treeNode * root,void * value, int cmpCallback(void * v1, void * v2));
void treeInsert(struct bst * tp, void * value);
struct treeNode * search(struct bst * tp, void * value);
void printTabs(int tabs);
int getTreeHeight(struct treeNode * root);
struct treeNodeDescription * createDesc(int indentation, void * data);
void getDescriptions(struct treeNode * root, struct queue * treeArray[], int level, int indentation);
void printTree(struct bst * tp);
void printTreeValue(struct bst * tp, struct treeNode * root);
bool isLeaf(struct treeNode * node);
int max(int a, int b);
