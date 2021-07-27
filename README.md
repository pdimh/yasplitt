#  yasplitt - Yet Another Split Tool

A tool to split/merge files with checksumming. 

## Warning!!

This is experimental! Don't use it blindly, double check your files, as this may have bugs.

## Compile

To build yasplitt you need glibc, autotools, and libsodium installed on your system. Most Linux distributions provide 
packages for those, check on your package manager. To Build:

```
autoreconf -i
./configure
make
```

## Usage

This tool provides three options: split, merge an checksumming. 
To split a file in 500kb chunks with checksumming: 

``yaspplit -s 500k -o outputfile -c outputfile.SUM inputfile``

To merge files in the same file:

``yaspplit -m -o outputfile -c inputfile.SUM inputfile.part.*``

See that ``-c`` works differently during split and merge. If splitting, checksum file is created. If merging, the file is used to verify if the checksum matches for every file.

You can run ``yaspplit --help`` for more information.