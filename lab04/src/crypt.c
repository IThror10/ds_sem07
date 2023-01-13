#include "crypt.h"

//Наименьший общий делитель
static size_t simple_evklid(size_t a, size_t b)
{
    while (b)
    {
        size_t res = a % b;
        a = b;
        b = res;
    }
    return a;
}

static size_t fi_N(size_t p_num, size_t q_num)
{
    return (p_num - 1) * (q_num - 1);
}

//Взаимно простое с fi_N
size_t get_open_key(word_t p_num, word_t q_num)
{
    size_t fi = fi_N(p_num, q_num), start = 3;//fi - 1;
    while (simple_evklid(fi, start) != 1)
        start += 2;//-= 2;
    return start;
}

// Расширенный алгоритм Евклида
// [(secret_key * open_key) mod fi == 1] -> secret_key
size_t get_secret_key(word_t p_num, word_t q_num)
{
    size_t open_key = get_open_key(p_num, q_num), fi = fi_N(p_num, q_num);

    size_t r_0 = fi, r_1 = open_key, r_2;
    long long t_0 = 0, t_1 = 1, t_2;

    while (r_1 != 1)
    {
        size_t q = r_0 / r_1;
        r_2 = r_0 - q * r_1;
        t_2 = t_0 - q * t_1;

        t_0 = t_1;
        t_1 = t_2;

        r_0 = r_1;
        r_1 = r_2;
    }
    return t_1 < 0 ? t_1 + fi : t_1;
}

// (word ^ key) mod N
// size_t static module_multiply(size_t a, size_t b, size_t N)
// {
//     __uint128_t res = (a * b)
// }

size_t crypt_word(size_t word, size_t key, size_t N)
{
    size_t R = 1;
    while (key)
    {
        if (key & 1)
            // R = module_multiply(R, word, N);
            R = ((__uint128_t) R * word) % N;
        key >>= 1;
        // word = module_multiply(word, word, N);
        word = ((__uint128_t) word * word) % N;
    }
    return R;
}