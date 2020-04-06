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
	char *ptr = my_malloc(10);
	char *ptr2 = my_malloc(1000000);
	char *ptr3 = my_malloc(15000);
	ptr[0] = 'a';
	ptr[1] = 'b';
	ptr[2] = '\0';
	ptr2[0] = 'a';
	ptr2[1] = 'b';
	ptr2[2] = '\0';
	printf("%s\n", ptr);
	printf("%s\n", ptr2);
	(void)ptr3;
	return  0;
}
