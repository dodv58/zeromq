.PHONY: all clean

all: master worker sink

master: master.c
	gcc -o master master.c -lzmq

worker: worker.c
	gcc -o worker worker.c -lzmq

sink: sink.c
	gcc -o sink sink.c -lzmq

clean:
	rm -f master worker sink

