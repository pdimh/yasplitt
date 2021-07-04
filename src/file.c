#include <err.h>
#include <file.h>
#include <math.h>
#include <sodium.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

filenode *add_filenode(filenode **flist, char *fname, unsigned int size)
{
    filenode *newnode = malloc(sizeof(filenode));
    filenode *curr = *flist;

    if (!*flist)
        *flist = curr = newnode;
    else {
        while (curr->next)
            curr = curr->next;
    }
    curr->next = newnode;
    newnode->path = malloc(strlen(fname));
    newnode->size = size;
    newnode->next = NULL;
    strncpy(newnode->path, fname, strlen(fname));
    return curr;
}

filenode *split_file(char *input_path, char *output_path, long size)
{
    filenode *fcurr;
    filenode *flist = NULL;
    FILE *fin = fopen(input_path, "rb");
    struct stat st;
    char buf[size + 1];
    char *fname;
    int counter = 0;
    int padding;
    int num_files;

    if (!fin)
        err(EXIT_FAILURE, "%s", input_path);

    stat(input_path, &st);

    num_files = (int)ceil((float)st.st_size / size);
    padding = num_files > 1 ? (int)ceil(log10(num_files)) : 1;

    fname = malloc(strlen(output_path) + padding + 5);

    while (!feof(fin)) {
        FILE *fout;
        int rbytes = fread(buf, 1, size, fin);

        sprintf(fname, "%s.part.%0*d", output_path, padding, counter++);
        fout = fopen(fname, "wb");
        if (!fout)
            err(EXIT_FAILURE, "%s", fout);
        fwrite(buf, 1, rbytes, fout);
        fcurr = add_filenode(&flist, fname, rbytes);

        fclose(fout);
    }
    free(fname);
    fclose(fin);

    return flist;
}

void merge(filenode *input_path, char *output_path)
{
    filenode *fcurr = input_path;
    FILE *fout = fopen(output_path, "wb");
    char buf[BUFSIZE];

    if (!fout)
        err(EXIT_FAILURE, "%s", fout);
    while (fcurr) {
        FILE *fin = fopen(fcurr->path, "rb");
        int rbytes;

        if (!fout)
            err(EXIT_FAILURE, "%s", fin);

        rbytes = fread(buf, 1, BUFSIZE, fin);
        fwrite(buf, 1, rbytes, fout);
        fclose(fin);

        printf("%s\n", fcurr->path);
        fcurr = fcurr->next;
    }
    fclose(fout);
}

void gen_sha256sum(filenode *flist)
{

    filenode *fcurr = flist;

    if (flist) {
        FILE *fout;
        char fname[strrchr(flist->path, '.') - flist->path];

        strncpy(fname, flist->path,
                strrchr(flist->path, '.') - flist->path - 5);
        strncpy(fname + sizeof(fname) - 5, ".SUM", 5);

        fout = fopen(fname, "w");

        if (!fout)
            err(EXIT_FAILURE, "%s", fname);

        while (fcurr) {
            FILE *fin = fopen(fcurr->path, "rb");
            char buf[fcurr->size];

            fread(buf, 1, fcurr->size, fin);
            crypto_hash_sha256(fcurr->sha256, (unsigned char *)buf,
                               fcurr->size);
            for (int i = 0; i < crypto_hash_sha256_BYTES; i++)
                fprintf(fout, "%02x", fcurr->sha256[i]);
            fprintf(fout, " %s\n", fcurr->path);
            fcurr = fcurr->next;
        }
        fclose(fout);
    }
}
