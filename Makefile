main: main.cpp maze.cpp maze.h functions.cpp functions.h draw.cpp draw.h setters.cpp setters.h
	g++ -o main main.cpp maze.cpp functions.cpp draw.cpp setters.cpp

run: main
	./main

clean: main
	rm main