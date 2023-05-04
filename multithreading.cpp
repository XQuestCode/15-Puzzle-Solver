//  Aditya Parmar ||  Kanishk Jain
//  multithreading.cpp
// This code implements a parallel version of the A* algorithm for finding the shortest path between two points on a graph. 
// The algorithm uses multiple threads to explore the search space in parallel.

threadsQueue<State*, stateHash, stateEqual> visited;

int lock = 0;
int totalQueues;

/*
The handle_tick function checks if the goal state has been visited. 
If it has, it checks if the current minimum key value is less than or equal to the goal state's key value. 
If not, it returns false, indicating that the search should continue.
*/
bool handle_tick()
{                                
    State* element;
    if ((element = visited.find(goal)) == NULL) 
    {
        return false;
    }

    int fval = element->getF();

    for (int i = 0; i < totalQueues; i++) 
    {
        if (visited.getMinKey(i) < fval) 
        {
            return false;
        }
    }
    return true;
}

/*
The parallelThread function is the main thread function that is executed by each thread. 
It runs an infinite loop, in which it pops a state from the priority queue and generates its neighboring states. 
It then adds the neighboring states to the priority queue if they have not been visited before.
*/
void* parallelThread(void* arg)                     
{
    int thread_id = (int)(long long)(arg);
    int visit = 0;

    int x = 1;
    while (1) 
    {    
        if (thread_id == 0 and visit%10000 == 0) 
        {
            if (visit % 100000 == 0) 
            {
                cout<<"Finding optimal solution..."<< x <<endl;
                x++;
            }

            if (handle_tick()) 
            {
                lock = 1;
                return NULL;
            }
        }

        visit++;

        State* current = NULL;
        while (current == NULL) 
        {
            if (lock == 1) 
            {
                return NULL;
            }

            if (queuesPerThread <= 1) 
            {
                cout<<"The value must be greater than 1..\nProgram will now exit"<<endl;
                exit(0); 
            }
            else 
            {
                current = visited.pop(rand()%totalQueues);
            }
        }
        
        current->removeVisited();
        
        vector<State*> neighbors = current->getNeighbors();     //Storing neighbors in vectors
        
        for (int i = 0; i < neighbors.size(); i++) 
        {
            State* neighbor = neighbors[i];
            visited.push(neighbor, current);
        }
    }

    return NULL;
}
/*
The createPath function creates the final path by tracing back from the goal state to the start state, 
using the prev pointers that are stored in each state.
*/
void createPath()                       
{
    vector<State*> tempPath;

    State* current = visited.find(goal);

    while (current != NULL && current != start) 
    {
        tempPath.push_back(current);
        current = current->getPrev();
    }
            
    tempPath.push_back(start);
            
    int pathLength = tempPath.size();

    for (int i = 0; i < pathLength; i++) 
    {
        path.push_back(tempPath[pathLength-1-i]);
    }

    return;
}

/*The parallel function is the main function that initializes the search. 
It creates the threads, initializes the priority queue with the start state, and then starts the search by calling the parallelThread function in each thread. 
Finally, it creates the final path by calling the createPath function.*/
void parallel(int numThreads)                       //Runs everything. Called by main
{
    if (queuesPerThread <= 1) 
    {
        cout<<"The value must be greater than 1..\nProgram will now exit"<<endl;
        exit(0); 
    }
    else 
    {
        totalQueues = queuesPerThread*numThreads;
    }

    srand(time(NULL));

    visited.init(totalQueues);                      //Initializing total queues

    pthread_t threads[numThreads];                  //Initializing threads

    visited.push(start, NULL);
    
    for (int i = 0; i < numThreads; i++)            //Creating threads as provided by user
    {
        pthread_create(&threads[i], NULL, &parallelThread, (void*)(long long)i);
    }

    for (int i = 0; i < numThreads; i++)            //Joining thread
    {
        pthread_join(threads[i], NULL);
    }

    createPath();                                   //Creating path
}
