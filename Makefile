lab1:
	bison -d -v syntax.y 
	flex Cmmlexer.l
	gcc lab1.c syntax.tab.c src/TreeNodes.c src/error.c -lfl -ly -o lab1
lab2:
	rm -f lab2
	bison -d -v syntax.y
	flex Cmmlexer.l
	gcc -g lab2.c syntax.tab.c src/TreeNodes.c src/error.c src/HashTable.c src/SemanticInfo.c src/Stack.c -lfl -ly -o lab2

clean:
	rm -f lab2