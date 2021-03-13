#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./data-structures/recipe.h"

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
        printf("%s -> %d\n", key, *map_get(ingredient_map_1, key));
        map_set(&comparison_map, key, *map_get(ingredient_map_1, key));
    }
    while (key = map_next(ingredient_map_2, &iter2))
    {
        printf("%s -> %d\n", key, *map_get(ingredient_map_2, key));
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
        printf("%s -> %d\n", key, *map_get(&comparison_map, key));
        sum += pow(*map_get(&comparison_map, key), 2);
        printf("Sum = %f\n", sum);
    }
    map_deinit(&comparison_map);
    return sqrt(sum);
}

int main(int argc, char const *argv[])
{
    // struct recipe rec1;
    // recipe_new(&rec1, 0, "Recipe A", "This is a cocktail that includes...", "Digestive, Refresher", "Bitter");
    // int percentages[] = {50, 10, 10, 20, 10};
    // char *ingredients[] = {"Water", "Coffee", "Sugar", "Cream", "Baileys"};
    // for (int i = 0; i < sizeof(percentages) / sizeof(*percentages); i++)
    // {
    //     add_ingredient(&rec1, ingredients[i], percentages[i]);
    // }
    // print_recipe(&rec1);
    // delete_recipe(&rec1);
    map_int_t map1;
    map_int_t map2;
    map_init(&map1);
    map_init(&map2);
    char *ingredients1[] = {"leche", "cereal"};
    char *ingredients2[] = {"leche", "cereal", "platano"};
    int percentages1[] = {50, 50};
    int percentages2[] = {45, 45, 10};
    for (int i = 0; i < sizeof(percentages1) / sizeof(*percentages1); i++)
    {
        map_set(&map1, ingredients1[i], percentages1[i]);
    }
    for (int i = 0; i < sizeof(percentages2) / sizeof(*percentages2); i++)
    {
        map_set(&map2, ingredients2[i], percentages2[i]);
    }
    printf("distance = %f", calculate_euclidean_distance(&map1, &map2));
    return 0;
}
