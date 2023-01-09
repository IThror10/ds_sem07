#include <check.h>
#include "data.h"
#include "crypt.h"

START_TEST(block_encryption)
{
    //Arrange
    block_t state = {{0x328831e0U, 0x435a3137U, 0xf6309807U, 0xa88da234U}, 0};
    block_t key = {{0x2b28ab09U, 0x7eaef7cfU, 0x15d2154fU, 0x16a6883cU}, 0};
    block_t res = {{0x3902dc19U, 0x25dc116aU, 0x8409850bU, 0x1dfb9732U}, 0};

    //Act
    encrypt_block(&state, &key);

    //Assert
    ck_assert_int_eq(state.words[0], res.words[0]);
    ck_assert_int_eq(state.words[1], res.words[1]);
    ck_assert_int_eq(state.words[2], res.words[2]);
    ck_assert_int_eq(state.words[3], res.words[3]);
}
END_TEST
START_TEST(block_decryption)
{
    //Arrange
    block_t state = {{0x3902dc19U, 0x25dc116aU, 0x8409850bU, 0x1dfb9732U}, 0};
    block_t key = {{0x2b28ab09U, 0x7eaef7cfU, 0x15d2154fU, 0x16a6883cU}, 0};
    block_t res = {{0x328831e0U, 0x435a3137U, 0xf6309807U, 0xa88da234U}, 0};

    //Act
    decrypt_block(&state, &key);

    //Assert
    ck_assert_int_eq(state.words[0], res.words[0]);
    ck_assert_int_eq(state.words[1], res.words[1]);
    ck_assert_int_eq(state.words[2], res.words[2]);
    ck_assert_int_eq(state.words[3], res.words[3]);
}
END_TEST

Suite* crypt_block_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("crypt_block_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, block_encryption);
    tcase_add_test(test, block_decryption);

    suite_add_tcase(s, test);
    return s;
}


START_TEST(keys_expand_test)
{
    //Arrange
    block_t key = {{0x2b28ab09U, 0x7eaef7cfU, 0x15d2154fU, 0x16a6883cU}, 4};
    block_t res[2] = {
        {{0xa088232aU, 0xfa54a36cU, 0xfe2c3976U, 0x17b13905U}, 4},
        {{0xf27a5973U, 0xc2963559U, 0x95b980f6U, 0xf2437a7fU}, 4},
    };
    block_t keys[2];

    //Act
    keys_expand(keys, &key, 2);

    //Assert
    ck_assert_int_eq(keys[0].words[0], res[0].words[0]);
    ck_assert_int_eq(keys[0].words[1], res[0].words[1]);
    ck_assert_int_eq(keys[0].words[2], res[0].words[2]);
    ck_assert_int_eq(keys[0].words[3], res[0].words[3]);

    ck_assert_int_eq(keys[1].words[0], res[1].words[0]);
    ck_assert_int_eq(keys[1].words[1], res[1].words[1]);
    ck_assert_int_eq(keys[1].words[2], res[1].words[2]);
    ck_assert_int_eq(keys[1].words[3], res[1].words[3]);
}
END_TEST
START_TEST(shift_rows_test)
{
    //Arrange
    block_t data = {{0xd4e0b81eU, 0x27bfb441U, 0x11985d52U, 0xaef1e530U}, 4};
    block_t res = {{0xd4e0b81eU, 0xbfb44127U, 0x5d521198U, 0x30aef1e5U}, 4};

    //Act
    shift_rows(&data);

    //Assert
    ck_assert_int_eq(data.words[0], res.words[0]);
    ck_assert_int_eq(data.words[1], res.words[1]);
    ck_assert_int_eq(data.words[2], res.words[2]);
    ck_assert_int_eq(data.words[3], res.words[3]);
}
END_TEST
START_TEST(inv_shift_rows_test)
{
    //Arrange
    block_t data = {{0xd4e0b81eU, 0xbfb44127U, 0x5d521198U, 0x30aef1e5U}, 4};
    block_t res = {{0xd4e0b81eU, 0x27bfb441U, 0x11985d52U, 0xaef1e530U}, 4};

    //Act
    inv_shift_rows(&data);

    //Assert
    ck_assert_int_eq(data.words[0], res.words[0]);
    ck_assert_int_eq(data.words[1], res.words[1]);
    ck_assert_int_eq(data.words[2], res.words[2]);
    ck_assert_int_eq(data.words[3], res.words[3]);
}
END_TEST
START_TEST(add_round_key_test)
{
    //Arrange
    block_t data = {{0x04e04828U, 0x66cbf806U, 0x8119d326U, 0xe59a7a4cU}, 4};
    block_t add = {{0xa088232aU, 0xfa54a36cU, 0xfe2c3976U, 0x17b13905U}, 4};
    block_t res = {{0xa4686b02U, 0x9c9f5b6aU, 0x7f35ea50U, 0xf22b4349U}, 4};

    //Act
    add_round_key(&data, &add);

    //Assert
    ck_assert_int_eq(data.words[0], res.words[0]);
    ck_assert_int_eq(data.words[1], res.words[1]);
    ck_assert_int_eq(data.words[2], res.words[2]);
    ck_assert_int_eq(data.words[3], res.words[3]);
}
END_TEST
START_TEST(mix_columns_test)
{
    //Arrange
    block_t data = {{0xd4e0b81eU, 0xbfb44127U, 0x5d521198U, 0x30aef1e5U}, 4};
    block_t res = {{0x04e04828U, 0x66cbf806U, 0x8119d326U, 0xe59a7a4cU}, 4};

    //Act
    mix_columns(&data, str_Cx);

    //Assert
    ck_assert_int_eq(data.words[0], res.words[0]);
    ck_assert_int_eq(data.words[1], res.words[1]);
    ck_assert_int_eq(data.words[2], res.words[2]);
    ck_assert_int_eq(data.words[3], res.words[3]);
}
END_TEST

Suite* subfunc_block_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("subfunc_block_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, keys_expand_test);
    tcase_add_test(test, shift_rows_test);
    tcase_add_test(test, add_round_key_test);
    tcase_add_test(test, mix_columns_test);
    tcase_add_test(test, inv_shift_rows_test);

    suite_add_tcase(s, test);
    return s;
}