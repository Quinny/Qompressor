#include "qompressor.h"
#include "HuffmanTree.h"
#include <iostream>

int main(int argc, char **argv){
	std::string usage = "Usage: qpress [-d] <filename>\n"
						"-d to decompress\n"
						"no option to compress\n";
	if(argc == 1){
		std::cout << usage;
		return 0;
	}
	std::string option = argv[1];

	if(option == "-d"){
		if(argc != 3){
			std::cout << usage;
			return 0;
		}
		std::string filename = argv[2];
		qompressor::decompress(filename);
	}
	else
		qompressor::compress(argv[1]);

	return 0;
}
