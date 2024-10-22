/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:40:03 by lpittigl          #+#    #+#             */
/*   Updated: 2024/01/29 23:40:06 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_putstrorchar(char *s, char c, int s_o_c)
{
	int	i;

	i = 0;
	if (s == NULL && s_o_c == 1)
		return (write(1, &c, 1));
	if (s == NULL && s_o_c == 0)
		return (write(1, "(null)", 6));
	while (*s)
		i += write (1, s++, 1);
	return (i);
}

int	ft_putnbr(long long int nb, int base, char *charset)
{
	int	count;

	count = 1;
	if (nb < 0 && base == 10)
	{
		count++;
		ft_putstrorchar(NULL, '-', 1);
		nb = -nb;
	}
	if (nb > base - 1)
		count += ft_putnbr(nb / base, base, charset);
	ft_putstrorchar(NULL, charset[(nb % base)], 1);
	return (count);
}

int	ptr(unsigned long long address, int count, char *charset)
{
	if (address > 15)
		count += ptr(address / 16, 1, charset);
	ft_putstrorchar(NULL, charset[(address % 16)], 1);
	return (count);
}

int	checkwhich(const char s, va_list *args, int len)
{
	if (s == 's')
		len += ft_putstrorchar(va_arg(*args, char *), '\0', 0);
	else if (s == 'p')
	{
		len += write (1, "0x", 2);
		len += ptr(va_arg(*args, unsigned long long), 1, "0123456789abcdef");
	}
	else if (s == 'd' || s == 'i')
		len += ft_putnbr(va_arg(*args, int), 10, "0123456789");
	else if (s == 'u')
		len += ft_putnbr(va_arg(*args, unsigned int), 10, "0123456789");
	else if (s == 'x')
		len += ft_putnbr(va_arg(*args, unsigned int), 16, "0123456789abcdef");
	else if (s == 'X')
		len += ft_putnbr(va_arg(*args, unsigned int), 16, "0123456789ABCDEF");
	else if (s == '%')
		len += write(1, &s, 1);
	else if (s == 'c')
		len += ft_putstrorchar(NULL, (char)va_arg(*args, int), 1);
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += checkwhich(s[i], &args, 0);
		}
		else
		{
			ft_putstrorchar(NULL, s[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
