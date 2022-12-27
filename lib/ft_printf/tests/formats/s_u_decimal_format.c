#include "../minunit.h"
#include <ft_printf.h>
#include <limits.h>

MU_TEST(test_u_decimal_id) {
	t_data_format	*data_format = get_u_decimal_format();

	mu_check(data_format != NULL);
	mu_check(!ft_strncmp(data_format->id, "%u", 2));

	free(data_format);
}

MU_TEST(test_u_decimal_formatter) {
	t_data_format	*data_format = get_u_decimal_format();

	mu_check(data_format != NULL);

	char	*result;
	int		n;

	n = -1;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "4294967295", 10));
	free(result);

	n = 0;
	result = data_format->formatter(&n);
	mu_check(!ft_strncmp(result, "0", 1));
	free(result);

	free(data_format);
}

static void	testing_u_decimal_get_arg(t_data_format *data_format, ...)
{
	va_list	ap;

	va_start(ap, data_format);
	
	unsigned int	*result = data_format->get_arg(ap);
	mu_check(*result == 4294967295);	

	free(result);
	va_end(ap);
}

MU_TEST(test_u_decimal_get_arg) {
	t_data_format	*data_format = get_u_decimal_format();

	mu_check(data_format != NULL);
	testing_u_decimal_get_arg(data_format, -1);
	free(data_format);
}

MU_TEST_SUITE(test_u_decimal_format) {
	MU_RUN_TEST(test_u_decimal_id);
	MU_RUN_TEST(test_u_decimal_formatter);
	MU_RUN_TEST(test_u_decimal_get_arg);
}
