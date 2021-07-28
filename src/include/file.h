/*  yasplitt - splitting/merging/checksumming files
    Copyright (C) 2021  Pedro Henrique da Silva Palhares

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

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
filenode *split_file(char *input_path, char *output_path, off_t size);
void merge(filenode *input_path, char *output_path);
void gen_sha256_file(filenode *flist, char *sum_path);
void check_sha256sum(filenode *flist, char *sum_path);
off_t get_filesize(char *f);
unsigned char *hex_to_byte(unsigned char *arr);
void calculate_sha256sum(filenode *flist);
#endif
