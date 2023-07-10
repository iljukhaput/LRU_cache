#ifndef _DOUBLE_LINEKED_LIST_
#define _DOUBLE_LINEKED_LIST_

struct list_t *list_create();
int list_size(const struct list_t *lst);
struct page_t *list_back_(struct list_t *lst);
void list_pop_back(struct list_t *lst);
void list_push_front_ (struct list_t *lst, struct page_t *q);
void list_move_upfront_(struct list_t *lst, struct list_node_t *p);
void list_free(struct list_t *lst);

#endif
