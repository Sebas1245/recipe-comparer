#ifndef RECIPE_H
#define RECIPE_H

#include <stdlib.h>

#include "./map-master/src/map.h"

struct recipe {
  int id;
  char *name;
  char *description;
  char *categories;
  char *profile;
  map_int_t ingredients;
};

void recipe_new(struct recipe *new_recipe, int id, char *name,
                char *desc, char *categories, char *profile);
void set_id(struct recipe *rec, int id);
void set_name(struct recipe *rec, char *name);
void set_description(struct recipe *rec, char *desc);
void set_categories(struct recipe *rec, char *categories);
void set_profile(struct recipe *rec, char *profile);
void add_ingredient(struct recipe *rec, char *new_ingredient_name,
                    int percentage);
void delete_recipe(struct recipe *rec);
void print_recipe(struct recipe *rec);

#endif
