#include "../includes/malloc.h"

void			*write_meta_data(void *ptr, size_t size) {
	f_list		*tmp;
	m_block		*block;

	block = find_corresponding_block(ptr);
	block->h_block.used += S_ALLOC(f_list) + size;
	delete_element_f_list(ptr);
	tmp = (f_list *)ptr;
	tmp->f.data.d.size = size;
	tmp->f.data.d.magic = MAGIC;
	add_element_f_list(ptr, size, block->h_block.size - block->h_block.used);
	return (void *)((void *)tmp + S_ALLOC(f_list));
}

void			*find_available_memory_chunk(size_t size) {
	f_list		*tmp;

	tmp = g_flist;
	while (tmp) {
		if (tmp->f.data.d.size > size)
			return write_meta_data((void *)(tmp), size);
		tmp = tmp->f.next;
	}
	return NULL;
}
