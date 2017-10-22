CC=gcc
CFLAGS=-I.
HEADS=command_parser.h commands.h environment.h expressions.h file_processing.h headers.h process_handler.h string_processing.h process_handler.h variables.h
OBJ=main.o file_processing.o environment.o variables.o command_parser.o expressions.o commands.o expressions.o process_handler.o string_processing.o
LIBS=-lm

%.o: %.c $(HEADS)
	$(CC) -c -o $@ $< $(CFLAGS)


shellbe: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o shellbe
