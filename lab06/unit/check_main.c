#include <check.h>

#define EXIT_SUCCESS 0 
#define EXIT_FAILURE 1

Suite* write_code_suite();
Suite* add_code_suite();
Suite* increase_freq_suite();
Suite* create_codes_suite();
Suite* rebalance_list_suite();

int main(void)
{
    int no_failed = 0;
    Suite *s[] = 
    {   
        write_code_suite(),
        add_code_suite(),
        increase_freq_suite(),
        rebalance_list_suite(),
        create_codes_suite()
    };
    SRunner *runner;

    for (int i = 0; i < sizeof(s) / sizeof(Suite*); i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        no_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
