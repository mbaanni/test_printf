#include<unistd.h>
#include<stdarg.h>
#include<stdlib.h>

int	ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	if (i > 0)
		write(1, str, i);
	return(i);
}

void	ft_putnbr(long int nbr, int *i)
{
	char c;
	if (nbr < 0)
		nbr *= -1;
	if (nbr / 10)
		ft_putnbr(nbr / 10, i);
	c = nbr%10 + 48;
	write(1, &c, 1);
	(*i)++;
}

void	put_hex(int nbr, int *i)
{
	char arr[16] = "0123456789abcdef";
	if (nbr / 16)
	{
		(*i)++;
		put_hex(nbr / 16, i);
	}
	write(1, &arr[nbr % 16], 1);
}

int	take_arg(va_list list, char *str)
{
	int i = 0;
	if (*str)
	{
			if (*(str + 1) == 's')
				return (ft_putstr(va_arg(list, char *)));
			else if (*(str + 1) == 'd')
			{
				ft_putnbr((long int)va_arg(list, int), &i);
				return (i);
			}
			else if (*(str + 1) == 'x')
			{
				put_hex(va_arg(list, int), &i);
				return (i);
			}
			else if (*(str + 1) == '%')
				return (write(1, "%", 1));
		}
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int	count = 0;
	va_list list;
	va_start(list, str);
	while (*str)
	{
		if (*str == '%')
		{
			count += take_arg(list, str);
			str++;
		}
		else
		{
			write(1, str, 1);
			count++;
		}
		str++;
	}

}

int main()
{
	ft_printf("%s this test", "simos");
}
