CC = gcc
CFLAGS = -o

my_shell : assign2_19200704.o my_commands.o
	$(CC) $(CFLAGS) my_shell assign2_19200704.o my_commands.o

assign2_19200704.o : assign2_19200704.c my_shell.h
	$(CC) -c assign2_19200704.c

my_commands.o : my_commands.c my_shell.h
	$(CC) -c my_commands.c

# clean :
# 	rm -rf *.o my_shell