#ifndef __CRYPT_H__
#define __CRYPT_H__

    typedef unsigned char byte_t;
    typedef unsigned int word_t;
    typedef unsigned long long size_t;

    size_t crypt_word(size_t word, size_t key, size_t N); 
    size_t get_open_key(word_t p_num, word_t q_num);
    size_t get_secret_key(word_t p_num, word_t q_num);

#endif //__CRYPT_H__