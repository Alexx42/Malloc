#include "../includes/malloc.h"

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
		tmp = (f_list *)((void *)g_block + S_ALLOC(m_block));
		j  = 0;
		k = 0;
		while (k < b->h_block.size) {
			if (tmp->f.data.d.magic == MAGIC) {
				printf("\tCHUNCK %d: \n", ++j);
				printf("\t\tSize: %zu bytes\n", tmp->f.data.d.size);
			}
			k += (S_ALLOC(m_data) + tmp->f.data.d.size);
			tmp = (f_list *)((void *)tmp + k);
		}
		printf("----------------------------------------------------------\n");
		b = b->h_block.next;
	}
}