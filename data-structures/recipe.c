#include <stdlib.h>
#include <stdio.h>
#include "recipe.h"

void recipe_new(
    struct recipe *new_recipe,
    int id,
    char *name,
    char *desc,
    char *categories,
    char *profile
)
{
    map_init(&new_recipe->ingredients);
    set_id(new_recipe, id);
    set_name(new_recipe, name);
    set_description(new_recipe, desc);
    set_categories(new_recipe, categories);
    set_profile(new_recipe, profile);
}
void set_id(struct recipe *rec, int id)
{
    rec->id = id;
}
void set_name(struct recipe *rec, char *name)
{
    rec->name = name;
}
void set_description(struct recipe *rec, char *desc)
{
    rec->description = desc;
}
void set_categories(struct recipe *rec, char *categories)
{
    rec->categories = categories;
}
void set_profile(struct recipe *rec, char *profile)
{
    rec->profile = profile;
}
void add_ingredient(struct recipe *rec, char *new_ingredient, int percentage)
{
    map_set(&rec->ingredients, new_ingredient, percentage);
}

void delete_recipe(struct recipe *rec)
{
    map_deinit(&rec->ingredients);
}

void print_recipe(struct recipe *rec)
{
    printf("Trying to print recipe...\n");
    printf("%s", rec->name);
    printf("%s", rec->description);
    printf("Categories: %s", rec->categories);
    printf("Profile: %s", rec->profile);
    char *key;
    map_iter_t iter = map_iter(&rec->ingredients);
    while (key == map_next(&rec->ingredients, &iter))
    {
        printf("%s -> %d\n", key, *map_get(&rec->ingredients, key));
    }
}