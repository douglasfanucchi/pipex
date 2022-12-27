#include <ft_printf.h>
#include "minunit.h"

MU_TEST(test_simple_convertion) {
	t_hex_base_converter	*converter;
	char					*result;

	converter = get_hex_base_converter();
	mu_check(converter != NULL);

	result = converter->convert(5, converter->hex_lower_digits);
	mu_check(!ft_strncmp(result, "5", 1));
	free(result);

	result = converter->convert(16, converter->hex_lower_digits);
	mu_check(!ft_strncmp(result, "10", 2));
	free(result);

	result = converter->convert(-1, converter->hex_lower_digits);
	mu_check(!ft_strncmp(result, "ffffffffffffffff", 16));
	free(result);

	result = converter->convert(-1, converter->hex_upper_digits);
	mu_check(!ft_strncmp(result, "FFFFFFFFFFFFFFFF", 16));
	free(result);

	result = converter->convert(0, converter->hex_upper_digits);
	mu_check(!ft_strncmp(result, "0", 1));
	free(result);

	result = converter->convert(16, converter->hex_upper_digits);
	mu_check(!ft_strncmp(result, "10", 2));
	free(result);

	result = converter->convert('\n', converter->hex_upper_digits);
	mu_check(!ft_strncmp(result, "A", 1));
	free(result);

	free(converter);
}

MU_TEST_SUITE(test_hex_base_converter) {
	MU_RUN_TEST(test_simple_convertion);
}
