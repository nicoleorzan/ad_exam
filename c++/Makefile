EXE = main_int.x 
EXE_TEST = test/testlog.x test/testlog_before.x test/testlog_after.x
CXX = c++
CFLAGS = -g -std=c++11 -Wall -Wextra
IFLAGS = -I include
# DFLAGS = -D DEBUG
SRC = src/btree.cc


all: $(EXE) $(EXE_TEST) 

testlognik: testlognik.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

testlognikOMP: testlognikOMP.o src/btree.o
	$(CXX) -fopenmp -o $@ $^ $(CFLAGS) $(IFLAGS) -O0

main_int: main_int.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS) $(DFLAGS)

#%.x: %.o src/btree.o
#	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

%.x: %.o src/btree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS) -fopenmp -O0

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

%.o: %.cc
	$(CXX) -c -o $@ $^ $(CFLAGS) $(IFLAGS) -fopenmp -O0

clean:
	@rm -rf *~ *.o src/*.o html latex $(EXE) $(EXE_TEST)

.PHONY: clean
