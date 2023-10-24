#include <unistd.h>
#include <stdarg.h>

void	ft_str(char *str, int *leng)
{
	if (str == NULL)
		str = "(null)";
	while (*str)
		*leng += write(1, str++, 1);
}

void	hex_digit(long long int nbr, int base, int *leng)
{
	if (nbr < 0)
	{
		nbr *= -1;
		*leng += write(1, "-", 1);
	}
	if (nbr >= base)
		hex_digit((nbr / base), base, leng);
	*leng += write(1, &"0123456789abcdef"[nbr % base], 1);
}

int	ft_printf(const char *str, ...)
{
	va_list	pointer;
	int	leng;

	leng = 0;
	va_start(pointer, str);
	while (*str)
	{
		if ((*str == '%') && *(str + 1))
		{
			str++;
			if (*str == 's')
				ft_str(va_arg(pointer, char *), &leng);
			else if (*str == 'd')
				hex_digit((long long int)va_arg(pointer, int), 10, &leng);
			else if (*str == 'x')
				hex_digit((long long int)va_arg(pointer, \
				unsigned int), 16, &leng);
		}
		else
			leng += write(1, str, 1);
		str++;
	}
	va_end(pointer);
	return (leng);
}
