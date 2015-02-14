#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

#define LEN_MAX 1000
char buffer [LEN_MAX];

_Bool printData(void* pData)
{ 
	return printf("%s", (char*)pData) >= 0;
}

int main(int argc,char ** argv){
	bstree_root *pStrTree = new_bstree( (CmpFunc_t*)strcmp, NULL );
	int n;
	while( fgets(buffer, LEN_MAX, stdin ) != NULL ){
		size_t len = strlen( buffer );
		if( bstree_insert( pStrTree, buffer, len+1 ) );
		else break;
	}
	if( !feof(stdin) ){
		fprintf( stderr, "%s: Error reading or storing text input.\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	n = bstree_inorder(pStrTree,printData);
	fprintf(stdout, "\nsortlines: print %d lines.\n",n);
	bstree_clear(pStrTree);
	return 0;
}

