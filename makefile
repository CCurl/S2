app := s2

CC := clang
CCFLAGS := -m32 -O3 -DIS_LINUX

srcfiles := s2.c
LDLIBS   := 

all: $(app)

$(app): $(srcfiles) $(incfiles)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(app) $(srcfiles) $(LDLIBS)
	ls -l $(app)

clean:
	rm -f $(app)

bin: $(app)
	cp -u -p $(app) ~/bin/
