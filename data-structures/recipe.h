#ifndef RECIPE_h
#define RECIPE_h

#include <stdlib.h>
#include "./map-master/src/map.h"
#include "./map-master/src/map.c"

struct recipe
{
    int id;
    const char *name;
    const char *description;
    const char *categories;
    const char *profile;
    map_int_t ingredients;
};

void recipe_new(
    struct recipe *new_recipe,
    int id,
    const char *name,
    const char *desc,
    const char *categories,
    const char *profile);
void set_id(struct recipe *rec, int id);
void set_name(struct recipe *rec, const char *name);
void set_description(struct recipe *rec, const char *desc);
void set_categories(struct recipe *rec, const char *categories);
void set_profile(struct recipe *rec, const char *profile);
void add_ingredient(struct recipe *rec, const char *new_ingredient_name, int percentage);
void delete_recipe(struct recipe *rec);
void print_recipe(struct recipe *rec);

#endif
