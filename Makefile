CFLAGS = -O
CC = gcc
SRC =  ./data-structures/map-master/src/map.c ./data-structures/recipe.c main.c
OBJ = $(SRC:.cpp = .o)

RecipeComparer: $(OBJ)
	$(CC) $(CFLAGS) -o RecipeComparer $(OBJ)

clean:
	rm -f core *.o
