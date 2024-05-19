/*
	Projekt: Depth-First-Search Labyrint
	Namn: Milton Wiklund
	Datum: 2022-08-21
	Betyg siktat mot: C
*/

#include <iostream>
#include "maze.h"
#include "functions.h"
#include "setters.h"

// Main function that creates a new maze.
int main() {
	srand(time(nullptr));
	int width, height, speed;
	std::string choice;

    while (true) {
		system("clear");

		width = set_width();
		height = set_height();
        speed = set_drawing_speed();

        // Asks the user if it wants to regenerate maze with the same settings.
        while (true) {
            system("clear");
            maze my_maze(width, height);
            my_maze.generate(speed);

            std::cout << "Regenerate? (y/n): ";
			std::getline(std::cin, choice);

            if (choice == "y") continue;
			else break;
        }

        // Asks the user if it wants to start from the beginning.
        std::cout << "Reset? (y/n): ";
		std::getline(std::cin, choice);

        if (choice == "y") continue;
		else break;
    }

    return 0;
}
