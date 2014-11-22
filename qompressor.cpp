#include "qompressor.h"
#include <iostream>
#include "HuffmanTree.h"

namespace qompressor{

trans_table compress(std::string const& filename){
	HuffmanTree h = HuffmanTree::make(filename);
	trans_table t = h.translation_table();
	std::ifstream in(filename);
	std::fstream out(filename + ".qzip", std::ofstream::out | std::ofstream::trunc);
	write_key(t, out);
	std::string tmp;
	while(!in.eof()){
		tmp = get_token(in);
		out << t[tmp];
	}
	out.close();
	in.close();
	return t;
}

void decompress(std::string const& filename){
	std::string tmp;
	char c;
	std::ifstream in(filename);
	if(!in){
		std::cout << "Error reading file" << std::endl;
		exit(0);
	}
	trans_table reverse = read_key(in);
	std::fstream out(filename + ".qunzipped", std::ofstream::out | std::ofstream::trunc);
	while(!in.eof()){
		while(reverse.find(tmp) == reverse.end()){
			in >> c;
			tmp += c;
		}
		out << reverse[tmp];
		tmp.clear();
	}
	in.close();
	out.close();
}

std::string get_token(std::ifstream& f){
	std::string s;
	char c;
	int place = f.tellg();
	place++;
	f >> c;
	s += c;
	while(is_letter(c) && f >> std::noskipws >> c){
		if(is_letter(c))
			s += c;
		else
			f.seekg(place);
		place = f.tellg();
	}
	return s;
}

bool is_letter(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void write_key(trans_table const& t, std::fstream& f){
	f << t.size() << DELIMETER;
	for(auto i:t)
		f << i.second.size() << DELIMETER << i.second << i.first.size() << DELIMETER << i.first;
}

std::string read_chars(std::ifstream &f, int n){
	char c;
	std::string s;
	for(int i = 0; i < n; i++){
		f >> std::noskipws >> c;
		s += c;
	}
	return s;
}

trans_table read_key(std::ifstream &f){
	char c;
	int tableN;
	int len;
	std::string first;
	std::string second;
	trans_table reverse;
	f >> tableN; // get table size
	f >> c; // kill delimeter
	for(int i = 0; i < tableN; i++){
		f >> len; // first string length
		f >> c; // kill delimeter
		first = read_chars(f, len);
		f >> len; // second string length
		f >> c; // kill delimeter
		second = read_chars(f, len);
		reverse[first] = second;
	}
	return reverse;
}

}