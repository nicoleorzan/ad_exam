EXE = main_int.x test/testlog.x
CXX = c++
CFLAGS = -g -std=c++11 -Wall -Wextra
IFLAGS = -I include
# DFLAGS = -D DEBUG
SRC = src/btree.cc


all: $(EXE)

testlognik: testlognik.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

testlognikOMP: testlognikOMP.o src/btree.o
	$(CXX) -fopenmp -o $@ $^ $(CFLAGS) $(IFLAGS) -O0

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

testlognik.o: testlognik.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

testlognikOMP.o: testlognikOMP.cc
	$(CXX) -c -fopenmp -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS) -O0
#%.o: %.cc
#	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)

clean:
	@rm -rf *~ *.o src/*.o html latex $(EXE)

.PHONY: clean
