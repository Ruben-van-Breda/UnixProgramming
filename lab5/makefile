CC = gcc
CFLAGS = −o

rectangle : main.o area.o cost.o
	$(CC) $(CFLAGS) rectangle main.o area.o cost.o

main.o : main.c rectangle.h
	$(CC) -c main.c

area.o : area.c rectangle.h
	$(CC) -c area.c

cost.o : cost.c rectangle.h
	$(CC) -c cost.c

clean :
	rm -rf *.o rectangle


