// Class to generate a random maze using disjoint sets and print it in ASCII format to a file
// By Mary Elaine Califf and Suhail Tailor
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include "DisjointSet.h"

using namespace std;

struct CellWalls
{
    bool south;
    bool east;
    CellWalls(bool startEast = true, bool startSouth = true) : east(startEast), south(startSouth) {}
};

class Maze
{
private:
    CellWalls *mazeWalls; // maze cells
    int numRows;
    int numColumns;

public:
    // constructor
    Maze(int rows, int cols);

    // copy constructor
    Maze(const Maze &orig) { copy(orig); };

    // destructor
    ~Maze() { delete[] mazeWalls; }

    // assignment operator
    Maze &operator=(const Maze &rhs);

    // generates the maze by randomly knocking down walls
    void generateMaze();

    // prints the maze to the specified outputStream
    void print(ostream &outputStream);

private:
    // private helper method to copy the data from another Maze object
    void copy(const Maze &orig);

    // finds next cell
    int move(int randomCell, int validDirection, int numColumns);

    // ensures move can be made without going out of maze boundary and return a valid direction
    int validateDirection(int numColumns, int numRows, int randomCell, int randomDirection, int numCells);

    // breaks down the wall in the valid direction
    void breakWall(int randomCell, int nextCell, int validDirection, CellWalls *&mazeWalls, DisjointSet &mySet, bool &mazeComplete);

    // checks if sets match
    bool checkSets(int randomCell, int nextCell, DisjointSet mySet);
};

#endif
