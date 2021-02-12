#include "mem_lst.h"

t_mem				*get_mem(void)
{
    static t_mem	mem = {0};

	return (&mem);
}
