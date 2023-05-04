// Author: Aditya Parmar ||  Kanishk Jain
// File: main.cpp

// This file serves as the main program for solving the n-puzzle problem using the A* search algorithm with multi-threading.
// It imports the necessary libraries and header files such as "board.cpp", "queues.cpp", and "multithreading.cpp" 
// for defining the required classes and functions.

// Importing necessary libraries
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

#include "board.cpp"

State* start;
State* goal;
vector<State*> path;
int numThreads = 0;
int queuesPerThread = -1 ;

#include "queues.cpp"
#include "multithreading.cpp"

int main(int argc, char *argv[]) 
{
    int size = 4;
    int moves = -1;

    int choice;
    string inputFile;
    // Prompting the user for file input or not
    cout<<"Do you want to test from file ?\n1: Yes\n2: No\nYour Choice = ";
    cin>>choice;

    if (choice == 1)
    {
        // Taking the input file name as input
        cout<<"Enter the name of the file = ";
        cin>>inputFile;
    }
    else
    {
        inputFile = "";
    }
    // Taking number of queues per thread as input
    cout<<"Enter the number of queues you want per thread = ";
    cin>> queuesPerThread;
    
    if (argc > 1)                                       //Number of arguments must be greater than 1
        numThreads = atoi(argv[1]);

    if (argc <=1 )
        cout<<"Invalid number of threads"<<endl;

    cout << "Number of threads = " << numThreads << endl;
    cout << "Size = " << size << endl;
    cout << "Moves = " << moves << endl;


    if (inputFile.empty())                              //If choice 2 is selected
    {
        if (moves >= 0) 
        {
            start = (State*)(new Board(size, moves));
        } else 
        {
            start = (State*)(new Board(size));
        }
    } 
    else 
    {
        start = (State*)(new Board(inputFile));
    }
    
    cout << "Start board:" << endl;                     //Displaying the initial board
    cout << start->toString() << endl;


    if (numThreads != 0) 
    {
        cout << "Running parallel version with " << numThreads << " threads..." << endl;            //Displaying number of threads
    }

    if (queuesPerThread != -1) 
    {
        int totalQueues = queuesPerThread * numThreads;       //Storing the total number of queues         
        cout << "Using " << totalQueues << " number of queues..." << endl;
        cout<<"Each thread will have "<<queuesPerThread << " queues to work with ...."<<endl;
    }           

    goal = (State*)(new Board(size, 0));

	auto start = high_resolution_clock::now();                          //Calculating execution time

    if (numThreads == 0) 
    {
        cout<<"Invalid number of threads entered.\nThe program will now exit........"<<endl;
        exit(0);
    } 
    else 
    {
        parallel(numThreads);
    }

    
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Optimal solution found!" << endl << endl;
    
    int length = path.size();
    
    for (int i = 0; i < length; i++)                    //Dispalying steps
    {
        cout << "Step " << i+1 << ":" << endl;
        cout << path[i]->toString() << endl;
    }

    cout << "Length of path: " << length-1 << endl;     //Displaying total number of steps
    cout << "Total time: " << duration.count() << " ms" << endl;            //Displaying execution time

    return 0;
}
