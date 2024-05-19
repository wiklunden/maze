/*
	Projekt: Depth-First-Search Labyrint
	Namn: Milton Wiklund
	Datum: 2022-08-21
	Betyg siktat mot: C
*/

#include "functions.h"

// Aligns a specified node to a node on the border.
// Purpose: aligning nodes to the starting and ending nodes.
void maze::align(node& align_node, node* border_node) {
    // If-statements to make sure aligned nodes are within the specified borders.
    if (border_node->y == 0) align_node.y = 1;
    else if (border_node->y == (height - 1)) align_node.y = (height - 2);
    else align_node.y = border_node->y;

    if (border_node->x == 0) align_node.x = 1;
    else if (border_node->x == (width - 1)) align_node.x = (width - 2);
    else align_node.x = border_node->x;
}

// Checks if one node is overlapping with another (identical positions).
bool maze::is_overlapping(node* n1, node* n2) {
    if (n1->x == n2->x && n1->y == n2->y) return true;
    return false;
}

// Prints out coordinates of a node.
void maze::print_coordinates(node* node) const {
    std::cout << node->x << ", " << node->y << "\n";
}

// Checks if a node is set as visited or not.
bool maze::is_visited(node* node) {
    if (visited_nodes[node->x][node->y]) return true;
    return false;
}

// Sets a node as visited.
bool maze::visit(node* node) const {
    visited_nodes[node->x][node->y] = true;
    return visited_nodes[node->x][node->y];
}

// Prints size of maze.
void maze::print_maze_resolution() {
    std::cout << " Maze size: " << width << " x " << height << " ";
    std::cout << "(" << width * height << " points)\n\n";
}

// Returns a node 'n' units north/east/south/west of a specified node.

maze::node maze::push_north(node node, int n) {
    node.x += 0;
    node.y -= n;

    return node;
}

maze::node maze::push_east(node node, int n) {
    node.x += n;
    node.y += 0;

    return node;
}

maze::node maze::push_south(node node, int n) {
    node.x += 0;
    node.y += n;

    return node;
}

maze::node maze::push_west(node node, int n) {
    node.x -= n;
    node.y += 0;

    return node;
}

// Returns true if input contains letters,
// returns false if not.
bool check_for_letters(std::string& input) {
	for (int i = 0; i < input.length(); i++)
		if (isalpha(input[i]))
			return true;
	
	return false;
}