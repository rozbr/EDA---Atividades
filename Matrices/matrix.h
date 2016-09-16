
typedef struct {
    int rows;
    int cols;
    int **elements;
} matrix_t;

matrix_t* init_matrix(int rows, int cols) {
    int i;
    matrix_t *matrix;
    
    if ((matrix = malloc(sizeof(matrix_t)))) {
        matrix->rows = rows;
        matrix->cols = cols;
        
        if ((matrix->elements = malloc(sizeof(int *) * rows))) {
            for (i = 0; i < rows; i++)
                matrix->elements[i] = malloc(sizeof(int) * cols);
            
            return matrix;
        }
    }
    
    exit(EXIT_FAILURE);
}

void print_matrix(matrix_t *matrix) {
    int i, j;
    
    for (i = 0; i < matrix->rows; i++) {
        printf("\t");

        for (j = 0; j < matrix->cols; j++)
            printf("%4d ", matrix->elements[i][j]);
        
        puts("");
    }
    
    puts("");
}
