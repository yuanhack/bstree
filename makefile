CC = gcc
MACRO = -Wall -g



test: *.c *.h
	gcc $(MACRO) bstree.c  test_bstree.c -o test_bstree
	gcc $(MACRO) bstree.c  sort_line.c -o sort_line

clean:
	rm -rf test_bstree sort_line

