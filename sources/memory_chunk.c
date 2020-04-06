#include "../includes/malloc.h"

void			*write_meta_data(void *ptr, size_t size) {
	f_list *tmp;
	
	tmp = (f_list *)ptr;
	tmp->f.data.d.size = size;
	tmp->f.data.d.magic = MAGIC;
	delete_element_f_list(ptr);
	// add_element_f_list(size);
	return (void *)ptr + S_ALLOC(m_data);
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
