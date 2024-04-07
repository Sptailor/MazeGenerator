// Implementation of Maze class
// By Mary Elaine Califf and Suhail Tailor

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete[] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    int randomCell, randomDirection;
  
    while (!mazeComplete)//while maze is not complete
    {
        randomCell = rand() % numCells;//pick random cell
        randomDirection = rand() % 4;//pick random direction
        int validDirection = validateDirection(numColumns, numRows, randomCell, randomDirection, numCells);//checks if direction is valid
        int nextCell = move(randomCell, validDirection, numColumns);//locates the cell to join to

        breakWall(randomCell, nextCell, validDirection, mazeWalls, mySet, mazeComplete);//breaks wall between random cell and next if they belong to different sets
    }

    // to do -- see assignment instructions for details
}
int Maze::move(int randomCell, int validDirection, int numColumns)//locate the next cell 
{
    int cellOut;
    if (validDirection == 0)
    {
        cellOut = randomCell - 1;// return left cell 
    }
    else if (validDirection == 1)
    {
        cellOut = randomCell + numColumns;// return bottom cell 
    }
    else if (validDirection == 2)
    {
        cellOut = randomCell + 1;// return right cell 
    }
    else if (validDirection == 3)
    {
        cellOut = randomCell - numColumns;// return top cell 
    }
    return cellOut;
}
int Maze::validateDirection(int numColumns, int numRows, int randomCell, int randomDirection, int numCells)//ensure direction is valid
{
    if (randomDirection == 0)//check left
    {
        if ((randomCell % numColumns) - 1 < 0)//flip if invalid
        {
           
            randomDirection = 2;
        }
    }
    else if (randomDirection == 2)//check right
    {
        if ((randomCell % numColumns) + 1 > numColumns-1)//flip if invalid
        {
           
            randomDirection = 0;
        }
    }
    else if (randomDirection == 1)//check bottom
    {
        if ((randomCell + numColumns) > (numCells - 1))//flip if invalid
        {
            randomDirection = 3;
        }
    }
    else if (randomDirection == 3)//check top
    {
        if ((randomCell - numColumns) < 0)//flip if invalid
        {
            randomDirection = 1;
        }
    }
    return randomDirection;
}
bool Maze::checkSets(int randomCell, int nextCell, DisjointSet mySet)//check which set each cell belongs to
{
    bool out = false;
    if (mySet.find(randomCell) == mySet.find(nextCell))//if they are the same set
    {
        out = true;
    }
    return out;
}
void Maze::breakWall(int randomCell, int nextCell, int validDirection, CellWalls *&mazeWalls, DisjointSet &mySet, bool &mazeComplete)
{
    if (!checkSets(randomCell, nextCell, mySet))//ensure wall needs to be broken
    {
        
        mazeComplete = mySet.doUnion(randomCell, nextCell);//updates bool after calling union to check if maze has been completed
       //checks all four directions and breaks the respective wall related to direction
        if (validDirection == 3)
        {
            mazeWalls[nextCell].south = false;//break top wall
        }
        else if (validDirection == 2)
        {
            mazeWalls[randomCell].east = false;//break right wall
        }
        else if (validDirection == 1)
        {
            mazeWalls[randomCell].south = false;//break bottom wall
        }
        else if (validDirection == 0)
        {
            mazeWalls[nextCell].east = false;//break left wall
        }
    }
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}
