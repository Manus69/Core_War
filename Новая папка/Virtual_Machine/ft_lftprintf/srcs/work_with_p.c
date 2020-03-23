
#include "printf.h" //////++++

int			work_with_pointer(int **s, va_list ap, int read)
{
	void	*d;
	int		count;
	int		*new;

	new = *s;
	d = va_arg(ap, void *);
	count = ft_putnbr_base_c((long long)d, 16);
	if ((new[2] == -2 || new[2] == -3) && new[1] <= 0 && (long long)d == 0)
	{
		ft_putstr_mod("0x", new[7]);
		return (2);
	}
	read = work_x_o_u(&new, (long long)d, count, 16);
	return (read);
}
