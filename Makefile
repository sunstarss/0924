 .PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=system.exe
OBJS=main.o User.o Session.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -std=c++0x
clean:
	rm -f *.o $(BIN)
