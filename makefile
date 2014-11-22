all: qompressor.cpp
	g++ qompressor.cpp HuffmanTree.cpp main.cpp -std=c++11 -o qpress

