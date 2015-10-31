all: sim refstr

sim: src/sim.h src/sim.c 2c clok fifo lru mm pcbl rrsched frame events scheduler
	gcc src/sim.c src/obj/2c.o src/obj/clok.o src/obj/fifo.o src/obj/lru.o src/obj/mm.o src/obj/pcbl.o src/obj/rrsched.o src/obj/frame.o src/obj/events.o src/obj/scheduler.o -o sim 

scheduler: src/scheduler.c src/scheduler.h
	gcc -c src/scheduler.c -o src/obj/scheduler.o

events: src/events.c src/events.h
	gcc -c src/events.c -o src/obj/events.o

frame: src/frame.c src/frame.h
	gcc -c src/frame.c -o src/obj/frame.o

2c: src/2c.h src/2c.c
	gcc -c src/2c.c -o src/obj/2c.o

clok: src/clok.c src/clok.h
	gcc -c src/clok.c -o src/obj/clok.o

fifo: src/fifo.c src/fifo.h
	gcc -c src/fifo.c -o src/obj/fifo.o

lru: src/lru.c src/lru.h
	gcc -c src/lru.c -o src/obj/lru.o

mm: src/mm.c src/mm.h
	gcc -c src/mm.c -o src/obj/mm.o

pcbl: src/pcbl.c src/pcbl.h
	gcc -c src/pcbl.c -o src/obj/pcbl.o

rrsched: src/rrsched.c src/rrsched.h
	gcc -c src/rrsched.c -o src/obj/rrsched.o

refstr: src/refstr.c src/refstr.h
	gcc src/refstr.c -o refstr

clean:
	rm src/obj/*.o
