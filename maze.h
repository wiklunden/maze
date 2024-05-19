/*
	Projekt: Depth-First-Search Labyrint
	Namn: Milton Wiklund
	Datum: 2022-08-21
	Betyg siktat mot: C
*/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <cmath>

#include "functions.h"
#include "draw.h"
#include "setters.h"

// Color definitions for printouts.
#define RST "\x1B[0m"
#define KBLU "\x1B[36m"
#define KRED "\x1B[31m"
#define BLUE(x) KBLU x RST
#define RED(x) KRED x RST

class maze {
private:
    struct node {
        node();
        int x, y;
		std::string value;
    };
    node start_node, end_node, root, last_path_node;
    
    node push_north(node, int);
    node push_east(node, int);
    node push_south(node, int);
    node push_west(node, int);

    int width, height, visited_counter, drawing_speed;

    bool** visited_nodes;
    node** node_matrix;

    std::stack<node> DFS_path;
    std::vector<node> border_nodes;

    void get_maze_border();
    bool is_visited(node*);

    bool visit(node*) const;
    void set_node_value(node*, std::string);
    void initiate_values();

    void randomize_start_node();
    void randomize_end_node();

public:
    maze(int, int);
    ~maze();
    void generate(int&);
    void DFS();

    void align(node&, node*);
    bool is_overlapping(node*, node*);
    void print_coordinates(node*) const;

    inline int size() { return width * height; } // Returns size of maze.
    void print_maze_resolution();

    void draw_maze();
    void draw_DFS_path(std::stack<node>&);

    void DEBUGGER(std::string);
};

#endif