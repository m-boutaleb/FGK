# FGK compression algorithm

FGK (Faller Galleger Knuth) is a lossless dynamic compression algorithm developed in C standard ISO/IEC 9899:1999. Thanks to the use of the siblings property of the tree the algorithm allows univocity in encoding and decoding. 

# Features

  - Command Lind Interface available
  - Multilayer architecture
  - Compress and decompress all kind of data

# Installation

FGK require MinGW or any other compiler for C. Static distributions are available for linux and windows in the *dist/* folder, while the necessary libraries are available in the *lib/* dir. 

To run the algorithm go to the dist/<your so> then run the following command and specify the option '-c' to compress or '-d' to decompress followed by an input and an ouput file:

```sh
$ ./static_FGK_1.0.0 <option> <input_file> <output_file>
```

License
----

MIT © Mohamed Boutaleb
