all: sim refstr

sim: sim.h sim.c 2c clok fifo lru mm pcbl rrsched frame events scheduler
	gcc sim.c 2c.o clok.o fifo.o lru.o mm.o pcbl.o rrsched.o frame.o events.o scheduler.o -o sim 

scheduler: scheduler.c scheduler.h
	gcc -c scheduler.c -o scheduler.o

events: events.c events.h
	gcc -c events.c -o events.o

frame: frame.c frame.h
	gcc -c frame.c -o frame.o

2c: 2c.h 2c.c
	gcc -c 2c.c -o 2c.o

clok: clok.c clok.h
	gcc -c clok.c -o clok.o

fifo: fifo.c fifo.h
	gcc -c fifo.c -o fifo.o

lru: lru.c lru.h
	gcc -c lru.c -o lru.o

mm: mm.c mm.h
	gcc -c mm.c -o mm.o

pcbl: pcbl.c pcbl.h
	gcc -c pcbl.c -o pcbl.o

rrsched: rrsched.c rrsched.h
	gcc -c rrsched.c -o rrsched.o

refstr: refstr.c refstr.h
	gcc refstr.c -o refstr

clean:
	rm *~ *.o
