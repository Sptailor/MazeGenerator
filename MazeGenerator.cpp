// Program to generate a random maze
// by Mary Elaine Califf and Suhail Tailor

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Maze.h"
using namespace std;

int main(int argc, char **argv)
{
    // manage command line inputs
    // arguments are numRows, numColumns, mazeFileName, randomSeed, stopEarly(optional)
    if (argc < 5)
    {
        cout << "Insufficient arguments. Correct usage:" << argv[0] << " numRows numColumns mazeFileName randomSeed (0 for unspecified) 1 to stop early {optional}" << endl;
        return 1;
    }
    int numRows, numColumns, randSeed;
    string mazeFileName;
    bool stopEarly = false;

    numRows = atoi(argv[1]);
    numColumns = atoi(argv[2]);
    mazeFileName = argv[3];
    randSeed = atoi(argv[4]);
    if (argc > 5)
    {
        stopEarly = (bool)atoi(argv[5]);
        if (stopEarly)
            cout << "stopping early" << endl;
    }

    //cout << "Arguments received: " << numRows << " " << numColumns << " " << mazeFileName << " "
    //    << randSeed << endl;

    if (randSeed)
    {
        srand(randSeed);
    }
    else
    {
        srand(time(nullptr));
    }

    Maze randMaze(numRows, numColumns);

    randMaze.generateMaze();

    // open the outputfile
    ofstream mazeOutStream(mazeFileName);
    randMaze.print(mazeOutStream);
    mazeOutStream.close();
}