# Recipe Comparer

C project that takes in text files with recipe descriptions and outputs a graph with the results of comparison by euclidiean distance where each vector component is an ingredient in a recipe.

## Map implementation

This project uses a map implementation which can be found [here](https://github.com/rxi/map).

## Compilation

To compile and run this project on Windows, enter the following on the terminal **(this will change as the project is updated)**:

```
gcc main.c .\data-structures\recipe.c .\data-structures\map-master\src\map.c -o main.exe
main.exe
```

On Linux, you may run `make` or `make debug` and this will automatically compile the project according to instructions on [Makefile](Makefile).

## Visualization Tool
On this project the vizualization tool GraphViz was used to create an undirected and weighted graph to show the similarities of the recipes. 
In order for the visualization tool to work, GraphViz needs to be install. On Windows install the tool [here](https://graphviz.org/download/). On Linux run the following: 

```
sudo apt install graphviz
```
After running the main program, run the following command to generate the png file containing the graph:
```
dot -Tpng graph.gv -o graph.png
```