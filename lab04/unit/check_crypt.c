#include <check.h>
#include "crypt.h"

START_TEST(get_secret_key_test)
{
    //Arrange
    size_t p_num = 3000017, q_num = 3000029;
    size_t open_key = get_open_key(p_num, q_num), fi = (p_num - 1) * (q_num - 1);

    //Act
    size_t secret_key = get_secret_key(p_num, q_num);

    //Assert
    ck_assert_int_eq((secret_key * open_key) % fi, 1);
}
END_TEST
START_TEST(get_open_key_test)
{
    //Arrange
    word_t p_num = 5, q_num = 11;

    //Act
    size_t open_key = get_open_key(p_num, q_num);

    //Assert
    ck_assert_int_eq(open_key, 3);
}
END_TEST
START_TEST(word_encrypt_test)
{
    //Arrange
    word_t p_num = 3, q_num = 7;
    size_t open_key = get_open_key(p_num, q_num), N = p_num * q_num;

    //Act
    size_t res1 = crypt_word(2, open_key, N);
    size_t res2 = crypt_word(3, 35, 91);
    size_t res3 = crypt_word(5, 14, 11);

    //Assert
    ck_assert_int_eq(res1, 11);
    ck_assert_int_eq(res2, 61);
    ck_assert_int_eq(res3, 9);
}

END_TEST
START_TEST(word_decrypt_test)
{
    //Arrange
    word_t p_num = 3, q_num = 7;
    size_t secret_key = get_secret_key(p_num, q_num), N = p_num * q_num;

    //Act
    size_t res1 = crypt_word(11, secret_key, N);

    //Assert
    ck_assert_int_eq(res1, 2);
}
END_TEST
START_TEST(word_crypt_test)
{
    //Arrange
    word_t p_num = 3000017, q_num = 3000029;
    size_t secret_key = get_secret_key(p_num, q_num), open_key = get_open_key(p_num, q_num);
    size_t N = (size_t) p_num * q_num, fi = (size_t) (p_num - 1) * (q_num - 1);

    size_t start = 562441757716U, crypted = 1008046814985;

    //Act
    size_t res1 = crypt_word(start, open_key, N);
    size_t res2 = crypt_word(crypted, secret_key, N);

    //Assert
    ck_assert_int_eq(N, 9000138000493);
    ck_assert_int_eq((secret_key * open_key) % fi, 1);
    ck_assert_int_eq(res1, crypted);
    ck_assert_int_eq(res2, start);
}
END_TEST

Suite* crypt_word_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("crypt_block_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, get_open_key_test);
    tcase_add_test(test, get_secret_key_test);
    tcase_add_test(test, word_encrypt_test);
    tcase_add_test(test, word_decrypt_test);
    tcase_add_test(test, word_crypt_test);

    suite_add_tcase(s, test);
    return s;
}