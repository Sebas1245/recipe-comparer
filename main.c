#include <stdlib.h>
#include <stdio.h>
#include "./data-structures/recipe.h"




recipe_new* fileReader() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;


    char * recipe;
    char * description;
    char * categories;
    char * profile;

    fp = fopen("./recepies.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if (strcmp(line, "\n") == 0) {
            continue;
        }
        if (strcmp(line, "Ingredients") == 0) {
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
