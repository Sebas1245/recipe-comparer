#include <stdlib.h>
#include <stdio.h>
#include "./data-structures/recipe.h"



void fileReader() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;


    char * recipe;
    char * description;
    char * categories;
    char * profile;

    int ingredients = 0;

    fp = fopen("./recepies.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    struct recipe rec1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if (line[0] == '\n') {
            recipe_new(&rec1, 0, recipe, description, categories, profile);
            print_recipe(&rec1);
            continue;
        }
        if (strcmp(line, "Ingredients") == 0) {
            ingredients = 1;
            continue;
        }

	    char delim[] = ":";
	    char *ptr = strtok(line, delim);

	    if(ptr != NULL)
	    {
		    printf("'%s'\n", ptr);
		    ptr = strtok(NULL, delim);
            if (strcmp(ptr, "Recipe") == 0) {
                ptr = strtok("\n", delim);
                recipe = ptr;
            }
            if (strcmp(ptr, "Description") == 0) {
                ptr = strtok("\n", delim);
                description = ptr;
            } 
            if (strcmp(ptr, "Categories") == 0) {
                ptr = strtok("\n", delim);
                categories = ptr;
            } 
            if (strcmp(ptr, "Profile") == 0) {
                ptr = strtok("\n", delim);
                profile = ptr;
            }  

            if (ingredients == 1) {
                 char *perecentage  = strtok("\n", delim);

                 int per = atoi(perecentage);
                 add_ingredient(&rec1, ptr, per);
            }
	    }

    }
}

int main(int argc, char const *argv[])
{
    struct recipe rec1;
    recipe_new(&rec1, 0, "Recipe A", "This is a cocktail that includes...", "Digestive, Refresher", "Bitter");
    int percentages[] = {50, 10, 10, 20, 10};
    char *ingredients[] = {"Water", "Coffee", "Sugar", "Cream", "Baileys"};
    for (int i = 0; i < sizeof(percentages)/sizeof(*percentages); i++)
    {
        add_ingredient(&rec1, ingredients[i], percentages[i]);
    }
    print_recipe(&rec1);
    delete_recipe(&rec1);
    return 0;
}
