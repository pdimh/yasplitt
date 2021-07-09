#include <sodium.h>

#ifndef FILE_H
#define FILE_H

#define BUFSIZE 4194304

typedef struct filenode filenode;
struct filenode {
        char *path;
        off_t size;
        unsigned char sha256[crypto_hash_sha256_BYTES];
        char verified;
        filenode *next;
};

filenode *add_filenode(filenode **flist, char *fname, off_t size);
filenode *split_file(char *input_path, char *output_path, long size);
void merge(filenode *input_path, char *output_path);
void gen_sha256_file(filenode *flist);
void check_sha256sum(filenode *flist, char *sum_path);
off_t get_filesize(char *f);
unsigned char *hex_to_byte(unsigned char *arr);
void calculate_sha256sum(filenode *flist);
#endif
