#ifndef __RCYH_BSTREE_H__
#define __RCYH_BSTREE_H__
//#This is a BSTree
//#	Page:176
//#     Date:08/08/07
#include <stdbool.h>
#include <string.h>


typedef struct bstree_node{
	struct bstree_node *left, *right;
	size_t size;
	char data[];
}bstree_node;

typedef const void * GetKeyFunc_t ( const void *pData );
typedef int CmpFunc_t ( const void * pKey1, const void * pKey2 );

typedef struct {
	struct bstree_node* pRoot;
	CmpFunc_t	*cmp;
	GetKeyFunc_t 	*getKey; 

}bstree_root;

bstree_root* new_bstree( CmpFunc_t* cmp, GetKeyFunc_t* getKey);
_Bool bstree_insert( bstree_root *pBST, const void *pData, size_t size );
const void *bstree_search( bstree_root *pBST, const void *pKey );
_Bool bstree_erase( bstree_root* pBST, const void *pKey);
void bstree_clear( bstree_root* pBST );

int bstree_inorder( bstree_root* pBST, _Bool(*action)( void* pData ));
int bstree_rev_inorder( bstree_root *pBST, _Bool(*action)( void *pData ));
int bstree_preorder( bstree_root* pBST, _Bool(*action)( void *pData ));
int bstree_postorder( bstree_root *pBST,_Bool(*action)( void *pData ));


const bstree_node * bstree_maxnode( bstree_root *pBST );
const bstree_node * bstree_minnode( bstree_root *pBST );


#endif /* __RCYH_BSTREE_H__ */
