
#include <stdio.h>
#include <stdlib.h>

#include "../Matrices/matrix.h"


FILE* open_file(char *filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r")))
        return file;
    
    exit(EXIT_FAILURE);
}

void update_incidence_matrix(FILE *file, matrix_t *matrix) {
    int j, vertexA, vertexB;
    
    for (j = 0; j < matrix->cols; j++) {
        fscanf(file, "%d %d", &vertexA, &vertexB);
        
//        matrix->elements[vertexA - 1][j] = matrix[vertexB - 1][j] = 1;
        matrix->elements[vertexA - 1][vertexB - 1] = 1;
    }
}

int main(int argc, char **args) {
    FILE *file;
    matrix_t *matrix;
    int vertices, edges;

    file = open_file(args[1]);
    
    fscanf(file, "%d %d", &vertices, &edges);
    
    matrix = init_matrix(vertices, edges);
    update_incidence_matrix(file, matrix);
    
    puts("\n\t -- Matriz de Incidência -- \n");
    print_matrix(matrix);
    
    fclose(file);
}
