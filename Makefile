main : main.cpp
	g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -O3 -march=native main.cpp -o main

plot : 
	gnuplot -p -e 'plot "SimulatedStockSnapshot.txt" with linespoints'
