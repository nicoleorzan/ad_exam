CXX=c++
CFLAGS=-std=c++11 -Wall -Wextra
IFLAGS=-I include

all:main

main:main.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)


src/btree.o: src/btree.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

main.o:main.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

clean:
	@rm -f *~ *.o src/*.o

.PHONY: clean
