#ifndef _DOUBLE_LINEKED_LIST_
#define _DOUBLE_LINEKED_LIST_

struct list_t *list_create();
int list_size(const struct list_t *lst);
int *list_back(struct list_t *lst);
void list_pop_back(struct list_t *lst);
void list_push_front (struct list_t *lst, int *q);
void list_move_upfront(struct list_t *lst, struct list_node_t *p);
void list_free(struct list_t *lst);

#endif
