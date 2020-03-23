#include "printf.h"
#include <fcntl.h>

/*
 * ft_fprintf - записывает форматированную строку в файл
 * если файла нет - создает новый (нужно указать название)
 * если файл есть - затирает содержимое (можно сделать чтобы не затирала)
 *
 * ft_vprint - передает в функцию готовый va_list ap
 * передать список аргументов можно из любой другой функции
 * за создание и закрытие va_list ap отвечает тот, кто вызывает функицию
 *
 * ft_vfprintf - объединяет функционал предыдущих 2х функций
 * 1)записывает результат в файл
 * 2)работает со сформированным и полученным заранее va_list ap
 *
 */

int     ft_fprintf(char *file, const char *format, ...)
{
	va_list			ap;
	int			    *conv;
	int				read_symbols;

	if (!format || !*format || !file || !*file)
		return (0);
	conv = ft_new_integer_list(8);
	if ((conv[7] = open(file, O_RDWR | O_TRUNC | O_CREAT)) < 0)
	{
		free(conv);
		conv = NULL;
		return (0);
	}

	va_start(ap, format);
	read_symbols = format_str(format, ap, &conv, 0);
	va_end(ap);
	close(conv[7]);
	free(conv);
	conv = NULL;
	return (read_symbols);
}

int     ft_vprintf(const char *format, va_list ap)
{
	int			    *conv;
	int				read_symbols;

	if (!format || !*format)
		return (0);
	conv = ft_new_integer_list(8);
	conv[7] = -1;
	read_symbols = format_str(format, ap, &conv, 0);
	free(conv);
	conv = NULL;
	return (read_symbols);
}

int     ft_vfprintf(char *file, const char *format, va_list ap)
{
	int			    *conv;
	int				read_symbols;

	if (!format || !*format || !file || !*file)
		return (0);
	conv = ft_new_integer_list(8);
	if ((conv[7] = open(file, O_WRONLY | O_TRUNC | O_CREAT)) < 0)
	{
		free(conv);
		conv = NULL;
		return (0);
	}

	read_symbols = format_str(format, ap, &conv, 0);
	close(conv[7]);
	free(conv);
	conv = NULL;
	return (read_symbols);
}