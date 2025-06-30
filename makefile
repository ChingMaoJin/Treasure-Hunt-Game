CC=gcc
CFLAGS=-Wall -ansi -pedantic -g
OBJ=Game.o GameMain.o DarkMode.o
EXEC=treasure

ifdef DARK
CFLAGS += -DDARK_MODE #define the macro DARK_MODE and append it to CFLAGS
endif

$(EXEC):$(OBJ)
		$(CC) $(OBJ) -o $(EXEC)

GameMain.o:GameMain.c Game.h DarkMode.h
		$(CC) -c GameMain.c $(CFLAGS)

Game.o:Game.c Game.h DarkMode.h
		$(CC) -c Game.c $(CFLAGS)

DarkMode.o:Game.h DarkMode.h DarkMode.c
		$(CC) -c DarkMode.c $(CFLAGS)

clean:
		rm -f $(EXEC) $(OBJ)