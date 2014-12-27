#ifndef QOMPRESSOR_H
#define QOMPRESSOR_H

#include <unordered_map>
#include <fstream>

namespace qompressor{

// I cant see the frequencies ever overflowing an int, but just to be safe
using freq_type = int;
using freq_table = std::unordered_map<std::string, freq_type>;
using trans_table = std::unordered_map<std::string, std::string>;
const char DELIMETER = '$'; // Delimeter used when storing the key

// Given a filename, this function handles the creating of the compressed file
// The file will be written to filename + ".qzip"
trans_table compress(std::string const& filename);

// Given a valid qzipped file, this function will decompress the file to its original
// Content
void decompress(std::string const& filename);

// Returns tokens in order from the file.  It will read words, whitespace and punctuation separately
// This makes it so that "dog." and "dog" do not get treated as separate words
std::string get_token(std::ifstream& f);

// Helper function for get_token which checks if a character is a letter
bool is_letter(char);

// Writes the key to uncompressing the file to the compressed file
void write_key(trans_table const& t, std::fstream &f);

// Reads the key from a compressed file and returns a translation table
trans_table read_key(std::ifstream &f);

// Reads n chars from the file stream and returns them as a string
std::string read_chars(std::ifstream &f, int n);

}

#endif