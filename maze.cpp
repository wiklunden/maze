/*
	Projekt: Depth-First-Search Labyrint
	Namn: Milton Wiklund
	Datum: 2022-08-21
	Betyg siktat mot: C
*/

#include "maze.h"

// Default constructor for maze.
maze::maze(int width, int height) {
    this->width = width;
	this->height = height;
    visited_counter = 0;

    visited_nodes = new bool*[width];
    node_matrix = new node*[width];

    // Creates two-dimensional arrays.
    for (int x = 0; x < width; x++) {
        visited_nodes[x] = new bool[height];
        node_matrix[x] = new node[height];
    }

    // Sets a starting condition for every bool in this array.
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            visited_nodes[x][y] = false;
}

// Destructor for maze.
// Deallocates memory stored by the 2D-arrays of pointers.
maze::~maze() {
	// Deallocates each entry.
	for (int x = 0; x < width; x++) {
		delete[] node_matrix[x];
		delete[] visited_nodes[x];
	}
	
	// Dellocates the entire arrays.
	delete[] node_matrix;
	delete[] visited_nodes;

	// Assigns arrays to null (resetting their values).
	node_matrix = nullptr;
	visited_nodes = nullptr;
}

// Default constructor for nodes.
maze::node::node() {
    x = 0;
    y = 0;
    value = "  ";
}

// Stores every accessible border-node in a vector.
// Accessible nodes have an odd value and only exist next to accessible slots on the matrix.
// Purpose: giving appropriate coordinates for the randomized start- and end-node.
void maze::get_maze_border() {
    node top, bottom, left, right;

    // Horizontal parts of the matrix' border.
    for (int x = 1; x < (width - 1); x++) {
		// Only runs if the coordinates are odd.
        if (x % 2 != 0) {
            top.x = x;
            top.y = 0;

            bottom.x = x;
            bottom.y = (height - 1);

            border_nodes.push_back(top);
            border_nodes.push_back(bottom);
        }
    }

    // Vertical parts of the matrix' border.
    for (int y = 1; y < (height - 1); y++) {
        if (y % 2 != 0) { // Only runs if the values are odd.
            left.x = 0;
            left.y = y;

            right.x = (width - 1);
            right.y = y;

            border_nodes.push_back(left);
            border_nodes.push_back(right);
        }
    }
}

// Generates a maze with a set drawing speed.
void maze::generate(int& speed) {
    this->drawing_speed = speed;
    // Calls the Depth-First-Search algorithm.
    DFS();

	std::string choice;

	while (true) {
		std::cout << "Show path? (y/n): ";
		std::getline(std::cin, choice);
		if (choice == "y") {
			draw_DFS_path(DFS_path);
			break;
		}
		else if (choice == "n")
			break;
		else
			std::cerr << "\nNot a valid input.\n";
	}
}

/*
   Depth-First-Search algorithm.
   The algorithm stores a number based on how many directions there are to choose between.
   I.e, if the stored number is 3, there are three different directions to choose between (north, east & west).
   One of the directions are randomly chosen, set to visited and then pushed to a stack.
   If there is no number stored (empty vector), the algorithm will backtrack by popping from the stack.
   The algorithm continues looping until there are no more nodes to visit.
*/
void maze::DFS() {
    std::stack<node> stored_nodes;

    get_maze_border(); // Selects matrix' border (outside).
    randomize_start_node(); // Randomizes start node.
    randomize_end_node(); // Randomizes end node.

    system("clear");

    // Sets the root node to appear next to the start node.
    // Purpose: gives the, later on, drawn out path a beginning node.
    align(root, &start_node); // Aligns path-tail to the start node.
    visit(&root); // Sets path-tail to visited.
    stored_nodes.push(root); // Stores path-tail.

    node neighbour, middle, north, east, south, west;
    std::vector<int> available_neighbours;

    // While-loop that continues as long as there are nodes to pick.
    while (!stored_nodes.empty()) {
        neighbour = stored_nodes.top();

        // Picks a node 2 units north of the neighbour node,
        // if the node is within the border and is unvisited.
        north = push_north(neighbour, 2);
        if (north.y >= 1 && !is_visited(&north))
            available_neighbours.push_back(0);

        // Picks a node 2 units east of the neighbour node,
        // if the node is within the border and is unvisited.
        east = push_east(neighbour, 2);
        if (east.x < (width - 1) && !is_visited(&east))
            available_neighbours.push_back(1);

        // Picks a node 2 units south of the neighbour node,
        // if the node is within the border and is unvisited.
        south = push_south(neighbour, 2);
        if (south.y < (height - 1) && !is_visited(&south))
            available_neighbours.push_back(2);

        // Picks a node 2 units west of the neighbour node,
        // if the node is within the border and is unvisited.
        west = push_west(neighbour, 2);
        if (west.x >= 1 && !is_visited(&west))
            available_neighbours.push_back(3);

        // Checks to see if all nodes are visited or not.
        if (visited_counter < (width * height)) {
            if (!available_neighbours.empty()) {

                // Picks a random number from the vector of available neighbours.
                int random_neighbour = available_neighbours[rand() % available_neighbours.size()];

                switch (random_neighbour) {
                    case 0: // North direction.
                        visit(&north);
                        stored_nodes.push(north);
                        middle = push_south(north, 1); // Coordinates for node between north and south nodes.
                        break;
                    case 1: // East direction.
                        visit(&east);
                        stored_nodes.push(east);
                        middle = push_west(east, 1); // Coordinates for node between east and west nodes.
                        break;
                    case 2: // South direction.
                        visit(&south);
                        stored_nodes.push(south);
                        middle = push_north(south, 1); // Coordinates for node between south and north nodes.
                        break;
                    case 3: // West direction.
                        visit(&west);
                        stored_nodes.push(west);
                        middle = push_east(west, 1); // Coordinates for node between west and east nodes.
                        break;
                }

                visited_counter++; // Increases counter for visited nodes.
                visit(&middle); // Sets middle node to visited.

                // Plays an animated drawing of the maze if drawing speed is greater than 0.
                if (drawing_speed > 0) {
                    system("clear");
                    initiate_values(); // Initiates all values that have been set throughout the algorithm.
                    draw_maze();
                    usleep(this->drawing_speed);
                }

                // When the top node in the stack is overlapping with the node adjacent to the end node,
                // all existing nodes are copied to a new stack. This is the path from start to end.
                if (is_overlapping(&stored_nodes.top(), &last_path_node))
                    DFS_path = stored_nodes;
            }
            else stored_nodes.pop(); // Backtracks if there are no more neighbours to visit.

            // Empties vector with neighbours before looping.
            // This prevents vector from overflowing with previous neighbours.
            for (const auto& n : available_neighbours)
				available_neighbours.pop_back();
        }
    }

    // If the drawing speed is set to 0, or the maze dimensions are 3-by-3, the maze is drawn without animation.
    if (drawing_speed == 0 || (height * width) == 9) {
        initiate_values();
        draw_maze();
    }

    std::cout << "\n Depth-First-Search generation complete!\n";
    print_maze_resolution();
}