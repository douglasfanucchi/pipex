#include "../minunit.h"
#include <ft_printf.h>

static void	func_testing_get_arg_hex_lower(t_data_format *data_format, ...)
{
	va_list ap;

	va_start(ap, data_format);
	int	*nb = data_format->get_arg(ap);
	mu_check(*nb == 123);
	free(nb);
	va_end(ap);
}

MU_TEST(testing_get_arg_hex_lower) {
	t_data_format	*data_format = get_hex_lower_format();
	func_testing_get_arg_hex_lower(data_format, 123);
	free(data_format);
}

MU_TEST(test_formatter) {
	t_data_format	*data_format = get_hex_lower_format();
	unsigned long	n;
	char			*result;

	mu_check(data_format != NULL);
	mu_check(!ft_strncmp(data_format->id, "%x", 2));

	n = -1;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "ffffffff", 8));
	free(result);

	n = 10;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "a", 1));
	free(result);

	n = 16;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "10", 1));
	free(result);

	free(data_format);
}

MU_TEST_SUITE(test_hex_lower_format) {
	MU_RUN_TEST(test_formatter);
	MU_RUN_TEST(testing_get_arg_hex_lower);
}
