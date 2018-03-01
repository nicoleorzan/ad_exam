CXX = c++
CFLAGS = -std=c++11 -Wall -Wextra -fopenmp
IFLAGS = -I include
DFLAGS = -D DEBUG


all: main_test test/testlognikOMP $(EXE_TEST)


src/btree.o:  src/btree.cc 
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)


test/testlognikOMP: test/testlognikOMP.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)


test/testlognikOMP.o: test/testlognikOMP.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)


test/testlog: test/testlog.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)


test/testlog.o: test/testlog.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS)


main_test: main_test.o src/btree-d.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)


main_test.o: main_test.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)


src/btree-d.o: src/btree.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)


doc: Doxygen/Doxy
	doxygen $^


clean:
	@rm -rf *~ *.o src/*.o test/*.o html latex main_test test/testlognikOMP test/testlog

.PHONY: clean
