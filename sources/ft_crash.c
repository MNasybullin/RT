#include "rt.h"

void	ft_crash(const char *message)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
