
#include <stdio.h>
#include <stdlib.h>

#include "../Matrices/matrix.h"

FILE* open_file(char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")))
        return file;
    
    exit(EXIT_FAILURE);
}

void update_adjacence_matrix(FILE *file, matrix_t *matrix) {
    int vertexA, vertexB;
    
    rewind(file);
    fscanf(file, "%d %d", &vertexA, &vertexB);
    
    while (!feof(file)) {
        fscanf(file, "%d %d", &vertexA, &vertexB);
        
        matrix->elements[vertexA - 1][vertexB - 1] = matrix->elements[vertexB - 1][vertexA - 1] = 1;
    }
}

int main(int argc, char **args) {
    FILE *file;
    int vertices, edges;
    
    file = open_file(args[1]);
    fscanf(file, "%d %d", &vertices, &edges);
    
    matrix_t *matrix;
    
    matrix = init_matrix(vertices, vertices);
    update_adjacence_matrix(file, matrix);
    
    puts("\n\t -- Matriz de Adjacência -- \n");
    print_matrix(matrix);
    
    return EXIT_SUCCESS;
}
