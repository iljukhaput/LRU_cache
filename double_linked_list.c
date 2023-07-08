
struct list_node_t {
	int *data;
	struct list_node_t *next;
	struct list_node_t *prev;
};

struct list_t {
	struct list_node_t *top;
	struct list_node_t *back;
};
	
