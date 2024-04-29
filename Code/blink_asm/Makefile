all: first start read_gpio write_gpio

first: first.o
	gcc -o $@ $+

first.o: first.s
	as -o $@ $<

start: start.o
	ld -o $@ $+ --nostdlib

start.o: start.s
	as -o $@ $<

read_gpio: read_gpio.c
	gcc -o read_gpio read_gpio.c

write_gpio: write_gpio.c
	gcc -o write_gpio write_gpio.c

clean:
	rm -vf first read_gpio write_gpio  start *.o
