#include "../includes/malloc.h"

void	my_free(void *ptr) {
	f_list		*tmp;
	m_block		*b;
	int			k;

	k = 0;
	if ((b = find_corresponding_block(ptr)) == NULL)
		return ;
	tmp = (f_list *)((void *)b + S_ALLOC(m_block));
	while ((void *)tmp < (void *)b + b->h_block.size) {
		if ((void *)tmp + S_ALLOC(f_list) == ptr) {
			add_element_f_list((void *)tmp, tmp->f.data.d.size);
			return ;
		}
		k += (S_ALLOC(f_list) + tmp->f.data.d.size);
		tmp = (f_list *)((void *)tmp + k);
	}
}