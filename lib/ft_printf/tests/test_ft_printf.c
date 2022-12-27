#include "./minunit.h"
#include <ft_printf.h>

MU_TEST(test_ft_printf_return) {
	int result = ft_printf("%");
	mu_check(result == -1);

	result = ft_printf("lorem ipsum%");
	mu_check(result == -1);

	result = ft_printf("%k");
	mu_check(result == 2);

	result = ft_printf("");
	mu_check(result == 0);

	result = ft_printf("\0");
	mu_check(result == 0);
}

MU_TEST_SUITE(test_ft_printf) {
	MU_RUN_TEST(test_ft_printf_return);
}
