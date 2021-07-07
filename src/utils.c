#include <sodium.h>

unsigned char *hex_to_byte(unsigned char *arr)
{
    unsigned char *buf = malloc(crypto_hash_sha256_BYTES);
    unsigned char *pos = arr;
    for (size_t count = 0; count < crypto_hash_sha256_BYTES; count++) {
        sscanf((char *)pos, "%2hhx", &buf[count]);
        pos += 2;
    }
    return buf;
}
