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
	char *ptr2 = my_malloc(5000);
	char *ptr3 = my_malloc(15000);
	ptr[0] = 'a';
	ptr[1] = 'b';
	ptr[2] = '\0';
	ptr2[0] = 'P';
	ptr3[0] = 'a';
	ptr3[1] = 'b';
	ptr3[2] = '\0';
	printf("ptr1: %s\nptr2: %s\nptr3: %s\n", ptr, ptr2, ptr3);
	return  0;
}
