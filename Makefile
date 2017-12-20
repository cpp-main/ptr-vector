objects=ptr_vector.o str_vector.o test.o
target=test

CFLAGS+=-g -Wall

all:$(target)

$(target) : $(objects)
	gcc -o $@ $^

clean:
	-rm -f $(objects)
	-rm -f $(target)
