all : clean program

main.o : main.c move.h
	gcc -c $< -o $@

move.o : move.c move.h
	gcc -c $< -o $@
render.o : render.c render.h
	gcc -c $< -o $@

program : main.o move.o render.o
	gcc $^ -o $@

clean : 
	del *.o *.exe