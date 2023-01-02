/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closefd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 22:14:28 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/01 22:14:29 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_closefd(int count, ...)
{
	va_list	ap;

	va_start(ap, count);
	while (count-- > 0)
		close(va_arg(ap, int));
	va_end(ap);
}
