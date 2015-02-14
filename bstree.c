 
//#This is a BSTree
//#	Page:176
//#     Date:08/08/07
#include "bstree.h"
#include <stdlib.h>

const void * defaultGetKey ( const void *pData ) { return pData; }

//创建二叉树
bstree_root * new_bstree ( CmpFunc_t * cmp, GetKeyFunc_t* getKey ) 
{
	bstree_root * pBST = NULL;
	if  ( cmp ) {
		pBST = malloc ( sizeof ( bstree_root ) ) ;
	}
	if  ( pBST ) {
		pBST->pRoot = NULL;
		pBST->cmp = cmp;
		pBST->getKey =   getKey != NULL  ? getKey : defaultGetKey;
	}
	return pBST;
}

//插入pData辅助
static _Bool insert  ( bstree_root *pBST, bstree_node **ppNode, const void *pData, size_t size ) 
{
	bstree_node * pNode = *ppNode;  //ppNode是指向子树根节点的,新的节点插入此子树
	if  ( pNode == NULL ) {		
		pNode = malloc ( sizeof ( bstree_node ) + size ) ;
		if  ( pNode != NULL ) {
			pNode->left = pNode->right = 0;
			memcpy ( pNode->data, pData, size ) ;
			*ppNode = pNode;
			return true;
		}
		else
			return false;
	}
	else {
	const void 
		*key1 = pBST->getKey ( pData ) ,
		*key2 = pBST->getKey ( pNode->data ) ;
	//比较两个键值,如果当前需要插入的数据比"根"小,则从左边递归继续,否则右边
	if  ( pBST->cmp ( key1,key2 ) < 0 ) 
		return insert ( pBST,& ( pNode->left ) ,pData,size ) ;
	else
		return insert ( pBST,& ( pNode->right ) ,pData,size ) ;
	}
}

//插入pDate
_Bool bstree_insert ( bstree_root *pBST, const void *pData, size_t size ) 
{
	if  ( !pBST || !pData || !size ) 
		return false;
	return insert ( pBST,& ( pBST->pRoot ) ,pData,size ) ;	
}

//查找pKey辅助
static const void * search ( bstree_root *pBST, const bstree_node *pNode, const void *pKey ) 
{
	if  ( ! pNode ) 
		return 0;
	int res_cmp = pBST->cmp ( pKey, pBST->getKey ( pNode->data ) ) ; 	
		
	if  ( res_cmp == 0 ) 
		return pNode->data;
	else if  ( res_cmp < 0 ) 
		return search ( pBST, pNode->left,  pKey ) ;	
	else
		return search ( pBST, pNode->right, pKey ) ;	
	
}

//查找pKey, 务必不可去修改作为key的值，那样会对树的结构造成破坏
const void * bstree_search ( bstree_root * pBST, const void * pKey ) 
{
	if  ( ! pBST || ! pKey ) 
		return 0;
	return search ( pBST, pBST->pRoot, pKey ) ;
}

//删除树辅助
static void clear ( bstree_node *pNode ) 
{
	if  ( pNode ) {
		clear ( pNode->left ) ;
		clear ( pNode->right ) ;
		free  ( pNode ) ;
	}
}

//删除树
void bstree_clear ( bstree_root *pBST ) 
{
	if  ( pBST ) {
		clear ( pBST->pRoot ) ;
		pBST->pRoot = NULL;
	}
}

//删除有
static bstree_node * detachMin ( bstree_node ** ppNode ) 
{
	bstree_node * pNode = *ppNode;
	if  ( pNode == NULL ) 
		return NULL;
	else if  ( pNode->left != NULL ) 
		return detachMin ( & ( pNode->left ) ) ;
	else {
		*ppNode = pNode->right;
		return pNode;
	}
}

//删除pKey节点辅助
static _Bool erase ( bstree_root *pBST, bstree_node **ppNode, const void *pKey ) 
{
	bstree_node * pNode = *ppNode;
	if  ( ! pNode ) 
		return false; 
	int res_cmp = pBST->cmp ( pKey ,pBST->getKey ( pNode->data ) ) ;
	
	if  ( res_cmp < 0 ) 
		return erase  ( pBST, & ( pNode->left ) , pKey ) ;
	else if  ( res_cmp > 0 ) 
		return erase  ( pBST, & ( pNode->right ) , pKey ) ;
	else {
		if  ( pNode->left == NULL ) 
			*ppNode = pNode->right;
		else if  ( pNode->right == NULL ) {
			*ppNode = pNode->left;	
		}
		else {
			bstree_node *pRightMin = detachMin ( & ( pNode->right ) ) ;
			*ppNode = pRightMin;
			pRightMin->left = pNode->left;
			pRightMin->right = pNode ->right;
		}
		free ( pNode ) ;
		return true;
	}
}

