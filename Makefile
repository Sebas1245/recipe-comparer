CFLAGS = -O
CC = gcc
SRC =  ./data-structures/map-master/src/map.c ./data-structures/recipe.c ./data-structures/edge.c main.c
OBJ = $(SRC:.c = .o)

RecipeComparer: $(OBJ)
	$(CC) $(CFLAGS) -o RecipeComparer.o $(OBJ) -lm

debug: $(OBJ)
	$(CC) $(CFLAGS) -o RecipeComparer.o $(OBJ) -lm -DDEBUG

clean:
	rm -f core *.o
