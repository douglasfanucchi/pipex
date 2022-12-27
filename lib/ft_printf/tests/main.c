#include "minunit.h"
#include "./formats/s_char_format.c"
#include "./formats/s_str_format.c"
#include "./formats/s_hex_lower_format.c"
#include "./formats/s_hex_upper_format.c"
#include "./formats/s_pointer_format.c"
#include "./formats/s_decimal_format.c"
#include "./formats/s_integer_format.c"
#include "./formats/s_u_decimal_format.c"
#include "./formats/s_percentage_format.c"
#include "./test_hex_base_converter.c"
#include "./test_find_format_from_str_start.c"
#include "./test_ft_printf.c"

int	main()
{
	MU_RUN_SUITE(tests_s_char_format);
	MU_RUN_SUITE(test_s_str_format);
	MU_RUN_SUITE(test_hex_base_converter);
	MU_RUN_SUITE(test_hex_lower_format);
	MU_RUN_SUITE(test_hex_upper_format);
	MU_RUN_SUITE(test_pointer_format);
	MU_RUN_SUITE(test_decimal_format);
	MU_RUN_SUITE(test_integer_format);
	MU_RUN_SUITE(test_u_decimal_format);
	MU_RUN_SUITE(test_percentage_format);
	MU_RUN_SUITE(test_find_format_from_str_start);
	MU_RUN_SUITE(test_ft_printf);
	MU_REPORT();

	return (0);
}
