#include <sodium.h>

#ifndef FILE_H
#define FILE_H

#define BUFSIZE 4194304

typedef struct filenode filenode;
struct filenode {
        char *path;
        unsigned int size;
        unsigned char sha256[crypto_hash_sha256_BYTES];
        filenode *next;
};  

filenode *add_filenode(filenode **flist, char *fname, unsigned int size);
filenode *split_file(char *input_path, char *output_path, long size);
void merge(filenode *input_path, char *output_path);
void gen_sha256sum(filenode *flist);
#endif
