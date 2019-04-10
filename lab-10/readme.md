# Lab 10: Mancala Solitaire with Linked Lists

## 1. Introduction

Today you will implement a class called `MancalaSolver`, which uses a circular singly-linked list to play a game called Mancala Solitaire, given some input. 
The goal of this lab is to give you a deeper understanding of the linked list data structure that you learned about in lecture.

**This lab comes with starter code**, provided in the files `lab-10.cpp`, `mancala.hpp` and `mancala.cpp`.

## 2. Visualizing Linked Lists

Here are a few images and explanations to help with your visual understanding of linked lists before you start working on the lab.

![image](http://www.java2novice.com/images/linked_list.png)

> Fig 2.1. An example of a singly linked list. 
Each node (pair of grey boxes) contains data, in this case integers, and a pointer to the next node. 
There is also a `head` pointer, which should always point to the first node in the linked list as long as operations are not currently being performed on it (i.e., "the `head` pointer points to the first node" is an *invariant* of a singly linked list).

![image](http://www.java2novice.com/images/sll_insert_after.png)

> Fig 2.2. A pictorial representation of the insertion of a new node into a singly linked list. 
Here `newNode` is added after `node`, so `newNode` is set to point to `node.next` and `node` is set to point to `newNode`. 
Note that if `newNode` were to be added to the beginning or end of the linked list, the insertion process would be different.

![image](http://www.java2novice.com/images/sll_delete_after.png)

> Fig 2.3. A pictorial representation of the deletion of a node from a singly linked list. 
Notice how `node`'s pointer just skips over the removed node, now pointing to what was originally `node.next.next`. 
If the node being removed was at the beginning or end of the linked list, the deletion process would also be different.

***IMPORTANT NOTE**: The tail node of a **circular** singly-linked list points to the head node instead of NULL.*  

## 3. Mancala Solitaire

The game your algorithm will play/solve is based on a two-player game called [Mancala](https://en.wikipedia.org/wiki/Mancala), in which players take turns moving glass pieces among pits in a wooden board. 
Mancala Solitaire is a one-player game using the same mechanic.
 
#### 3.1 Rules

You are given a board with N pits indexed 0 to N-1, each containing some number of pieces, and a starting index `idx`. 
You play the game by carrying out the following steps:

1. Take all the pieces out of the pit with index `idx`. This pit is now considered dead and will not receive pieces anymore.
2. Place one piece in each pit after the pit at `idx` (wrapping from pit N-1 to pit 0)
3. Whichever pit receives the last piece is the new starting pit (its index is the new `idx`)
4. Repeat steps 1 through 3 until only one pit remains. This pit is the winning pit.

#### 3.2 Example

It's one thing to read some rules about a game, but it's often much more useful to see it being played, so here is an example of a small game of Mancala Solitaire being played out in full.

![Mancala Solitaire 1](./mancala1.png "Mancala Solitaire 1")

> Fig 3.1. The starting state of a game of Mancala Solitaire with `N = 4` pits. 
Each large circle is a pit, the number inside is the number of pieces in the pit, the small numbers in the corners are the indices of each pit, and the arrows show the direction in which pieces will move. 
Since the starting index `i` is 1, the game will start at the pit with index 1, which has its number of pieces highlighted in red.

![Mancala Solitaire 2](./mancala2.png "Mancala Solitaire 2")

> Fig 3.2. The 3 pieces from pit 1 are distributed one-by-one following the arrows, and pit 1 is considered dead (hence the red X). 
The pit where the last piece was dropped is the next pit to be used, which in this case is pit 0.

![Mancala Solitaire 3](./mancala3.png "Mancala Solitaire 3")

> Fig 3.3. The pieces from pit 0 are distributed in the same manner as those of pit 1 in the previous illustration. 
Since the fourth piece lands in pit 3, that is the next pit to be used. 
While at this point we already know the winner, for boards of any size N this process would continue until...

![Mancala Solitaire 4](./mancala4.png "Mancala Solitaire 4")

> Fig 3.4. Every pit is dead except for one, which now contains all the pieces. 
All of pit 3's pieces were put into pit 2 and it was removed from play, leaving pit 2 as the last pit standing, and thus the winning pit has been found!

*Although Mancala Solitaire is based on the game Mancala, it would probably be better described as a simulation as opposed to a game, since there is no real winning or losing.*

## 4. Starter Code & Objective

#### 4.1 Starter Code

The starter code for this lab is contained within the `mancala.hpp`, `mancala.cpp` and `lab-10.cpp` files. 
You are given the entire class definition for `MancalaSolver`, which internally uses a circular singly-linked list to solve Mancala Solitaire, along with the entire implementation of the `Pit` class, which corresponds to the nodes in the linked list. 
You are also given implementations of `MancalaSolver`'s constructor, destructor, and print function. 

Here is a brief overview of the code:

```c++
#ifndef __MANCALA_SOLVER_H__
#define __MANCALA_SOLVER_H__
...
// All the class definitions and other stuff
...
#endif
```

This preprocessor directive appears in nearly all header files, both in C++ and in C. 
It instructs the preprocessor to check if it has seen the name `__MANCALA_SOLVER_H__` before, if it has *not* it "declares" this name and includes everything in the header. 
This essentially prevents a header from being included in more than once, which can happen in more complex programs. 
You do not need to worry about this much, but it's good to know what it is and get into the habit of putting similar lines in your own header files.

```c++
#ifndef NULL
#define NULL 0x00
#endif
```

This just lets you use `NULL` to represent the number 0, which is also the memory address of the null pointer.

> Side note: Whenever you see a line starting in the `#` symbol in C/C++, you're seeing what's called a *preprocessor directive*. 
Basically, the C++ compiler runs a routine on the source code, called the preprocessor, which does something specific to the code each time it finds a line starting with a `#` symbol, such as pulling in code in the case of `#include`, or replacing every instance of `A` with `B` in the case of `#define A B`.

```c++
class Pit {

private:
    Pit* next;
    int index;
    int num_pieces;

public:
    Pit(int idx, int pieces);
    ~Pit();

    friend class MancalaSolver;

};
```

The definition of the `Pit` class is fairly regular on most accounts, consisting of just three fairly self-explanatory private data members, a constructor, a destructor and...a friend? 
Sort of. The line `friend class MancalaSolver;` actually gives the class `MancalaSolver` permission to directly access the private data members of an instance of the `Pit` class, which will be important in your implementation of `MancalaSolver`. 
The word "friend" is likely used because it is almost like the `Pit` class is sharing its data with `MancalaSolver`, just as someone may share some of their belongings with one of their friends.

```c++
class MancalaSolver {

private:
    Pit* head;
    Pit* curr;
    unsigned int n_elem;

public:
    MancalaSolver();
    ~MancalaSolver();

    int removeByIndex(unsigned int idx);

    void append(int idx, int num_pieces);

    int solve(int idx);

    unsigned int getSize();
    void print();
};
```

There also isn't much to say about the definition of the `MancalaSolver` class. 
Its private data members are `head`, which points to the start of the circular linked list, `n_elem` the number of pits *remaining in the game*, and `curr`. 
The pointer `curr` has no explicit purpose, but during your implementation you may find it useful to store a "place where you left off" so-to-speak, which will be accessible after a function call has completed.

As for the methods, the constructor, the destructor and `print()` have all been implemented already. 
The constructor initializes `head`, `curr` and `n_elem` to `NULL`, `NULL` and 0 respectively, the destructor deletes any nodes remaining in the linked list and `print()` prints information about all the nodes in the linked list, which you may want to see at some point. 
The remaining methods are for you to implement, and are described within `mancala.cpp`.

Finally, you will notice that `lab-10.cpp` is a blank template, consisting of nothing but includes for your header and `iostream`, along with an empty `main()`. 
Based on the instructions given in the next subsection, you will need to write everything for `main()` yourself.

#### 4.2 Input/Output

Your program will take a path to a file `filename` containing `N` lines, where each line has a single number representing the number of pieces in the corresponding pit (i.e. if the lines numbers are counting from 1, then the `i`th line has the number of pieces in the `i-1`th pit), the number of pits `N` and the starting index `idx`. 
It should then output the index of the winning pit. 
Thus, if your compiled program is named `lab-10`, your function will receive input as follows:

```bash
./lab-10 filename N idx
```

For example, given the file `in.txt` with the contents:

```
3
3
4
3
```

Examples of correct input and output are as follows:

```bash
./lab-10 in.txt 4 1
2
./lab-10 in.txt 4 3
1
```

#### 4.3 Objective

Your objective for this lab will be to do the following (preferably in order):

1. Implement `MancalaSolver`'s `append()` function.
2. Create an instance of `MancalaSolver` and write the code to read the data from the input file.
3. Implement `removeAtIndex` and `solve`.
4. Call `solve` and output the index of the winning pit.
5. Each node has its own index during its entire life. In other words, if a node is deleted from the circularly linked list, it should not affect the indices of any of the other nodes.

> Make sure you test each method **AS YOU GO**.

#### 4.4 Extra Details/Hints

Here are some details that will help you in your implementation:

+ You will only need to call `solve()` once, and it should be called from within `main()`
+ You will need to call `removeAtIndex()` within `solve()`
+ `removeAtIndex()` should both move the pieces and remove the pit at the given index from play.
+ You will need to use additional `#include`s in `lab-10.cpp`, particularly for reading from a file.
+ When implementing/debugging methods that involve changing pointers, it may help to draw out what you are trying to do and/or what your code is currently doing using circles and arrows.

#### 4.5 Questions

> Question 1: What is the key advantage of using linked lists for functions such as `append` and `removeByIndex` over traditional arrays?

> Question 2: What is the Big O runtime of `append`? What is the Big O runtime of `removeByIndex`?

## 5. Submission

Your **Gradescope** submission for this lab will include your `lab-10.cpp` and `mancala.cpp` files containing your class and function implementations, as well as a `lab-10.txt` file containing your answers to the above questions.

* If you did not finish the lab within the period you should submit the `mancala.cpp` and `lab-10.cpp` files containing everything you were able to implement. 
* If you did not answer the questions for this week, submit a blank `lab-10.txt` file.
