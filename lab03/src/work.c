#include "work.h"
#include "data.h"
#include "crypt.h"

static status_t read_block(FILE *src, block_t *data)
{
    status_t res = ok;
    if (data == NULL)
        res = null_pointer_error;
    else
    {
        block_t block = {{0, 0, 0, 0}, 0};
        block.size += fread(block.words, sizeof(char), 4, src) > 0;
        block.size += fread(block.words + 1, sizeof(char), 4, src) > 0;
        block.size += fread(block.words + 2, sizeof(char), 4, src) > 0;
        block.size += fread(block.words + 3, sizeof(char), 4, src) > 0;


        *data = block;
    }
    return res;
}


typedef status_t (*crypt_func_t)(block_t*, const block_t*);
static status_t crypt_file(FILE *src, FILE *dst, crypt_func_t crypt_func, size_t bytes)
{
    status_t res;
    block_t data;
    const static block_t cipher_key = {{-454430834, -762685917, 249668894, -687125378}, 4};

    for (res = read_block(src, &data); res == ok && data.size && bytes > 0; res = read_block(src, &data))
    {
        int write = bytes > 15 ? 16 : bytes;
        bytes -= write;
        
        res = crypt_func(&data, &cipher_key);
        fwrite(data.words, sizeof(char), write, dst);
    }
    return res;
}

status_t encrypt_file(FILE *src, FILE *dst)
{
    status_t res;
    long long size = 0;
    
    fwrite(&size, sizeof(size_t), 1, dst);
    res = crypt_file(src, dst, encrypt_block, -1ULL);

    size = ftell(src);
    if (res == ok)
    {
        rewind(dst);
        fwrite(&size, sizeof(size_t), 1, dst);
    }
    return res;
}

status_t decrypt_file(FILE *src, FILE *dst)
{
    size_t size = 0;
    fread(&size, sizeof(size_t), 1, src);
    return crypt_file(src, dst, decrypt_block, size);
}