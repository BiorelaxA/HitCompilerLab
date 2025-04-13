lab1:
	bison -d -v syntax.y 
	flex Cmmlexer.l
	gcc -Iinclude lab1.c syntax.tab.c src/TreeNodes.c src/error.c src/SemanticInfo.c src/HashTable.c src/Stack.c -lfl -ly -o lab1
lab2:
	rm -f lab2
	bison -d -v syntax.y
	flex Cmmlexer.l
	gcc -g -DLAB2_ENABLE_HASH lab2.c syntax.tab.c src/TreeNodes.c src/error.c src/HashTable.c src/SemanticInfo.c src/Stack.c -lfl -ly -o lab2
lab3:
	bison -d -v syntax.y
	flex Cmmlexer.l
	gcc -g -DLAB2_ENABLE_HASH lab3.c syntax.tab.c src/TreeNodes.c src/error.c src/HashTable.c src/SemanticInfo.c src/Stack.c src/Intercode.c -lfl -ly -o lab3

cleanlab1:
	rm -f lab1
cleanlab2:
	rm -f lab2
cleanlab3:
	rm -f lab3