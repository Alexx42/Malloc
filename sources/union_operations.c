#include "../includes/malloc.h"

void		delete_element_f_list(void *ptr) {
	f_list		*tmp;
	f_list		*prev;

	tmp = g_flist;
	prev = NULL;
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

static int	is_in_f_list(void *ptr) {
	f_list *tmp;

	tmp = g_flist;
	while (tmp) {
		if ((void *)tmp == ptr)
			return EXIT_SUCCESS;
		tmp = tmp->f.next;
	}
	return EXIT_FAILURE;
}

void		add_element_f_list(void *ptr, size_t size) {
	f_list		*node;
	f_list		*fast;

	node = (f_list *)ptr;
	if (is_in_f_list((void *)node) == EXIT_SUCCESS)
		return ;
	node->f.data.d.magic = MAGIC;
	node->f.data.d.size = size;
	node->f.next = NULL;
	if (g_flist == NULL) {
		g_flist = node;
		return ;
	}
	fast = g_flist;
	while (fast->f.next)
		fast = fast->f.next;
	fast->f.next = node;
	return ;
}