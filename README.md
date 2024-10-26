# Genetic Algorithm Robots Simulation

## Overview
The GARobot simulation is a C++ program that models a population of robots navigating a randomly generated map to harvest resources. Each robot has a set of genetic traits that influence its movement and decision-making process. The simulation iterates through multiple generations, where the best-performing robots contribute their genes to the next generation.

## Features
- Generates a 10x10 grid map with random obstacles.
- Creates an initial population of 200 robots with genetic traits.
- Robots move on the map, harvesting power and avoiding obstacles.
- Tracks and averages the performance of robots across multiple generations.
- Uses a genetic algorithm approach to evolve robot traits over generations.

## Classes
### `genMap`
- **Attributes**: 
  - `int map[10][10]`: A 2D array representing the map.
- **Methods**: 
  - `void newMap()`: Generates a new map with random obstacles.
  - `void mapPrint()`: Prints the current state of the map.
  - `int getValue(int i, int j)`: Retrieves the value at coordinates (i, j).
  - `int changeValue(int i, int j, int k)`: Changes the value at coordinates (i, j) to k.

### `genBot`
- **Attributes**: 
  - `int bots[200][16][5]`: A 3D array representing the genetic traits of 200 robots.
- **Methods**: 
  - `void setGenes()`: Initializes random genes for the robots.
  - `void genPrint()`: Prints the genes of all robots.
  - `void botPrint(int i)`: Prints the genes of a specific robot.
  - `int getValue(int i, int j, int k)`: Retrieves a specific gene value.
  - `int changeValue(int i, int j, int k, int n)`: Changes a specific gene value.

## Compilation
To compile the code, use a C++ compiler. For example, you can use `g++`:
```bash
g++ GARobot.cpp -o GARobot
