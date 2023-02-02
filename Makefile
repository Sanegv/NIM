run: compile
	./main

compile: main.o fonctions.o AI.o
	gcc -Wall -o main main.o fonctions.o AI.o -g

main.o: main.c fonctions.o AI.o
	gcc -Wall -c main.c fonctions.h fonctions.c AI.c AI.h -g

AI.o: AI.h AI.c AI.o
	gcc -Wall -c AI.c AI.h fonctions.c fonctions.h -g

fonctions.o: fonctions.h fonctions.c
	gcc -Wall -c fonctions.h fonctions.c -g

clean: 
	rm *.o
	rm *.gch

valgrind: compile
	valgrind ./main
