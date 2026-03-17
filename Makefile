all: sum-nbo

sum-nbo: sum-nbo.cpp
	g++ -o sum-nbo sum-nbo.cpp
