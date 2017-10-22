all: dispersa

# Regla para el programa principal
dispersa: dispersa.o
	gcc -o dispersa dispersa.o

dispersa.o: dispersa.c dispersa.h
	gcc -c dispersa.c

clean:
	rm -f dispersa *.o