#include <check.h>
#include "freq_list.h"

START_TEST(list_build)
{
    //Arrange
    freq_list_t *list = NULL;

    //Act
    status_t res1 = increase_freq(&list, 'a');
    status_t res2 = increase_freq(&list, 'b');
    status_t res3 = increase_freq(&list, 'b');

    //Assert
    ck_assert_int_eq(ok, res1);
    ck_assert_int_eq(ok, res2);
    ck_assert_int_eq(ok, res3);
    ck_assert_int_eq(1, list->amount);
    ck_assert_int_eq('a', list->letter);
    ck_assert_int_eq(2, list->next->amount);
    ck_assert_int_eq('b', list->next->letter);

    free_list(&list);
}
END_TEST

Suite* increase_freq_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("increase_freq_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, list_build);

    suite_add_tcase(s, test);
    return s;
}


START_TEST(center_insert)
{
    //Arrange
    freq_list_t node1, node2, node3, node4, node5, node6;
    node1.amount = 5;
    node1.next = &node2;

    node2.amount = 2;
    node2.next = &node3;

    node3.amount = 3;
    node3.next = &node4;

    node4.amount = 4;
    node4.next = &node5;

    node5.amount = 5;
    node5.next = &node6;

    node6.amount = 6;
    node6.next = NULL;

    //Act
    status_t res = rebalance_list(&node1);

    //Assert
    ck_assert_int_eq(ok, res);
    ck_assert_int_le(node1.amount, node2.amount);
    ck_assert_int_le(node2.amount, node3.amount);
    ck_assert_int_le(node3.amount, node4.amount);
    ck_assert_int_le(node4.amount, node5.amount);
    ck_assert_int_le(node5.amount, node6.amount);
}
END_TEST

Suite* rebalance_list_suite(void)
{
    Suite *s;
    TCase *test;

    s = suite_create("rebalance_list_suite");
    test = tcase_create("tests:");
    
    tcase_add_test(test, center_insert);

    suite_add_tcase(s, test);
    return s;
}