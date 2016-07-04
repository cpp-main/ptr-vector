objects=ptr_vector.o test.o
target=test

CFLAGS+=-g

all:$(target)

$(target) : $(objects)
	gcc -o $@ $^

clean:
	-rm -f $(objects)
	-rm -f $(target)
