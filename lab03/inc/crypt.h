#ifndef __CRYPT_H__
#define __CRYPT_H__

    #include "data.h"
    #include "status.h"

    const static byte_t str_Cx[][4] = {
        {02, 03, 01, 01},
        {01, 02, 03, 01},
        {01, 01, 02, 03},
        {03, 01, 01, 02}
    };

    const static byte_t rev_Cx[][4] = {
        {0x0E, 0x0B, 0x0D, 0x09},
        {0x09, 0x0E, 0x0B, 0x0D},
        {0x0D, 0x09, 0x0E, 0x0B},
        {0x0B, 0x0D, 0x09, 0x0E}
    };


    status_t shift_rows(block_t *data);
    status_t inv_shift_rows(block_t *data);
    status_t add_round_key(block_t *data, const block_t *key);
    status_t mix_columns(block_t *data, const byte_t (*mtr)[4]);
    status_t keys_expand(block_t *keys, const block_t *key, int amount);

    status_t encrypt_block(block_t *data, const block_t *key);
    status_t decrypt_block(block_t *data, const block_t *key);

#endif //__CRYPT_H__