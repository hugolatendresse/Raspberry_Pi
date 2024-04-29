all: first start

first: first.o
	gcc -o $@ $+

first.o: first.s
	as -o $@ $<

start: start.o
	gcc -o $@ $+

start.o: start.s
	as -o $@ $<

clean:
	rm -vf first start *.o
