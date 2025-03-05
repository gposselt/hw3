CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: heap-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

llrec-test: llrec-test.cpp llrec.o heap.o
	$(CXX) $(CXXFLAGS) llrec-test.cpp -o $@ llrec.o heap.o

heap-test: heapTests.cpp heap.o
	$(CXX) $(CXXFLAGS) heapTests.cpp -o $@ heap.o

llrec.o: llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#makes CLion do intellisense
heap.o: heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 