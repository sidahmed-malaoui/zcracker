#include <mhash.h>
#include <string.h>


#include "hashes.h"

extern void md5_compress(uint32_t state[4], const uint8_t block[64]);

/* Décommentes pour tester.

int main(int argc, char *argv[])
{
    char hash[1024];

    printf("%d\n", mhash_get_block_size(MHASH_SHA1));
    printf("%d\n", mhash_get_block_size(MHASH_SHA224));
    printf("%d\n", mhash_get_block_size(MHASH_SHA256));
    printf("%d\n", mhash_get_block_size(MHASH_SHA384));
    printf("%d\n", mhash_get_block_size(MHASH_SHA512));

    printf("This is the \"Hello World\" hash in different algorithms\n");
    hash_md5("Hello World", hash);
    printf("md5 : %s\n", hash);

    hash_sha1("Hello World", hash);
    printf("sha1 : %s\n", hash);

    hash_sha224("Hello World", hash);
    printf("sha224 : %s\n", hash);

    hash_sha256("Hello World", hash);
    printf("sha512 : %s\n", hash);

    hash_sha384("Hello World", hash);
    printf("sha384 : %s\n", hash);

    hash_sha512("Hello World", hash);
    printf("sha512 : %s\n", hash);

    hash_sha1("Hello World", hash);
    printf("sha1 : %s\n", hash);

    unsigned char hash_vector[16];
    int size = hash_md5_vector("Hello World", hash_vector);
    printf("md5 vector : ");
    for(int i = 0; i < size; i++){
        printf("%d ", hash_vector[i]);
    }
    printf("\n");

    hash_md5("Hello World", hash);
    printf("md5 : %s\n", hash);
    return 0;
}
*/




/* entry point ==================================================================================================================================== */


int hash_md5(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[16];

    td = mhash_init(MHASH_MD5);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }

    hash[2*i] = '\0';

    return 0;
}


int hash_md5_vector(const char original_str[], unsigned char vector_hash[], int string_length) {
    MHASH td;

    td = mhash_init(MHASH_MD5);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    return mhash_get_block_size(MHASH_MD5);
}

void md5_hash(const uint8_t *message, size_t len, uint32_t hash[4]) {
    hash[0] = UINT32_C(0x67452301);
    hash[1] = UINT32_C(0xEFCDAB89);
    hash[2] = UINT32_C(0x98BADCFE);
    hash[3] = UINT32_C(0x10325476);
    
    size_t i;
    for (i = 0; len - i >= 64; i += 64)
        {
            md5_compress(hash, &message[i]);
        }
    uint8_t block[64];
    size_t rem = len - i;
    memcpy(block, &message[i], rem);
    
    block[rem] = 0x80;
    rem++;
    if (64 - rem >= 8)
        memset(&block[rem], 0, 56 - rem);
    else {
        memset(&block[rem], 0, 64 - rem);
        md5_compress(hash, block);
        memset(block, 0, 56);
    }
    
    block[64 - 8] = (uint8_t)((len & 0x1FU) << 3);
    len >>= 5;
    for (i = 1; i < 8; i++, len >>= 8)
        block[64 - 8 + i] = (uint8_t)len;
    md5_compress(hash, block);
}




int hash_sha1(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[20];

    td = mhash_init(MHASH_SHA1);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_SHA1); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }

    hash[2*i] = '\0';

    return 0;
}

int hash_sha224(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[28];

    td = mhash_init(MHASH_SHA224);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_SHA224); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }
    hash[2*i] = '\0';

    return 0;
}

int hash_sha256(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[32];

    td = mhash_init(MHASH_SHA256);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_SHA256); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }
    hash[2*i] = '\0';

    return 0;
}

int hash_sha384(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[48];

    td = mhash_init(MHASH_SHA384);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_SHA384); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }
    hash[2*i] = '\0';

    return 0;
}


int hash_sha512(const char original_str[], char hash[]) {
    unsigned int i;
    MHASH td;
    unsigned char vector_hash[64];

    td = mhash_init(MHASH_SHA512);

    if (td == MHASH_FAILED) {
        perror("Error : ");
        return -1;
    }

    mhash(td, original_str, strlen(original_str));

    /* Finish the hash and give the result in vector_hash in integer format (Ex : {255, 16 ..}) */
    mhash_deinit(td, vector_hash);

    /* We convert our hash from integer to string. Ex : {255, 16 ..} -> "ff10.." */
    for (i = 0; i < mhash_get_block_size(MHASH_SHA512); i++) {
        sprintf( hash + 2*i, "%.2x", vector_hash[i]);
    }
    hash[2*i] = '\0';

    return 0;
}
