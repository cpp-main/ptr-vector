objects=ptr_vector.o test.o
target=test

CFLAGS+=-g -Wall -std=c99

all:$(target)

$(target) : $(objects)
	gcc -o $@ $^

clean:
	-rm -f $(objects)
	-rm -f $(target)
