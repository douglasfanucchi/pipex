#include "../minunit.h"
#include <ft_printf.h>
#include <limits.h>

MU_TEST(test_decimal_formatter) {
	t_data_format	*data_format = get_decimal_format();
	mu_check(data_format != NULL);

	mu_check(!ft_strncmp(data_format->id, "%d", 2));

	int n;
	char *result;

	n = 101;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "101", 3));
	free(result);

	n = -1;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "-1", 2));
	free(result);

	n = INT_MAX;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "2147483647", 10));
	free(result);

	n = INT_MIN;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "-2147483648", 10));
	free(result);
	
	free(data_format);
}

static void	testing_decimal_get_arg(t_data_format *data_format, ...)
{
	va_list ap;
	int		*result;

	va_start(ap, data_format);
	result = data_format->get_arg(ap);
	mu_check(*result == INT_MAX);
	free(result);
	va_end(ap);
}

MU_TEST(test_decimal_get_arg) {
	t_data_format *data_format = get_decimal_format();
	mu_check(data_format != NULL);

	testing_decimal_get_arg(data_format, INT_MAX);

	free(data_format);
}

MU_TEST_SUITE(test_decimal_format) {
	MU_RUN_TEST(test_decimal_formatter);
	MU_RUN_TEST(test_decimal_get_arg);
}
