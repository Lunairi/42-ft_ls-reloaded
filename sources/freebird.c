
#include "ftls.h"

void				free_struct(t_data *data)
{
	if (free->d)
}

void				free_dir(t_data *start)
{
	t_data			*ptr;

	ptr = start;
	while (ptr) {
		free_struct(ptr);
		ptr = ptr->next;
	}
}