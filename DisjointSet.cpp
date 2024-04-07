// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Suhail Tailor

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    // to do
    theArray.resize(numObjects);//assign correct size
    this->numValues = numObjects;//assign num of values

    fill(theArray.begin(), theArray.end(), -1);//make sure each starts as -1
}

// recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    // to do -- see assignment instructions for details

    if (theArray[objectIndex] < 0)//base case 
    {
        return objectIndex;
    }
    return theArray[objectIndex] = find(theArray[objectIndex]);//recursion with path compression
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{
    // to do -- see assignment instructions for details
    int root1 = find(objIndex1);//locate roots
    int root2 = find(objIndex2);

    if (theArray[root1] <= theArray[root2])//compare roots
    {
        theArray[root1] += (theArray[root2]);//adds up smaller to larger 
        theArray[root2] = root1;//update value
    }
    else
    {
        theArray[root2] += (theArray[root1]);//adds up smaller to larger
        theArray[root1] = root2;//update value
    }
    if (abs(theArray[root1]) == numValues || abs(theArray[root2]) == numValues)//check if all belong to one set
    {
        return true;
    }
    else//if they are in different sets
    {
        return false;
    }
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
