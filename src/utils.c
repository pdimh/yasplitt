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
