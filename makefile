CC = gcc
libdd: libdependency.o hashtable.o
	${CC} -o libdd libdependency.o hashtable.o libdependency.h 
libdependency.o:libdependency.c
	${CC} -c -g libdependency.c libdependency.h
hashtable.o:hashtable.c
	${CC} -c -g hashtable.c libdependency.h
clean:
	rm -rf *.o