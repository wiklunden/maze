/*
	Projekt: Depth-First-Search Labyrint
	Namn: Milton Wiklund
	Datum: 2022-08-21
	Betyg siktat mot: C
*/

#include "setters.h"

// Randomizes where the start node appears on the border.
void maze::randomize_start_node() {
	// Picks a random node from the vector with border nodes.
    node random_node = border_nodes[rand() % border_nodes.size()];

    start_node.x = random_node.x;
    start_node.y = random_node.y;

    visit(&start_node); // Sets start node to visited.
}

// Randomizes where the end node appears on the border.
void maze::randomize_end_node() {
    node random_node = border_nodes[rand() % border_nodes.size()];

    // If start node and end node are identical, pick another random position.
    while (is_overlapping(&random_node, &start_node)) {
        random_node = border_nodes[rand() % border_nodes.size()];

        if (!is_overlapping(&random_node, &start_node)) break;
    }

    end_node.x = random_node.x;
    end_node.y = random_node.y;

    align(last_path_node, &end_node); // Aligns head (top) of path to the end node of the maze.
    visit(&end_node); // Sets end node to visited.
}

// Assigns value to a specific node.
void maze::set_node_value(node* node, std::string value) {
    node_matrix[node->x][node->y].value = value;
}

// Checks every node on the matrix and initiates their values.
void maze::initiate_values() {
    node node;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            node.x = x;
            node.y = y;

            if (visited_nodes[x][y]) set_node_value(&node, "  ");
            else set_node_value(&node, "██");

            if (start_node.x == node.x && start_node.y == node.y) {
                set_node_value(&start_node, "S ");
            }
            else if (end_node.x == node.x && end_node.y == node.y) {
                set_node_value(&end_node, "E ");
            }
        }
    }
}

// Sets width of maze.
int set_width() {
	unsigned int width;
	std::string input;
	bool contains_letters;
    const int MAX_SIZE = 299, MIN_SIZE = 3;

    while (true) {
		// While-loop treating errors caused by letter input.
		while (true) {
			std::cout << "Set width (0=default): ";
			getline(std::cin, input);
			
			contains_letters = check_for_letters(input);

			if (contains_letters)
				std::cout << "\nMust be a numerical value.\n";
			else {
				width = stoi(input);
				break;
			}
		}

		// Sets default value for maze.
        if (width == 0) {
			width = 11;
			break;
		}

        // Statements for error handling.
		if (width > MAX_SIZE)
            std::cerr << "\nWidth cannot be greater than " << MAX_SIZE << ".\n\n";
		else if (width < MIN_SIZE)
			std::cerr << "\nWidth cannot be less than " << MIN_SIZE << ".\n\n";
        else if (width % 2 == 0)
            std::cerr << "\nWidth must be an odd number.\n\n";
        else break;
    }

	return width;
}

// Sets height of maze.
int set_height() {
	unsigned int height;
	std::string input;
	bool contains_letters;
	const int MAX_SIZE = 299, MIN_SIZE = 3;

    while (true) {
		// While-loop treating errors caused by letter input.
		while (true) {
			std::cout << "Set height (0=default): ";
			getline(std::cin, input);

			contains_letters = check_for_letters(input);

			if (contains_letters)
				std::cout << "\nMust be a numerical value.\n";
			else {
				height = stoi(input);
				break;
			}
		}

		// Sets default value for maze.
		if (height == 0) {
			height = 11;
			break;
		}

        // Statements for error handling.
        if (height > MAX_SIZE)
            std::cerr << "\nHeight cannot be greater than " << MAX_SIZE << ".\n\n";
		else if (height < MIN_SIZE)
			std::cerr << "\nHeight cannot be less than " << MIN_SIZE << ".\n\n";
        else if (height % 2 == 0)
            std::cerr << "\nHeight must be an odd number.\n\n";
        else break;
    }

	return height;
}

// Sets drawing speed for maze.
int set_drawing_speed() {
	unsigned int speed;
	std::string input;
	bool contains_letters;
	
	// While-loop treating errors caused by letter input.
    while (true) {
        std::cout << "Set drawing speed (ms): ";
        getline(std::cin, input);

		contains_letters = check_for_letters(input);

		if (contains_letters)
			std::cerr << "\nMust be a numerical value.\n";
		else {
			speed = stoi(input);
			break;
		}
    }

	return speed;
}