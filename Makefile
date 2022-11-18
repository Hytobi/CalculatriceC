all : exec clean run

exec : main.o pile.o lecture.o
	gcc -o exec main.o pile.o lecture.o

main.o: main.c pile.h lecture.h rage.h
	gcc -c main.c

pile.o: pile.c pile.h
	gcc -c pile.c	

lecture.o: lecture.c lecture.h rage.h pile.h
	gcc -c lecture.c

clean:
	rm -f *.o

run: exec
	./exec