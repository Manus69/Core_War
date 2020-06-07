#include "tokens.h"
#include "function_prototypes.h"

char *replace_extension(const char *file_name, t_container *container)
{
	unsigned int    length;
	char            *replacing_string;

	if (ft_strlen(file_name) < 3)
		invoke_error("file name error", NULL, NULL, container); //EMSG
	length = ft_strlen(file_name) + 2;
	replacing_string = ft_strnew(length);
	replacing_string = ft_strcpy(replacing_string, file_name);
	replacing_string[length - 3] = 'c';
	replacing_string[length - 2] = 'o';
	replacing_string[length - 1] = 'r';
	return (replacing_string);
}

char *trim_file_name(const char *file_name, t_container *container)
{
	unsigned int    length;
	char            *resulting_string;
	int             slash_index;

	length = ft_strlen(file_name);
	if (length < 3)
		invoke_error("file name error while trimmig", NULL, NULL, container); //EMSG
	slash_index = is_in_string(file_name, '/');
	if (slash_index == -1)
		return (ft_strdup(file_name));
	resulting_string =
	ft_strsub(file_name, slash_index + 1, length - slash_index - 1);
	return (resulting_string);
}