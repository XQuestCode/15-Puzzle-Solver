
# 15 Puzzle Solver

The challenge of solving this puzzle lies in finding the most efficient sequence of moves to reach the goal state, as there are numerous possible permutations of the tiles that can result in an unsolvable puzzle. Not only this, if tried to solve using the Sequential Approach, the only outcome the user gets is Memory Overflow. This is because, with each further step, a number of new permutations are generated and these permutations are then needed to be calculated further.

For the implementation of this problem, we used 3 different data structures: queues, vectors, and priority queues. We used the A* algorithm and implemented it using 3 different classes and 1 main class, making a total of 4 classes. We start by creating a randomized 4x4 board using permutation, or by providing an unsolved puzzle. After the implementation of the board, we used a hash function in the A* algorithm to randomly create board combinations and check their cost. We select the lowest-cost board and store it in the hash function to avoid revisiting combinations. We also implemented a priority queue and a queue of priority-queues. We added multithreading by passing the number of threads as an argument and initializing that many threads to perform the desired task.




## Developers

- [@kanishkjain0263](https://github.com/kanishkjain0263)

- [XQuestCode](https://github.com/XQuestCode)


## Deployment

To deploy this project run

If make is configured, use this:
```bash
  g++ main.cpp -pthread -o main
```
```bash
  ./main n
```

Else, use this:
```bash
  make
```
```bash
  ./main n
```
n - the number of threads

## Screenshots
Random Puzzle is initialized
![App Screenshot](https://i.postimg.cc/GhNDmbWH/Whats-App-Image-2023-05-04-at-22-09-50.jpg)


![App Screenshot](https://i.postimg.cc/BQtD3jwr/Whats-App-Image-2023-05-04-at-22-10-04.jpg)

![App Screenshot](https://i.postimg.cc/3rtpzX9j/Whats-App-Image-2023-05-04-at-22-10-16.jpg)


![App Screenshot](https://i.postimg.cc/Hnvy5mjv/Whats-App-Image-2023-05-04-at-22-10-33.jpg)
Number of Steps and Time taken to solve the puzzle is printed at the end of the output