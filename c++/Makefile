EXE = main_int.x test/testlog.x
CXX = c++
CFLAGS = -g -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D DEBUG
SRC = src/btree.cc


all: $(EXE)

main_int: main_int.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

#%.x: %.o src/btree.o
#	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

doc: Doxygen/Doxy
	doxygen $^

src/btree.o:  $(SRC) 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

main_int.o: main_int.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

#%.o: %.cc
#	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

clean:
	@rm -rf *~ *.o src/*.o html latex $(EXE)

.PHONY: clean
