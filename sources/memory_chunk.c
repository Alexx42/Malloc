#include "../includes/malloc.h"

int		valid_current_block(m_block *block, size_t size) {
	if (block->h_block.size == (size_t)TINY_ZONE && size > TINY_MAX_SIZE)
		return EXIT_FAILURE;
	else if (block->h_block.size == (size_t)SMALL_ZONE && size > SMALL_MAX_SIZE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void			*write_meta_data(void *ptr, size_t size) {
	f_list		*tmp;
	m_block		*block;

	block = find_corresponding_block(ptr);
	block->h_block.used += S_ALLOC(f_list) + size;
	delete_element_f_list(ptr);
	tmp = (f_list *)ptr;
	tmp->f.data.d.size = size;
	tmp->f.data.d.magic = MAGIC;
	if (block->h_block.size == (size_t)SMALL_ZONE || block->h_block.size == (size_t)TINY_ZONE) {}
		add_element_f_list(ptr, size, block->h_block.size - block->h_block.used);
	return (void *)((void *)tmp + S_ALLOC(f_list));
}

void			*find_available_memory_chunk(size_t size) {
	f_list		*tmp;
	m_block		*b;

	tmp = g_flist;
	while (tmp) {
		b = find_corresponding_block((void *)tmp);
		if (valid_current_block(b, size) == EXIT_SUCCESS && tmp->f.data.d.size > size)
			return write_meta_data((void *)(tmp), size);
		tmp = tmp->f.next;
	}
	return NULL;
}