//删除pKey节点
_Bool bstree_erase ( bstree_root* pBST, const void *pKey ) 
{
	if  ( ! pBST || ! pKey ) 	
		return false;
	return erase ( pBST, & ( pBST->pRoot ) , pKey ) ;
}


//获取最小节点辅助
static bstree_node * minnode ( bstree_node *pNode ) 
{
	if  ( pNode == NULL ) 
		return NULL;
	else if  ( pNode->left != NULL ) 
		return minnode ( pNode->left ) ;
	else {
		return pNode;
	}

}

//获取最小节点指针
const bstree_node * bstree_minnode ( bstree_root *pBST ) 
{
	if  ( pBST != NULL ) 
		return minnode ( pBST->pRoot ) ;
	return NULL;
}
//获取最大节点辅助
static bstree_node *maxnode ( bstree_node *pNode ) 
{
	if  ( pNode == NULL ) 
		return 0;
	else if  ( pNode->right  != NULL ) 
		return maxnode ( pNode->right ) ;
	else
		return pNode;
}

//获取最大节点指针
const bstree_node * bstree_maxnode ( bstree_root *pBST ) 
{
	if  ( pBST != NULL ) 
		return maxnode ( pBST->pRoot ) ;
	return NULL;
}


//中序遍历辅助
static int inorder ( bstree_node* pNode, _Bool ( *action ) ( void *pData ) ) 
{
	int count = 0;
	if  ( pNode == NULL ) 
		return 0;
	count = inorder ( pNode->left, action ) ;
	if  ( action  ( pNode->data ) ) 
		++count;
	count += inorder ( pNode->right,action ) ;
	return count;
}

// LNR
int bstree_inorder ( bstree_root * pBST, _Bool ( * action ) ( void *pData ) ) 
{
	if  ( ! pBST ||action == NULL ) 
		return 0;
	else 
		return inorder ( pBST->pRoot, action ) ;

}

//前序遍历辅助
static int preorder ( bstree_node *pNode, _Bool ( *action ) ( void * pData ) ) 
{
	int count = 0;
	if  ( pNode == NULL ) 
		return 0;
	if  ( action ( pNode->data ) ) 
		++count;
	count += preorder ( pNode->left ,action ) ;
	count += preorder ( pNode->right,action ) ;
	return count;
}

//NLR
int bstree_preorder ( bstree_root *pBST, _Bool ( *action ) ( void* pData ) ) 
{
	if  ( ! pBST || ! action ) 
		return 0;
	return preorder ( pBST->pRoot, action ) ;
}


//后序遍历辅助
static int postorder ( bstree_node *pNode, _Bool ( *action ) ( void* pData ) ) 
{
	int count = 0;
	if  ( pNode == NULL ) 
		return 0;
	count += postorder ( pNode->left, action ) ;
	count += postorder ( pNode->right,action ) ;
	if  ( action ( pNode->data ) ) 	
		++count;
	return count;
}

//LRN
int bstree_postorder ( bstree_root *pBST, _Bool ( *action ) ( void* pData ) ) 
{
	if  ( ! pBST || ! action ) 
		return 0;	
	return postorder ( pBST->pRoot, action ) ;
}

//右中左遍历辅助
static int rev_inorder ( bstree_node *pNode, _Bool ( *action ) ( void* pData ) ) 
{
	int count = 0;
	if  ( pNode == NULL ) 
		return 0;
	count += rev_inorder ( pNode->right,action ) ;
	if  ( action ( pNode->data ) ) 
		++count;	
	count += rev_inorder ( pNode->left, action ) ;
	return count;
}

//RNL
int bstree_rev_inorder ( bstree_root *pBST, _Bool ( *action ) ( void *pData ) ) 
{
	if  ( pBST == NULL ) 
		return 0;
	return rev_inorder ( pBST->pRoot, action ) ;
}



