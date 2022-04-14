all: bison.tab lexer.l.c
	g++ -w -o kompilator bison.tab.cpp lexer.l.c codeGenerator.cpp Memory/lookupTab.cpp Conditions.cpp errorHandler.cpp Expressions.cpp Values.cpp

lexer.l.c: lexer.l
	flex -o lexer.l.c lexer.l

bison.tab: bison.ypp
	bison -d bison.ypp
