
#include <stdio.h>
#include <stdlib.h>

#include "../Queues/queue.h"

FILE* open_file(char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")))
        return file;
    
    puts("\nErro ao abrir o arquivo!");
    
    exit(EXIT_FAILURE);
}

queue_t** generate_adjacence_list(int vertices) {
    int i;
    queue_t **queues;
    
    if ((queues = malloc(sizeof(queue_t *) * vertices))) {
        for (i = 0; i < vertices; i++)
            queues[i] = init_queue();
    
        return queues;
    }
    
    puts("\nErro ao realizar alocamento!");
    
    exit(EXIT_FAILURE);
}

void update_adjacence_list(FILE *file, queue_t **queues) {
    int i, edges, vertexA, vertexB;
    
    rewind(file);
    fscanf(file, "%d %d", &vertexA, &edges);
    
    for (i = 0; i < edges; i++) {
        fscanf(file, "%d %d", &vertexA, &vertexB);
        
        enqueue(queues[vertexA - 1], vertexB);
        enqueue(queues[vertexB - 1], vertexA);
    }
}

void print_queues(queue_t **queues, int vertices) {
    int i;
    
    for (i = 0; i < vertices; i++){
        printf("\t%d ", vertices);
    
        print_queue(queues[i]);
    }
    
    puts("");
}

int main(int argc, char **args) {
    FILE *file;
    int vertices, edges;
    queue_t **adjacence_list;
    
    file = open_file(args[1]);
    
    fscanf(file, "%d %d", &vertices, &edges);
    
    adjacence_list = generate_adjacence_list(vertices);
    update_adjacence_list(file, adjacence_list);
    
    puts("\n\t -- Lista de Adjacência -- \n");
    print_queues(adjacence_list, vertices);
    
    fclose(file);
    
    return EXIT_SUCCESS;
}
