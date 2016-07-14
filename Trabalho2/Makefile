all: build

build:
	g++ -o mps *.cpp -Wall -Wextra -pedantic -std=c++11 -O2 -g #fast -march=native -unroll-loops

clean:
	rm mps
	rm ManPages.dat
	rm InvertedIndex.dat
	rm ManPages.tree
	rm Index.tree