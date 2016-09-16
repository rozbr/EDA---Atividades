
typedef struct NODE {
    int info;
    
    struct NODE *next;
} node_t;

typedef struct {
    node_t *first;
    node_t *last;
} queue_t;

node_t* init_node(int info) {
    node_t *node;
    
    if ((node = malloc(sizeof(node_t)))) {
        node->info = info;
        node->next = NULL;
        
        return node;
    }
    
    exit(EXIT_FAILURE);
}

queue_t* init_queue() {
    queue_t *queue;
    
    if ((queue = malloc(sizeof(queue_t)))) {
        queue->first = queue->last = NULL;
        
        return queue;
    }
    
    exit(EXIT_FAILURE);
}

void enqueue(queue_t *queue, int info) {
    node_t *node;
    
    node = init_node(info);
    
    if (!queue->first)
        queue->first = queue->last = node;
    else {
        queue->last->next = node;
        queue->last = node;
    }
}

void print_queue(queue_t *queue) {
    node_t *node;
    
    node = queue->first;
    
    while (node) {
        printf("~> %d ", node->info);
        
        node = node->next;
    }
    
    puts("");
}
