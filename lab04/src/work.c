#include "work.h"
#include "crypt.h"

void print_error_status(status_t status)
{
    switch (status)
    {
    case argv_error:
        printf("Передано неверное количество аргументов: <Command>, <src.file>, <dst.file>, <keys.file>");
        break;
    
    case unknown_file:
        printf("Укзанный файл не найден");
        break;

    case unknown_command:
        printf("Неизвестная команда");
        break;

    case keys_read_error:
        printf("Неверное содержимое файла с ключами");
        break;

    case small_keys_error:
        printf("Простые числа <keys.file> слишком малы");
        break;
    
    case null_pointer_error:
        printf("Null Pointer Exception");
        break;

    case ok:
        break;
    }
}

static status_t read_nums(word_t *p_num, word_t *q_num, FILE *src)
{
    status_t res = ok;
    word_t read_A, read_B;
    size_t mult;

    if (p_num == NULL || q_num == NULL || src == NULL)
        res = null_pointer_error;
    else if (fscanf(src, "%u %u", &read_A, &read_B) != 2)
        res = keys_read_error;
    else
    {
        mult = (size_t) read_A * read_B;
        if (mult <= (word_t)(-1))
            res = small_keys_error;
        {
            *p_num = read_A;
            *q_num = read_B;
        }
    }
    return res;
}

status_t encrypt_file(FILE *src, FILE *dst, FILE *key_src)
{
    status_t res;
    word_t p_num, q_num;
    size_t size = 0, key;
    
    res = read_nums(&p_num, &q_num, key_src);
    if (res == ok)
    {
        key = get_open_key(p_num, q_num);
        fwrite(&size, sizeof(size_t), 1, dst);
        
        word_t read_word;
        size_t write_word, alph_size = (size_t) p_num * q_num;
        while ((fread(&read_word, sizeof(word_t), 1, src)))
        {
            write_word = crypt_word(read_word, key, alph_size);
            fwrite(&write_word, sizeof(char), sizeof(size_t), dst);
        }
    }

    if (res == ok)
    {
        size = ftell(src);
        rewind(dst);
        fwrite(&size, sizeof(size_t), 1, dst);
    }
    return res;
}

status_t decrypt_file(FILE *src, FILE *dst, FILE *key_src)
{
    status_t res;
    word_t p_num, q_num;
    size_t size = 0, key;

    res = read_nums(&p_num, &q_num, key_src);
    if (res == ok)
    {
        key = get_secret_key(p_num, q_num);
        fread(&size, sizeof(size_t), 1, src);

        word_t write_word;
        size_t read_word, alph_size = (size_t) p_num * q_num;
        while ((fread(&read_word, sizeof(size_t), 1, src)) > 0 && size > 0)
        {
            int write = size > sizeof(word_t) - 1 ? sizeof(word_t) : size;
            size -= write;
            
            write_word = crypt_word(read_word, key, alph_size);
            fwrite(&write_word, sizeof(char), write, dst);
        }
    }
    return res;
}