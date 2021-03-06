#include "../includes/malloc.h"

static int	is_in_f_list(void *ptr) {
	f_list *tmp = g_flist;
	
	while (tmp) {
		if ((void *)tmp == ptr)
			return EXIT_SUCCESS;
		tmp = tmp->f.next;
	}
	return  EXIT_FAILURE;
}

void		dump_block(void) {
	int			i;
	int			j;
	size_t		k;
	m_block		*b;
	f_list		*tmp;

	i = 0;
	b = g_block;
	while (b) {
		printf("\n---------------------BLOCK %d INFORMATION---------------------\n", ++i);
		printf("Size: %zu bytes\n", b->h_block.size);
		tmp = (f_list *)((void *)b + S_ALLOC(m_block));
		j  = 0;
		k = 0;
		if (b == find_corresponding_block((void *)tmp)) {
			while ((void *)tmp < (void *)b + b->h_block.size) {
				if (tmp->f.data.d.magic == MAGIC && is_in_f_list((void *)tmp) == EXIT_FAILURE) {
					printf("\tCHUNCK %d: \n", ++j);
					printf("\t\tSize: %zu bytes\n", tmp->f.data.d.size);
				} 
				k = (S_ALLOC(f_list) + tmp->f.data.d.size);
				tmp = (f_list *)((void *)tmp + k);
			}
		}
		printf("----------------------------------------------------------\n");
		b = b->h_block.next;
	}
}