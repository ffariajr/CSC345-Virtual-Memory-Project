all: sim refstr

sim: sim.h sim.c 2c clock fifo lru mm pcbl proc rrsched scheduler
	gcc sim.c 2c.o clock.o fifo.o lru.o mm.o pcbl.o proc.o rrsched.o scheduler.o -o sim 

scheduler: scheduler.c scheduler.h
	gcc -c scheduler.c -o scheduler.o

2c: 2c.h 2c.c
	gcc -c 2c.c -o 2c.o

clock: clock.c clock.h
	gcc -c clock.c -o clock.o

fifo: fifo.c fifo.h
	gcc -c fifo.c -o fifo.o

lru: lru.c lru.h
	gcc -c lru.c -o lru.o

mm: mm.c mm.h
	gcc -c mm.c -o mm.o

pcbl: pcbl.c pcbl.h
	gcc -c pcbl.c -o pcbl.o

proc: proc.c proc.h
	gcc -c proc.c -o proc.o

rrsched: rrsched.c rrsched.h
	gcc -c rrsched.c -o rrsched.o

refstr: refstr.c refstr.h
	gcc refstr.c -o refstr

clean:
	rm *~ *.o
