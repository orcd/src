
cfiles = $(shell find -name "*.c")
efiles = $(patsubst %.c,%.bin,${cfiles})

all: ${efiles}

%.bin: %.c
	gcc $^ -o $@

clean:
	rm *.bin
