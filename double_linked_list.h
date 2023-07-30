#ifndef _DOUBLE_LINEKED_LIST_
#define _DOUBLE_LINEKED_LIST_

struct page_t;
struct list_node_t;
struct list_t;

void list_info(const struct list_t *lst);
struct list_node_t *find_node(const struct list_t *lst, int val);
int get_num(const struct page_t *p_page);

struct list_t *list_create();
int list_size(const struct list_t *lst);
struct page_t *list_back(struct list_t **lst);
void list_pop_back(struct list_t *lst);
void list_push_front(struct list_t *lst, struct page_t *q);
void list_move_upfront(struct list_t *lst, struct list_node_t *p);
void list_free(struct list_t **lst);
struct page_t *page_create(int num);
void list_print(const struct list_t *lst);

#endif
