#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "./data-structures/recipe.h"
#include "./data-structures/edge.h"

char* trimWhitespace(char *str)
{
    char *end;
    
    // Leading whitespace
    while(isspace(*str)) str++;
    
    if(*str == 0) return str;

    // Trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;

    end[1] = '\0';
    return str;
}

int isBlankLine(const char *line)
{
    int isBlank = 1;
    for (const char *ch = (char *)line; *ch != '\0'; ++ch)
    {
        if (!isspace(*ch))
        {
            isBlank = 0;
            break;
        }
    }

    return isBlank;
}

struct recipe *fileReader(int* n)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    int index = 0;
    int ingredients = 0;
    int sumOfIngredients = 0;

    fp = fopen("./recepies.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    struct recipe *rec1 = malloc(sizeof(struct recipe) * 100);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        #ifdef DEBUG
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        #endif

        if (isBlankLine(line) == 1)
        {
            if (sumOfIngredients != 100) {
                printf("Bad recipe format (Recipe: %s), discarding...\n", rec1[index].name);
                ingredients = 0;
                sumOfIngredients = 0;
                strcpy(rec1[index].name, "");
                strcpy(rec1[index].categories, "");
                strcpy(rec1[index].description, "");
                strcpy(rec1[index].profile, "");
                map_init(&rec1[index].ingredients);
                continue;
            }
            #ifdef DEBUG
            print_recipe(&rec1[index]);
            #endif
            ingredients = 0;
            sumOfIngredients = 0;
            rec1[index].id = index;
            index = index + 1;
            continue;
        }

        char delim[] = ":";
        char *ptr = strtok(line, delim);

        if (strcmp(ptr, "Ingredients") == 0)
        {
            ingredients = 1;
            continue;
        }

        if (ptr != NULL)
        {
            #ifdef DEBUG
            printf("%s\n", ptr);
            #endif

            if (strcmp(ptr, "Recipe") == 0)
            {
                ptr = strtok(NULL, delim);
                #ifdef DEBUG
                printf("%s\n", ptr);
                #endif
                if (!(rec1[index].name = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].name, ptr);
                rec1[index].name = trimWhitespace(rec1[index].name);
            }
            if (strcmp(ptr, "Description") == 0)
            {
                ptr = strtok(NULL, delim);
                #ifdef DEBUG
                printf("%s\n", ptr);
                #endif
                if (!(rec1[index].description = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].description, ptr);
                rec1[index].description = trimWhitespace(rec1[index].description);
            }
            if (strcmp(ptr, "Categories") == 0)
            {
                ptr = strtok(NULL, delim);
                #ifdef DEBUG
                printf("%s\n", ptr);
                #endif
                if (!(rec1[index].categories = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].categories, ptr);
                rec1[index].categories = trimWhitespace(rec1[index].categories);
            }
            if (strcmp(ptr, "Profile") == 0)
            {
                ptr = strtok(NULL, delim);
                #ifdef DEBUG
                printf("%s\n", ptr);
                #endif
                if (!(rec1[index].profile = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].profile, ptr);
                rec1[index].profile = trimWhitespace(rec1[index].profile);
            }
            if (ingredients == 1)
            {
                char *perecentage = malloc(strlen(ptr) + 1);
                perecentage = strtok(NULL, delim);
                perecentage[strlen(perecentage) - 1] = 0;
                int per = atoi(perecentage);
                #ifdef DEBUG
                printf("Adding (%s, %d)\n", ptr, per);
                #endif
                sumOfIngredients += per;
                add_ingredient(&rec1[index], ptr, per);
            }
        }
    }

    *n = index;
    return rec1;
}

double calculate_euclidean_distance(map_int_t *ingredient_map_1, map_int_t *ingredient_map_2)
{
    double sum = 0;
    map_int_t comparison_map;
    map_init(&comparison_map);
    const char *key;
    map_iter_t iter1 = map_iter(ingredient_map_1);
    map_iter_t iter2 = map_iter(ingredient_map_2);
    map_iter_t iter3 = map_iter(&comparison_map);
    while (key = map_next(ingredient_map_1, &iter1))
    {
        #ifdef DEBUG
        printf("%s -> %d\n", key, *map_get(ingredient_map_1, key));
        #endif
        map_set(&comparison_map, key, *map_get(ingredient_map_1, key));
    }
    while (key = map_next(ingredient_map_2, &iter2))
    {
        #ifdef DEBUG
        printf("%s -> %d\n", key, *map_get(ingredient_map_2, key));
        #endif
        int *current_value = map_get(&comparison_map, key), new_value;
        if (current_value != NULL)
        {
            new_value = *current_value - *map_get(ingredient_map_2, key);
        }
        else
        {
            new_value = *map_get(ingredient_map_2, key);
        }
        map_set(&comparison_map, key, new_value);
    }
    while (key = map_next(&comparison_map, &iter3))
    {
        #ifdef DEBUG
        printf("%s -> %d\n", key, *map_get(&comparison_map, key));
        #endif
        sum += pow(*map_get(&comparison_map, key), 2);
        #ifdef DEBUG
        printf("Sum = %f\n", sum);
        #endif
    }
    map_deinit(&comparison_map);
    return sqrt(sum);
}


void printGraph(int iNum, struct edge** adjMat){
    FILE *ptr;
    ptr = fopen("graph.gv", "w");
    if(ptr == NULL) {
        printf("Erro al abrir archivo de visualización\n");
        return; 
    }

    fputs("graph G {\n", ptr);

    for(int i = 0; i < iNum; i++){
        for(int j = 0; j <iNum; j++){
            if(i < j && i != j && adjMat[i][j].weight != 0){
                #ifdef DEBUG
                printf("%s %s %f\n", adjMat[i][j].source, adjMat[i][j].dest, adjMat[i][j].weight);
                #endif
                fprintf(ptr, " \" %s \" -- \" %s \" [label = \" %f \"  fontsize = 10.0 color = blue]; \n", adjMat[i][j].source, adjMat[i][j].dest, adjMat[i][j].weight);
            }
        }
    }

    fputs("}", ptr);
    printf("Corra el comando: dot -Tpng graph.gv -o graph.png y Abra el archivo graph.png\n");
    fclose(ptr);
}

int main(int argc, char const *argv[])
{
    int n = 0;
    struct recipe *rec1;
    rec1 = fileReader(&n);

    printf("No. of recipes: %d\n", n);
    struct edge **adjMat = malloc(n * sizeof(struct edge*)); 
    for (int i = 0; i < n; i++) {
        adjMat[i] = malloc(n * sizeof(struct edge)); 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            set_source(&adjMat[i][j], rec1[i].name);
            set_dest(&adjMat[i][j], rec1[j].name);

            set_weight(&adjMat[i][j], (i == j) ? 0 
                : calculate_euclidean_distance(
                    &rec1[i].ingredients, &rec1[j].ingredients));
        }
    }

    printGraph(n, adjMat);

    #ifdef DEBUG
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            print_edge(&adjMat[i][j]);
            printf("-------------\n");
        }
    }
    #endif

    return 0;
}
