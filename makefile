.PHONY: all
all: build/liblist.a

build/liblist.a: build/list.o
	ar rcs $@ $<

build/list.o: src/list.c include/list.h
	gcc -c -I include $< -o $@

.PHONY: clean
clean:
	rm build/list.o build/liblist.a