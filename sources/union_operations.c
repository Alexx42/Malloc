#include "../includes/malloc.h"

void		delete_element_f_list(void *ptr) {
	f_list		*tmp;
	f_list		*prev;

	tmp = g_flist;
	if (tmp != NULL && (void *)tmp == ptr) {
		g_flist = tmp->f.next;
		return ;
	}
	while (tmp != NULL && (void *)tmp != ptr) {
		prev = tmp;
		tmp = prev->f.next;
	}
	if (tmp == NULL)
		return ;
	prev->f.next = tmp->f.next;
}

// static int	is_in_f_list(void *ptr) {
// 	f_list *tmp;

// 	tmp = g_flist;
// 	while (tmp) {
// 		if ((void *)tmp == ptr)
// 			return EXIT_SUCCESS;
// 		tmp = tmp->f.next;
// 	}
// 	return EXIT_FAILURE;
// }

// void		add_element_f_list(void *ptr, size_t size) {
// 	f_list		*node;

// 	node = (void *)ptr + S_ALLOC(m_data) + size;
// 	if (is_in_f_list((void *)node) == EXIT_FAILURE || node->f.data.d.magic ==  MAGIC)
// 		return ;
// 	node->f.data.d.magic = MAGIC;
// 	node->f.data.d.size = 
// }