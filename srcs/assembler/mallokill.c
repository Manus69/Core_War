#include <stdlib.h>

void	*mallokill(size_t size)
{
	void *result;

	result = malloc(size);
	if (!result)
	{
		free(result);
		exit(1);
	}
	return (result);
}