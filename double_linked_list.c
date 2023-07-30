#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list.h"

struct page_t *page_create(int num)
{
	struct page_t *p_page = malloc(sizeof(struct page_t));
	p_page->num = num;
	return p_page;
}

struct list_node_t *node_create(struct page_t *p)
{
	struct list_node_t *p_list = malloc(sizeof(struct list_node_t));
	p_list->data = p;
	p_list->next = NULL;
	p_list->prev = NULL;
	return p_list;
}

void node_free(struct list_node_t *node_t)
{
	free(node_t);
	node_t = NULL;
}

struct list_t *list_create()
{
	struct list_t *p_list_t = malloc(sizeof(struct list_t));
	p_list_t->top = NULL;
	p_list_t->back = NULL;
	return p_list_t;
 
}

int list_size(const struct list_t *lst)
{
	if (!lst->top) {
		return 0;
	}

	int size = 1;
	struct list_node_t *tmp = lst->top;
	while (tmp->prev != NULL) {
		tmp = tmp->prev;
		size++;
	}

	return size;
}

struct page_t *list_back(struct list_t **lst)
{
	if (!(*lst)->top) {
		return 0;
	}
	return (*lst)->back->data;
}

void list_pop_back(struct list_t *lst)
{
	if (!lst->back) {
		// printf("List is empty\n");
		return;
	}
	struct list_node_t *tmp = lst->back;
	if (!lst->top) {
		return;
	} else if (lst->top != lst->back) {
		lst->back->next->prev = NULL;
		lst->back = lst->back->next;
	} else {
		lst->back = NULL;
		lst->top = NULL;
	}
	free(tmp->data);
	free(tmp);
}

void list_push_front(struct list_t *lst, struct page_t *q)
{
	struct list_node_t *new_node = node_create(q);
	if (lst->top) {
		// list is not empty
		lst->top->next = new_node;
		new_node->prev = lst->top;
	} else {
		// list is empty
		lst->back = new_node;
	}
	lst->top = new_node;
}

void list_move_upfront(struct list_t *lst, struct list_node_t *p)
{
	if (lst->top == lst->back || !p->next) {
		return;
	} else if (!p->prev) {
		lst->back = p->next;
		lst->back->prev = NULL;
	} else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	p->next = NULL;
	p->prev = lst->top;
	lst->top = p;
	lst->top->prev->next = lst->top;
}

void list_free(struct list_t **lst)
{
	if (!(*lst)->top) {
		return;
	}
	struct list_node_t *tmp = (*lst)->top;
	while ((*lst)->top) {
		tmp = (*lst)->top;
		(*lst)->top = (*lst)->top->prev;
		node_free(tmp);
	}
	// we will free the list at the end of the programm
	// free(*lst);
	// *lst = NULL;
}

void list_print(const struct list_t *lst)
{
	if (!lst->top){
		printf("List is empty\n");
		return;
	}
	struct list_node_t *tmp = lst->top;
	while (tmp) {
		printf("%d ", tmp->data->num); 
		tmp = tmp->prev;
	}
	printf("\n");
}

