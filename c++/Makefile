EXE=main_int
CXX=c++
CFLAGS=-g -std=c++11 -Wall -Wextra
IFLAGS=-I include
SRC= src/btree.cc


all: $(EXE)

main_int:main_int.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

doc: Doxy
	doxygen $^

src/btree.o:  $(SRC) 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

main_int.o:main_int.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

clean:
	@rm -rf *~ *.o src/*.o html latex #$(EXE)

.PHONY: clean
