
cfiles = $(shell ls *.c)
efiles = $(patsubst %.c,%.bin,${cfiles})

all: ${efiles}

%.bin: %.c
	gcc $^ -o $@ -g -lpthread -levent_core


clean:
	rm *.bin
