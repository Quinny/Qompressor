#ifndef QP_HUFFMAN_TREE_H
#define QP_HUFFMAN_TREE_H

#include <string>
#include "qompressor.h"
#include <vector>

namespace qompressor{

struct HuffmanNode{
	freq_type freq_;
	std::string word_;
	std::vector<HuffmanNode> children_;
	HuffmanNode(std::string const& word, freq_type f): freq_(f), word_(word) {};
	HuffmanNode(std::vector<HuffmanNode> const& v): children_(v), word_(""){
		for(auto i:v)
			freq_ += i.freq_;
	}
	bool is_leaf(){ return children_.empty(); }
	void add_child(HuffmanNode n){ children_.push_back(n); }
};

struct CompareNode{
	bool operator() (HuffmanNode const& x, HuffmanNode const& y) const { return x.freq_ > y.freq_; }
};

class HuffmanTree{
	HuffmanNode root_;
	// Given a filename, this function will generate a huffman tree
	public:
		static HuffmanTree make(std::string const& filename){
			HuffmanTree t(HuffmanNode("a",1)); 
			freq_table f = t.frequency_table(filename);
			HuffmanNode n = t.make_tree(f);
			return HuffmanTree(n);
		}
		trans_table translation_table();
		

	private:
		void fill_table(HuffmanNode root, std::string seq, trans_table& t);
		HuffmanTree(HuffmanNode n): root_(n) {};
		freq_table frequency_table(std::string const& filename);
		int opt_size(freq_table const& t);
		HuffmanNode make_tree(freq_table& t);
		std::string get_char(int n);
		std::string random_string(int n);

};

}

#endif