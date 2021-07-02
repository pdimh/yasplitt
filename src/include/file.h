#include <sodium.h>

#ifndef FILE_H
#define FILE_H

typedef struct filenode filenode;
struct filenode {
        char *path;
        unsigned int size;
        unsigned char sha256[crypto_hash_sha256_BYTES];
        filenode *next;
};  

filenode *split_file(char *input_path, char *output_path, long size);
void gen_sha256sum(filenode *flist);
#endif
