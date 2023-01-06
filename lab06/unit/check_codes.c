#include <check.h>
#include "codes.h"

START_TEST(two_bytes)
{
    //Arrange
    char buff[64];
    buff[0] = 0;
    codes_t *codes = alloc_codes(1);
    unsigned char code[] = {'a', 'b'};
    add_code(codes, code, 15, 'a');

    //Act
    int pos = write_code(buff, 'a', codes, 0);

    //Assert
    ck_assert_int_eq(pos, 15);
    ck_assert_int_eq(97, buff[0]);
    ck_assert_int_eq(98, buff[1]);

    free_codes(codes);
}
END_TEST
START_TEST(double_write)
{
    //Arrange
    char buff[64];
    buff[0] = 0;
    codes_t *codes = alloc_codes(1);
    unsigned char code[] = {'a'};
    add_code(codes, code, 5, 'a');

    //Act
    int pos1 = write_code(buff, 'a', codes, 0);
    int pos2 = write_code(buff, 'a', codes, pos1);
    int pos3 = write_code(buff, 'a', codes, pos2);

    //Assert
    ck_assert_int_eq(pos1, 5);
    ck_assert_int_eq(pos2, 10);
    ck_assert_int_eq(pos3, 15);
    ck_assert_int_eq(99, buff[0]);
    ck_assert_int_eq(24, buff[1]);

    free_codes(codes);
}
END_TEST
START_TEST(byte_write)
{
    //Arrange
    char buff[64];
    buff[0] = 0;
    codes_t *codes = alloc_codes(1);
    unsigned char code[] = {'a'};
    add_code(codes, code, 8, 'a');

    //Act
    int pos1 = write_code(buff, 'a', codes, 0);
    int pos2 = write_code(buff, 'a', codes, pos1);

    //Assert
    ck_assert_int_eq(pos1, 8);
    ck_assert_int_eq(pos2, 16);
    ck_assert_int_eq('a', buff[0]);
    ck_assert_int_eq('a', buff[1]);

    free_codes(codes);
}
END_TEST

Suite* write_code_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("write_code_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, two_bytes);
    tcase_add_test(test, double_write);
    tcase_add_test(test, byte_write);

    suite_add_tcase(s, test);
    return s;
}


START_TEST(add_long_code)
{
    //Arrange
    codes_t *codes = alloc_codes(1);
    unsigned char code[] = {'a', 'b'};

    //Act
    status_t res = add_code(codes, code, 12, 'a');

    //Assert
    ck_assert_int_eq(ok, res);
    ck_assert_int_eq(1, codes->size);
    ck_assert_int_eq(12, codes->data[0].bits);
    ck_assert_int_eq('a', codes->data[0].string[0]);
    ck_assert_int_eq('b' & 0xF0, codes->data[0].string[1]);
    ck_assert_int_eq('a', codes->data[0].sim);

    free_codes(codes);
}
END_TEST
START_TEST(add_short_codes)
{
    // Arrange
    codes_t *codes = alloc_codes(2);
    codes->data[0].bits = 5;
    codes->data[0].sim = 'a';
    codes->data[0].string = NULL;

    codes->data[1].bits = 5;
    codes->data[1].sim = 'a';
    codes->data[1].string = NULL;
    unsigned char code[] = {'b'};

    // Act
    status_t res1 = add_code(codes, code, 8, 'a');
    status_t res2 = add_code(codes, code, 5, 'b');

    // Assert
    ck_assert_int_eq(ok, res1);
    ck_assert_int_eq(ok, res2);
    ck_assert_int_eq(2, codes->size);
    ck_assert_int_eq(8, codes->data[0].bits);
    ck_assert_int_eq('b', codes->data[0].string[0]);
    ck_assert_int_eq('a', codes->data[0].sim);
    ck_assert_int_eq(5, codes->data[1].bits);
    ck_assert_int_eq('b' & 0xF8, codes->data[1].string[0]);
    ck_assert_int_eq('b', codes->data[1].sim);

    free_codes(codes);
}
END_TEST
Suite* add_code_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("add_code_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, add_long_code);
    tcase_add_test(test, add_short_codes);

    suite_add_tcase(s, test);
    return s;
}

START_TEST(create_func_codes)
{
    //Arrange
    codes_t *codes = NULL;
    nodes_t *nodes = alloc_nodes(3);
    nodes->data[0].left = 'd';
    nodes->data[0].right = 1;
    nodes->data[0].flags = LEAF_LEFT | TREE_RIGHT;

    nodes->data[1].left = 2;
    nodes->data[1].right = 'c';
    nodes->data[1].flags = TREE_LEFT | LEAF_RIGHT;

    nodes->data[2].left = 'a';
    nodes->data[2].right = 'b';
    nodes->data[2].flags = LEAF_LEFT | LEAF_RIGHT;

    //Act
    status_t res = create_codes(&codes, nodes);

    //Assert
    ck_assert_int_eq(ok, res);
    ck_assert_int_eq(4, codes->size);
    
    ck_assert_int_eq(1, codes->data[0].bits);
    ck_assert_int_eq('d', codes->data[0].sim);
    ck_assert_int_eq(0x80, codes->data[0].string[0]);

    ck_assert_int_eq(3, codes->data[1].bits);
    ck_assert_int_eq('a', codes->data[1].sim);
    ck_assert_int_eq(0x60, codes->data[1].string[0]);

    ck_assert_int_eq(3, codes->data[2].bits);
    ck_assert_int_eq('b', codes->data[2].sim);
    ck_assert_int_eq(0x40, codes->data[2].string[0]);

    ck_assert_int_eq(2, codes->data[3].bits);
    ck_assert_int_eq('c', codes->data[3].sim);
    ck_assert_int_eq(0, codes->data[3].string[0]);

    free_nodes(nodes);
    free_codes(codes);
}
END_TEST
START_TEST(create_deep_codes)
{
    //Arrange
    codes_t *codes = NULL;
    nodes_t *nodes = alloc_nodes(3);
    nodes->data[0].left = 1;
    nodes->data[0].right = 2;
    nodes->data[0].flags = TREE_LEFT | TREE_RIGHT;

    nodes->data[1].left = 'a';
    nodes->data[1].right = 'b';
    nodes->data[1].flags = LEAF_LEFT | LEAF_RIGHT;

    nodes->data[2].left = 'c';
    nodes->data[2].right = 'd';
    nodes->data[2].flags = LEAF_LEFT | LEAF_RIGHT;

    //Act
    status_t res = create_codes(&codes, nodes);

    //Assert
    ck_assert_int_eq(ok, res);
    ck_assert_int_eq(4, codes->size);
    
    ck_assert_int_eq(2, codes->data[0].bits);
    ck_assert_int_eq('a', codes->data[0].sim);
    ck_assert_int_eq(0xC0, codes->data[0].string[0]);

    ck_assert_int_eq(2, codes->data[1].bits);
    ck_assert_int_eq('b', codes->data[1].sim);
    ck_assert_int_eq(0x80, codes->data[1].string[0]);

    ck_assert_int_eq(2, codes->data[2].bits);
    ck_assert_int_eq('c', codes->data[2].sim);
    ck_assert_int_eq(0x40, codes->data[2].string[0]);

    ck_assert_int_eq(2, codes->data[3].bits);
    ck_assert_int_eq('d', codes->data[3].sim);
    ck_assert_int_eq(0, codes->data[3].string[0]);

    free_nodes(nodes);
    free_codes(codes);
}
END_TEST
Suite* create_codes_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("create_codes_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, create_func_codes);
    tcase_add_test(test, create_deep_codes);

    suite_add_tcase(s, test);
    return s;
}