#include <stdlib.h>
#include <stdio.h>
#include "./data-structures/recipe.h"

void fileReader()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int index = 0;
    int ingredients = 0;

    fp = fopen("./recepies.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    struct recipe rec1[100];

    while ((read = getline(&line, &len, fp)) != -1)
    {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if (line[0] == '\n')
        {
            ingredients = 0;
            print_recipe(&rec1[index]);
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
            printf("%s\n", ptr);

            if (strcmp(ptr, "Recipe") == 0)
            {
                ptr = strtok(NULL, delim);
                printf("%s\n", ptr);
                if (!(rec1[index].name = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].name, ptr);
            }
            if (strcmp(ptr, "Description") == 0)
            {
                ptr = strtok(NULL, delim);
                printf("%s\n", ptr);
                if (!(rec1[index].description = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].description, ptr);
            }
            if (strcmp(ptr, "Categories") == 0)
            {
                ptr = strtok(NULL, delim);
                printf("%s\n", ptr);
                if (!(rec1[index].categories = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].categories, ptr);
            }
            if (strcmp(ptr, "Profile") == 0)
            {
                ptr = strtok(NULL, delim);
                printf("%s\n", ptr);
                if (!(rec1[index].profile = malloc(strlen(ptr) + 1))) //+1 is to make room for the NULL char that terminates C strings
                {
                    break;
                }
                strcpy(rec1[index].profile, ptr);
            }
            if (ingredients == 1)
            {
                char * perecentage = malloc(strlen(ptr) + 1);
                perecentage = strtok(NULL, delim);
                perecentage[strlen(perecentage) - 1] = 0;
                int per = atoi(perecentage);
                printf("%d\n", per);
                //add_ingredient(&rec1[index], ptr, per);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    struct recipe rec1;
    fileReader();
    // recipe_new(&rec1, 0, "Recipe A", "This is a cocktail that includes...", "Digestive, Refresher", "Bitter");
    // int percentages[] = {50, 10, 10, 20, 10};
    // char *ingredients[] = {"Water", "Coffee", "Sugar", "Cream", "Baileys"};
    // for (int i = 0; i < sizeof(percentages)/sizeof(*percentages); i++)
    // {
    //     add_ingredient(&rec1, ingredients[i], percentages[i]);
    // }
    // print_recipe(&rec1);
    // delete_recipe(&rec1);
    return 0;
}
