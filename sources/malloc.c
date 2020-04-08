#include "../includes/malloc.h"

m_block			*g_block = NULL;
f_list			*g_flist = NULL;


void			*my_malloc(size_t size) {
	void	*ptr;

	if (size <= 0)
		return NULL;
	ptr = NULL;
	// I guess the free list doesnt work
	if((ptr = find_available_memory_chunk(size)) == NULL) {
		if ((ptr = allocate_new_block(size)) == NULL)
			return NULL;
	}
	dump_block();
	return ptr;
}

int				main(void) {
	void *ptr = my_malloc(10);
	(void)ptr;
	my_free(ptr);
	ptr = my_malloc(5);
	void *ptr2 = my_malloc(10);
	(void)ptr2;
	return  0;
}
