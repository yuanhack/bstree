#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include <time.h>

//---------- C source file ----------
/*
************************************************************
**
**  Author  :  fposkln
**  Date    :  07/25/2008|00:52:44
**  Comment :  testing BSTree
**
************************************************************
*/

int cmpNode(const void *p1,const void *p2){
	return *(int *)p1 - *(int*)p2;
}

_Bool printData(void *data){
	static int i=0;
	int rtn = printf("%10d ",*(int*)data) >= 0;
	if(i++ % 10 == 9)
		printf("\n");
	return rtn;
}

#include <errno.h>
#include <string.h>
int main(int argc,char ** argv)
{
	bstree_root *pTree = new_bstree(cmpNode, NULL);
	srand((unsigned)time(NULL));	
	int i;
	int x;
//store some rand number intger
	int max = 100;
	for(i=0; i< max; ++i){
		x = rand() % max;
		printf("rand: %d\n", x);
		if (bstree_insert(pTree,&x,sizeof(int)) == false) {
			printf("error: %s\n", strerror(errno));
		}
	}
	
	int count = 0;

//test LNR
	printf("...LNR...------------------------\n");
	count = bstree_inorder(pTree,printData);
	printf("^^^LNR^^^------------------------\n");

//test RNL
	printf("...RNL...------------------------\n");
	count = bstree_rev_inorder(pTree,printData);
	printf("^^^RNL^^^------------------------\n");

//test NLR
	printf("...NLR...------------------------\n");
	count = bstree_preorder(pTree,printData);
	printf("^^^NLR^^^------------------------\n");

//test LRN
	printf("...LRN...------------------------\n");
	count = bstree_postorder(pTree,printData);
	printf("^^^LRN^^^------------------------\n");

//test max node
	bstree_node * pMax = (bstree_node*) bstree_maxnode(pTree);
	printf("Max:%d\n", *(int*)(pMax->data));

//test min node
	bstree_node * pMin = (bstree_node*) bstree_minnode(pTree);
	printf("Min:%d\n", *(int*)(pMin->data));

	printf("Count:%d\n",count);
	bstree_clear(pTree);
	return 0;
}

