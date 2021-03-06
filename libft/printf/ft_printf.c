/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:16:06 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:16:06 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		**update(void)
{
	void		**funcs;

	funcs = (void **)malloc(sizeof(void *) * 15);
	funcs[CHAR] = ft_putch;
	funcs[UNICODE_CH] = put_un_ch;
	funcs[UNICODE_STR] = put_un_string;
	funcs[STRING] = ft_putstring;
	funcs[BAD_TYPE] = bad_type;
	funcs[POINTER] = pointer;
	funcs[PERCENT] = percent;
	funcs[DECIMAL] = decimal;
	funcs[U_OCTAL] = octal;
	funcs[U_DECIMAL] = unsigned_decimal;
	funcs[U_HEX_LOWER] = hexdecimal_low;
	funcs[U_HEX_UPPER] = hexdecimal_up;
	funcs[FLOAT] = print_float;
	funcs[BINARY] = print_binary;
	funcs[MEMORY] = print_memory;
	return (funcs);
}

int			all_oper(t_mask *mask, va_list ap, void **funcs)
{
	int		(*func)(t_mask *, void *);
	int		(*floats)(t_mask *, long double, int);
	int		len;

	len = 0;
	(mask->width < 0) ? mask->minus = 1 : 0;
	(mask->width < 0) ? mask->width *= -1 : 0;
	(mask->accurancy < -1) ? mask->accurancy = -1 : 0;
	(mask->l && mask->type == CHAR) ? mask->type = UNICODE_CH : 0;
	(mask->l && mask->type == STRING) ? mask->type = UNICODE_STR : 0;
	(mask->width < -1) ? mask->width = 0 : 0;
	(mask->type != FLOAT) ? func = funcs[mask->type] : 0;
	(mask->type == FLOAT) ? floats = funcs[mask->type] : 0;
	if (mask->type == BAD_TYPE || mask->type == PERCENT)
		len += func(mask, NULL);
	else if (mask->type == FLOAT)
		len += (mask->l_big) ? floats(mask, va_arg(ap, long double), 0)
	: floats(mask, va_arg(ap, double), 0);
	else
		len += func(mask, va_arg(ap, void *));
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_mask		*mask;
	void		**funcs;
	int			i;
	int			len;

	i = -1;
	len = 0;
	funcs = update();
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += read_mask(((char *)format) + i, &mask, &ap);
			len += all_oper(mask, ap, funcs);
			free(mask);
			(i > 0) ? i-- : 0;
			continue ;
		}
		len += write(1, &(format[i]), 1);
	}
	free(funcs);
	va_end(ap);
	return (len);
}
