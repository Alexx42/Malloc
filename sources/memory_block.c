#include "../includes/malloc.h"

static size_t		size_to_allocate(size_t size) {
	if (size <= TINY_MAX_SIZE) {
		return TINY_ZONE;
	} else if (size <= SMALL_MAX_SIZE) {
		return SMALL_ZONE;
	}
	return size + S_ALLOC(f_list) + S_ALLOC(m_block);
}

void				*allocate_new_block(size_t size) {
	m_block			*block;
	m_block			*fast;
	size_t			size_block;

	size_block = size_to_allocate(size);
	block = MMAP_ALLOC(size_block);
	block->h_block.next = NULL;
	block->h_block.used = S_ALLOC(m_block);
	block->h_block.size = size_block;
	if (g_block == NULL) {
		g_block = block;
		fast = g_block;
	} else {
		fast = g_block;
		while (fast->h_block.next)
			fast = fast->h_block.next;
		fast->h_block.next = block;
	}
	return write_meta_data((void *)block + S_ALLOC(m_block), size);
}


m_block			*find_corresponding_block(void *ptr) {
	m_block *tmp;

	tmp = g_block;
	while (tmp) {
		if (ptr > (void *)tmp && ptr < (void *)tmp + tmp->h_block.size)
			return tmp;
		tmp = tmp->h_block.next;
	}
	return NULL;
}