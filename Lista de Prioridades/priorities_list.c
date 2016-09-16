
#include <stdio.h>
#include <stdlib.h>

int pou(int base, int exp) {
    return exp ? base * pou(base, exp - 1) : 1;
}

typedef struct {
    int size;
    int max_size;
    int *elements;
} list_t;

void menu(int *option) {
    puts("\n\nEntre com o número da opção desejada:");
    puts("1 - Inserir elemento");
    puts("2 - Remover elemento");
    puts("3 - Imprimir lista");
    puts("0 - Finalizar execução");
    printf("\t-> ");
    
    scanf("%d", option);
}

int get_height(list_t *list) {
    int height, vertices, vertices_count;
    
    height = vertices_count = 0;
    vertices = list->size;
    
    while (vertices_count < vertices)
        vertices_count += pou(2, height++);
    
    return height;
}

list_t* init_list(int max_size) {
    list_t *list;
    
    if ((list = malloc(sizeof(list_t)))) {
        list->size = 0;
        list->max_size = max_size;
        
        if ((list->elements = malloc(sizeof(int) * max_size)))
            return list;
    }
    
    exit(EXIT_FAILURE);
}

void swap(list_t *list, int i, int j) {
    int aux;
    
    aux = list->elements[i];
    list->elements[i] = list->elements[j];
    list->elements[j] = aux;
}

void up(list_t *list, int index) {
    int parent = (index + 1) / 2 - 1;
    
    if (parent >= 0)
        if (list->elements[index] > list->elements[parent]) {
            swap(list, index, parent);

            up(list, parent);
        }
}

void down(list_t *list, int index) {
    int child = 2 * index + 1;
    
    if (child <= list->size) {
        if (child < list->size)
            if (list->elements[child + 1] > list->elements[child])
                child += 1;
        
        if (list->elements[child] > list->elements[index]) {
            swap(list, child, index);

            down(list, child);
        }
    }
}

void insert(list_t *list, int element) {
    if (list->size == list->max_size)
        puts("\nLista Cheia!");
    else {
        list->elements[list->size] = element;
        
        up(list, list->size++);
    }
}

void remove_(list_t *list) {
    list->elements[0] = list->elements[--list->size];
    
    down(list, 0);
}

void show_list(list_t *list) {
    int i;
    
    if (!list->size)
        printf("\nLista vazia!");
    else {
        printf("\n\tLista: ");
        
        for (i = 0; i < list->size; i++)
            printf("%d ", list->elements[i]);
    }
    
    puts("");
}

void show_tree(list_t *list, int height) {
    int max_spaces, i, n, width, position, j, index = 0;

    max_spaces = 4 * pou(2, height - 1);
    
    for (i = 0; i < height; i++) {
        n = pou(2, i);
        width = max_spaces / n;
        position = width / 2 + 2;
        
        for (j = 0; j < n; j++) {
            if (index > list->size - 1) break;
            
            printf("%*d", position, list->elements[index++]);
            printf("%*c", width - position, ' ');
        }
        
        puts("");
    }
}


int get_value() {
    int value;
    
    printf("\nEntre com um número: ");
    scanf("%d", &value);
    
    return value;
}

int main() {
    int option;
    list_t *list;
    
    printf("\n -- Tamanho da Lista -- ");
    
    list = init_list(get_value());
    
    menu(&option);
    
    while (option) {
        switch (option) {
            case 1:
                insert(list, get_value());
            break;
                
            case 2:
                remove_(list);
            break;
                
            case 3:
//                show_list(list);
                show_tree(list, get_height(list));
            break;
        }
        
        menu(&option);
    }
}
