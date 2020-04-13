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
	block->h_block.used = block->h_block.used + S_ALLOC(f_list) + size;
 	delete_element_f_list(ptr);
	tmp = (f_list *)ptr;
	tmp->f.data.d.size = size;
	tmp->f.data.d.magic = MAGIC;
	return (void *)((void *)tmp + S_ALLOC(f_list));
}

static void		*find_available_in_f_list(size_t size) {
	f_list		*tmp;
	f_list		*min;
	m_block		*b;

	min = NULL;
	tmp = g_flist;
	while (tmp) {
		b = find_corresponding_block((void *)tmp);
		if (valid_current_block(b, size) == EXIT_SUCCESS && tmp->f.data.d.size >= size) {
			if (min == NULL || tmp->f.data.d.size < min->f.data.d.size)
				min = tmp;
		}
		tmp = tmp->f.next;
	}
	if (min != NULL) {
		if (min->f.data.d.size > size) {
			add_element_f_list((void *)min + S_ALLOC(f_list) + min->f.data.d.size, min->f.data.d.size - size);
		}
	}
	return (void *)min;
}

static void		*find_available_in_block(size_t size) {
	m_block		*b;
	f_list		*tmp;

	b = g_block;
	while (b) {
		if (valid_current_block(b, size) == EXIT_SUCCESS) {
			tmp = (void *)b + b->h_block.used;
			if (((void *)b + b->h_block.size) - (void *)tmp - size > S_ALLOC(f_list)) {
				return (void *)tmp;
			}
		}
		b = b->h_block.next;
	}
	return NULL;
}

void			*find_available_memory_chunk(size_t size) {
	f_list		*ret;

	if ((ret = find_available_in_f_list(size)) != NULL) {
		return write_meta_data((void *)ret, size);
	}
	if ((ret = find_available_in_block(size)) != NULL) {
		return write_meta_data((void *)ret, size);
	}
	return NULL;
}
