
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int info;
	
	struct NODE *parent;
} node_t;

node_t* init_node(int info) {
	node_t *node;
	
	if ((node = malloc(sizeof(node_t)))) {
		node->info = info;
		
		return node;
	}
	
	exit(1);
}

node_t** generate(int *elements, int count) {
	int i;
	node_t **sets;
	
	if ((sets = malloc(sizeof(node_t *) * count))) {
		for (i = 0; i < count; i++)
			sets[i] = init_node(elements[i]);
			
		return sets;
	}
	
	exit(1);
}

void fuse(node_t *a, node_t *b) {
	b->parent = a;
}

int search(node_t *node) {
	node_t *tmp;

	if (node)
		tmp = node;
		
	while (tmp->parent)
		tmp = tmp->parent;
		
	return tmp->info;
}

node_t* get_a_way(node_t *node, int dst) {
	node_t* tmp;

	if (!node)
		return NULL;
		
	if (node->info == dst) {
		printf("%d ", dst);

		return node;
	}
	else
		tmp = get_a_way(node->parent, dst);
		
	if (tmp)
		printf("%d ", node->info);
		
	return tmp;
}

node_t* get_src_node(node_t **sets, int count, int src) {
	int i;
	
	for (i = 0; i < count; i++)
		if (sets[i]->info == src)
			return sets[i];
			
	return NULL;
}

int main() {
	int v[] = {1, 2, 3, 4, 5, 6};
	node_t **sets;
	
	sets = generate(v, 6);
	
	fuse(sets[0], sets[2]);
	fuse(sets[4], sets[5]);
	fuse(sets[0], sets[4]);
	fuse(sets[0], sets[3]);
	
	get_a_way(get_src_node(sets, 6, 6), 1);
	
	return 0;
}
