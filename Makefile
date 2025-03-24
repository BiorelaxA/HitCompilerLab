lab1:
	bison -d -v syntax.y 
	flex Cmmlexer.l
	gcc lab1.c syntax.tab.c src/TreeNodes.c src/error.c -lfl -ly -o scanner
