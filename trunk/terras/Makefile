# terras Makefile
CC := gcc


INCDIRS := -Ilibs/yaml-cpp/include
LIBDIRS := 
LIBS := -lm -lSDL -lGLU -lGL -lSDL_image libs/yaml-cpp/libyaml-cpp.a
CFLAGS := -Wall -g $(INCDIRS)
LDFLAGS := $(LIBDIRS) $(LIBS)



%.o: %.cpp *.h
	$(CC) -c $(CFLAGS) $< -o $@

all: terras

terras: terras.o view.o controller.o model.o sdltextures.o node.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf terras *.o

.PHONY: clean all