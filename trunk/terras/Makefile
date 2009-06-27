# terras Makefile
CC := gcc

#LIBDIRS := -I/usr/include
LIBS := -lSDL -lGLU -lGL -lSDL_image -lyaml
CFLAGS := -Wall -g $(LIBDIRS)
LDFLAGS := -lm  $(LIBS)



%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

all: terras

terras: terras.o view.o controller.o model.o sdltextures.o node.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf terras *.o

.PHONY: clean all