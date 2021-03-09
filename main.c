#include <stdlib.h>
#include <stdio.h>
#include "./data-structures/recipe.h"
#include "./data-structures/recipe.c"

int main(int argc, char const *argv[])
{
    struct recipe rec1;
    recipe_new(&rec1, 0, "Recipe A", "This is a cocktail that includes...", "Digestive, Refresher", "Bitter");
    int percentages[] = {50, 10, 10, 20, 10};
    char *ingredients[] = {"Water", "Coffee", "Sugar", "Cream", "Baileys"};
    for (int i = 0; i < sizeof(percentages); i++)
    {
        add_ingredient(&rec1, ingredients[i], percentages[i]);
    }
    print_recipe(&rec1);
    delete_recipe(&rec1);
    return 0;
}
