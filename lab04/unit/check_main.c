#include <check.h>

#define EXIT_SUCCESS 0 
#define EXIT_FAILURE 1

Suite* crypt_word_suite(void);

int main(void)
{
    int no_failed = 0;
    Suite *s[] = 
    {   
        crypt_word_suite()
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
