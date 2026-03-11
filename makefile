ARCH ?= 64

CC := clang
CCFLAGS := -m$(ARCH) -O3 -DIS_LINUX

srcfiles := s2.c
LDLIBS   := 

all: s2

s2: $(srcfiles) $(incfiles)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o s2 $(srcfiles) $(LDLIBS)
	ls -l s2

run: s2
	./s2

test: s2
	./s2 tests

clean:
	rm -f s2

bin: s2
	cp -u -p s2 ~/bin/
