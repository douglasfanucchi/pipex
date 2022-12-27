#include "../minunit.h"
#include <ft_printf.h>

MU_TEST(test_percentage_id) {
	t_data_format	*data_format = get_percentage_format();
	
	mu_check(data_format != NULL);
	mu_check(!ft_strncmp(data_format->id, "%%", 2));

	free(data_format);
}

MU_TEST(test_percentage_formatter) {
	t_data_format	*data_format = get_percentage_format();

	mu_check(data_format != NULL);
	mu_check(data_format->formatter == NULL);

	free(data_format);
}

MU_TEST(test_percentage_get_arg) {
	t_data_format	*data_format = get_percentage_format();

	mu_check(data_format != NULL);
	mu_check(data_format->get_arg == NULL);

	free(data_format);
}

MU_TEST_SUITE(test_percentage_format) {
	MU_RUN_TEST(test_percentage_id);
	MU_RUN_TEST(test_percentage_formatter);
	MU_RUN_TEST(test_percentage_get_arg);
}
