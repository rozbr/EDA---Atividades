
typedef struct NODE {
	int info;
	
	struct NODE *previous;
} node_t;

typedef struct {
	node_t *top;
} stack_t;

node_t* init_node(int info) {
	node_t *node;
	
	if ((node = malloc(sizeof(node_t)))) {
		node->info = info;
		
		return node;
	}
	
	exit(EXIT_FAILURE);
}

stack_t* init_stack() {
	stack_t *stack;
	
	if ((stack = malloc(sizeof(stack_t)))) {
		stack->top = NULL;
		
		return stack;
	}
	
	exit(1);
}

void push(stack_t *stack, int info) {
	node_t *node;
	
	if ((node = init_node(info))) {
		node->previous = stack->top;
		
		stack->top = node;
	}
}

int pop(stack_t *stack) {
	node_t *tmp;
	int info;

	if (stack->top) {
		tmp = stack->top;
		stack->top = stack->top->previous;
		
		info = tmp->info;
		
		free(tmp);
		tmp = NULL;
	}
	
	return info;
}

void print_stack(stack_t *stack) {
	node_t *node;
	
	node = stack->top;
	
	while (node) {
		printf("%d ", node->info);
		
		node = node->previous;
	}
}
