#include "minunit.h"
#include <ft_printf.h>

static void	del_formats(void *data_format)
{
	free(data_format);
}

MU_TEST(test_find_formats) {
	t_data_format *data_format;
	t_list	**formats = get_formats_list();
	mu_check(formats != NULL);

	char	*formats_ids[9] = {"%c", "%d", "%x", "%X", "%i", "%%", "%p", "%s", "%u"};
	size_t	i = 0;
	while (i < 9)
	{
		data_format = find_format_from_str_start(formats, formats_ids[i]);
		mu_check(data_format != NULL);
		mu_check(!ft_strncmp(data_format->id, formats_ids[i], ft_strlen(formats_ids[i])));
		i++;
	}

	ft_lstclear(formats, del_formats);
	free(formats);
}

MU_TEST_SUITE(test_find_format_from_str_start) {
	MU_RUN_TEST(test_find_formats);
}
