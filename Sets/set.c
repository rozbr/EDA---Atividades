
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
	
	exit(EXIT_FAILURE);
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

int connected_components(node_t **sets, int count) {
	int *roots, *unique_roots, *unique_roots_flag;
	int i, j, unique_roots_size = 1, components = 0;

	roots = malloc(sizeof(int) * count);
	unique_roots = malloc(sizeof(int));

	roots[0] = unique_roots[0] = search(sets[0]);

	for (i = 1; i < count; i++)
	    roots[i] = search(sets[i]);

    for (i = 0; i < count; i++){
        for (j = 0; j < unique_roots_size; j++) {
            if (roots[i] == unique_roots[j])
                break;

            unique_roots = realloc(unique_roots, sizeof(int) * (unique_roots_size + 1));
            unique_roots[unique_roots_size++] = roots[i];

            break;
        }
    }

    unique_roots_flag = calloc(unique_roots_size, sizeof(int));

    for (j = 0; j < count; j++)
        for (i = 0; i < unique_roots_size; i++)
            if (unique_roots[i] == roots[j]) {
                unique_roots_flag[i] = 1;
                
                break;
            }
                
    for (i = 0; i < unique_roots_size; i++)
        if (unique_roots_flag[i])
            components += 1;

    return components;
}

int main() {
	int v[] = {1, 2, 3, 4, 5, 6};
	node_t **sets;
	
	sets = generate(v, 6);
	
	fuse(sets[0], sets[2]);
	fuse(sets[4], sets[5]);
	fuse(sets[0], sets[4]);
    fuse(sets[0], sets[3]);
	fuse(sets[1], sets[0]);
	
	printf("Caminho de 6 a 1: ");
	get_a_way(get_src_node(sets, 6, 6), 1);
	
	printf("\nComponentes conexas: %d\n", connected_components(sets, 6));
	
	return EXIT_SUCCESS;
}
