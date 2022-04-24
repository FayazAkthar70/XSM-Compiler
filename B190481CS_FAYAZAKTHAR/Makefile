cdmake:
	byacc -d -v -t parser.y
	lex rules.l
	gcc lex.yy.c y.tab.c LST.c AST.c codegen.c LAT.c -g -o test1
	./test1 < $(input)
	lex LAT.l
	gcc lex.yy.c
	./a.out

