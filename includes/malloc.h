#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>

# define PAGE_SIZE getpagesize()

# define TINY_ZONE PAGE_SIZE * 16
# define SMALL_ZONE TINY_ZONE * 16

# define TINY_MAX_SIZE 512
# define SMALL_MAX_SIZE (TINY_MAX_SIZE * 16)

# define MMAP_ALLOC(SIZE) (mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0))

# define S_ALLOC(x) (sizeof(x))

# define MAGIC 0xA028092019


/*
** We align the memory with long
*/
typedef long align;

/* Align the memory*/
typedef union			block {
	struct head_block{
		size_t			size;
		size_t			used;
		union block		*next;
	} h_block;
	align				x;
}						m_block;

typedef union 			data {
	struct {
		size_t			size;
		size_t			magic;
	} d;
	align				x;
}						m_data;

typedef union 			free_list {
	struct {
		m_data			data;
		union free_list	*next;
	} f;
	align				x;
}						f_list;

extern m_block			*g_block;
extern f_list			*g_flist;


void	my_free(void *ptr);

void					*allocate_new_block(size_t size);
m_block					*find_corresponding_block(void *ptr);


void					dump_block(void);


void					*find_available_memory_chunk(size_t size);
void					*write_meta_data(void *ptr, size_t size);



void					delete_element_f_list(void *ptr);
void					add_element_f_list(void *ptr, size_t size);


int						valid_current_block(m_block *block, size_t size);

extern void				*malloc(size_t size);
extern void				free(void  *ptr);