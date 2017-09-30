CC = gcc
CFLAGS =
HEADERS = mytoc.h
OBJECTS = shell.o mytoc.o util.o
default: all
all: ush
ush: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
	rm -f ush
.PHONEY: all clean