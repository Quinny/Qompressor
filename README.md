Qompressor
=============
A little text compression project that I am working on.

In its current state it doesn't really compress anything (it actually makes files bigger) but its kind of a cool encoder.  I used Huffmans algorithm for encoding, but slightly modified it to work with an n-ary tree as apposed to always using a binary tree.  I have a few ideas for making it better and hopefully it will be able to actually compress things soon.

For a more detailed explanation and thought process see [here](http://quinnftw.com/qompressor/) .

Usage
=====

#To build:
Clone the repo, cd into the directory and run
`make`

#To use:
`qpress [-d] <filename>`

The -d option is to decompress a file.  If run with no options, it will compress the given file and store it as `filename.qzip`.  I plan to add options in the future to specifiy whether you want the key stored in the compressed file or in a separate file (for information hiding).
