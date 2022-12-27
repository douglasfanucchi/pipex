#include <ft_printf.h>
#include "../minunit.h"

MU_TEST(test_pointer_formatter) {
	t_data_format	*data_format = get_pointer_format();
	mu_check(data_format != NULL);
	mu_check(!ft_strncmp(data_format->id, "%p", 2));

	void	**any = malloc(sizeof(void *));

	mu_check(any != NULL);
	*any = "douglas fanucchi";

	char	*result = data_format->formatter(any);

	mu_check(!ft_strncmp("0x", result, 2));
	free(result);

	*any = NULL;
	result = data_format->formatter(any);
	mu_check(!ft_strncmp("(nil)", result, 3));
	free(result);

	free(any);
	free(data_format);
}

static void**	testing_pointer_get_arg(t_data_format *data_format, ...)
{
	va_list ap;
	void	*result;

	va_start(ap, data_format);
	result = data_format->get_arg(ap);
	va_end(ap);

	return (result);
}

MU_TEST(test_pointer_get_arg) {
	t_data_format	*data_format = get_pointer_format();
	void	*any = malloc(1);

	mu_check(data_format != NULL);
	mu_check(any != NULL);

	void	**ptr = testing_pointer_get_arg(data_format, any);
	mu_check(*ptr == any);

	free(ptr);
	free(any);
	free(data_format);
}

MU_TEST_SUITE(test_pointer_format) {
	MU_RUN_TEST(test_pointer_formatter);
	MU_RUN_TEST(test_pointer_get_arg);
}
