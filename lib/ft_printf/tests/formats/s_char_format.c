#include "../minunit.h"
#include <ft_printf.h>

static char	*testing_get_arg(void *(*f)(va_list), ...)
{
	va_list	ap;

	va_start(ap, f);
	char *str = f(ap);
	va_end(ap);

	return (str);
}

MU_TEST(test_get_char_format) {
	t_data_format	*data_format;
	
	data_format = get_char_format();
	mu_check(data_format != NULL);
	mu_check(!ft_strncmp(data_format->id, "%c", 2));
	
	free(data_format);
}

MU_TEST(test_char_formatter) {
	t_data_format	*data_format = get_char_format();

	mu_check(data_format != NULL);
	mu_check(data_format->formatter == NULL);

	free(data_format);
}

MU_TEST(test_char_get_arg) {
	t_data_format	*data_format;

	data_format = get_char_format();
	char *s = testing_get_arg(data_format->get_arg, 'd');
	mu_check(!ft_strncmp(s, "d", 1));

	free(s);
	free(data_format);
}

MU_TEST_SUITE(tests_s_char_format) {
	MU_RUN_TEST(test_get_char_format);
	MU_RUN_TEST(test_char_formatter);
	MU_RUN_TEST(test_char_get_arg);
}
