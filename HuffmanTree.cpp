#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <random>
#include <queue>

namespace qompressor{

int HuffmanTree::opt_size(freq_table const& f) const {
	int n = f.size();
	for(int i = 36; i >= 2; i--){
		if(n % (i - 1) == 0) return i;
	}
	return 2; 
}

trans_table HuffmanTree::translation_table() const {
	trans_table t;
	fill_table(root_, "", t);
	return t;
}

void HuffmanTree::fill_table(HuffmanNode root, std::string seq, trans_table& t) const {
	if(root.is_leaf())
		t[root.word_] = seq;

	for(int i = 0; i < root.children_.size(); i++)
		fill_table(root.children_[i], seq + get_char(i), t);
}

freq_table HuffmanTree::frequency_table(std::string const& filename) const {
	std::ifstream f(filename);
	if(!f){
		std::cout << "Error reading file" << std::endl;
		exit(0);
	}
	freq_table t;
	std::string word;
	while(!f.eof()){
		word = get_token(f);
		if(t.find(word) == t.end())
			t[word] = 1;
		else
			t[word]++;
	}
	f.close();
	return t;
}

std::string HuffmanTree::get_char(int n) const {
	if(n <= 9) return std::to_string(n);
	char c = 'a' - (10 - n);
	std::string s;
	return s + c;
}

HuffmanNode HuffmanTree::make_tree(freq_table& freq) const {
	std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, CompareNode> trees;
	while(opt_size(freq) < 20) // Force a tree of size 20
		freq[random_string(16)] = 0;
	int n = opt_size(freq);
	for(auto i:freq)
		trees.push(HuffmanNode(i.first, i.second));

	while(trees.size() > 1){
		std::vector<HuffmanNode> smallest;
		for(int i = 0; i < n && !trees.empty(); i++){
			smallest.push_back(trees.top());
			trees.pop();
		}
		HuffmanNode parent(smallest);
		trees.push(parent);
	}
	return trees.top();
}

std::string HuffmanTree::random_string(int n) const {
	std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
	std::string r;
	for(int i = 0; i < n; i++)
		r += alpha[rand() % alpha.size()];
	return r;
}

}