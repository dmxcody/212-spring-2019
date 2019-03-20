# Lab 01: Creating a `string` class

## 1. Introduction

The major focus of today's lab will be to learn how to write and use classes in C++, while gaining experience with pointers and dynamic memory.
To accomplish this, you will be creating a `MyString` class that behaves like, and has some of the functions associated with `std::string`. 

## 2. Background

By now you should be well aware of the existence of classes (you've probably even used them before), but you may not be completely comfortable with them. 
In this section we hope to bridge that gap, making you more comfortable both with using classes and writing them yourself. 
We will also review dynamic memory allocation, as it's an important C++ concept to be familiar with.

### 2.1 Classes

#### 2.1.1 What is a Class?

To understand what a class is, perhaps we can start with a technical definition, a very non-technical definition, and then meet somewhere in the middle.

*Technical definition:*

A class is a programming language construct used to encapsulate both data and functionality, and is designed to represent a single, well-defined concept. An object is an instantiation of a class.

*Very non-technical definition:*

A class is blueprint for a thing that has certain qualities and can do certain things. 
An object is one of the things that comes from a blueprint.
Much like a human is an abstract blueprint, you yourself are a specific instantiation of a human. 

While the first definition is much more specific and correct, the second may be more intuitive for some. 
The general idea is that a class is used to represent some concept, or "thing", which may be real or abstract. 
A class will have certain *properties* or *data members*, which can be thought of as being a part of, belonging to, or describing that "thing", as well as *methods*, which can be thought of as the the functionality of that "thing", i.e. what it can do.

Finally, an *object* or *instance* of a class is one specific member of that class. 
So the class just describes what the "thing" is and what it can do, whereas an object actually *is* a "thing". 
This will likely make more sense with an example.

So suppose you have a program with a `mammal` class. 
The purpose of this class will then be to describe what a mammal is and what it does. 
Perhaps a given mammal is described by how many legs it has, what kind of food it eats, how hungry it is, and how much it weighs. 
Then those would be some of its properties. 
To decide what methods a mammal may have, you can think about what a mammal (generally) does, such as walking and eating a meal. 
Now of course, it's great to know what a mammal is, and what it does, but now we actually want to have a mammal in our program, which is where objects come in. 
You can use your `mammal` class to create an object called `dog`, and specify that it has four legs, eats dog food, is not hungry at all, and weighs 60 lbs.

Hopefully if you didn't have a good conceptual understanding of classes before, you do now. 
The next step will be to make these concepts concrete in terms of code.

#### 2.1.2 Headers and Source Files

Just to get a bit of technical information out of the way, if you have ever worked with classes before, or even looked into any C++ repository, you will likely have seen `.h` or `.hpp` files.
These are called *header files*, the presence of which often signifies that classes are being used. 
This is because header files tend to contain declarations for an associated *source file*, a `.cc` or `.cpp` file, which contains method implementations. 
Thus, if you look into this lab's starter code, you'll see a `mystring.hpp` and a `mystring.cpp`, which will respectively contain the declarations and implementations for today's class.

#### 2.1.3 Defining a Class

As stated in the previous section, a class is almost always defined separately from being implemented. 
This is so that we can tell at a glance what a class is and what it is supposed to do, without having to worry about all the details of how it does the things that it does (how its methods are implemented). 
Part of the definition for the `MyString` class from the starter code is as follows:

```c++
    ```c++
    class MyString {
        private:
	    // declare all your data members here
	    
        public:
            // constructors and destructor
            MyString();
            MyString(const char *);
            ~MyString();

            // other functions
            unsigned int len();

            void set(int, char);
            char get(int);
            void del(int);
            const char *substr(int, int);
	    ...
    }
```

This class definition has a few features that are shared between nearly all classes:

The most noticeable part of this class definition is all the functions. 
This is where all the talk of "data members" and "methods" come into play. 
When working with classes, a class' variables and constants are called its *data members* and its inherent functions are called its *methods*. 
Also, since this is just a class definition, all of the methods will *only be declared*, their implementations should be in the source file.

The `private` and `public` keywords are used to define the *scope* of every data member and method. 
Private data members and methods can only be accessed within the class' own methods, whereas public data members and methods can be accessed in any part of the program where an object of that class exists. 
Sometimes you may not know when to make something private or public, but there are a few pretty straightforward rules:

1. Nearly all data members (variables in particular) should be private, since you want your class to have full control over its own properties, without interference from other parts of the program. However, if you have a data member that is constant, you may consider making it public.
2. Methods are the ways by which a class interacts with the "outside world", so a class will likely have many methods, and if you aren't sure whether a method should be public or private, public is the more likely answer. However, if you have any sort of helper method, especially one that shouldn't ever need to be called in some other part of the program, it should be made private.
3. Constructors and the destructor will always be public, as you'll shortly see why.

Constructors and destructors are an integral part of every class definition, and every class will have at least one constructor and one destructor (which may be implicit). 
The essential idea behind a constructor is that when you want to create an object from a class, the class needs to know what values to assign to all of its data members. 
Thus a constructor functions similarly to a method, except it is called (once) automatically when an object is first created. 
In the case of the `MyString` class, the constructors are: `MyString();` and `MyString(const char *);`. 
The naming here is no coincidence, as a constructor is always defined in the form `ClassName(type1 param1, type2, param2, ...);`. 
When a constructor has no parameters, it is called the *default constructor*; **every class is required to have at least one constructor**.

If a constructor is called when a class is created, then you might have been able to guess that the destructor is called when the class is destroyed, or deallocated. 
An object may be destroyed when the function call in which an object was created returns, or an object created dynamically is deallocated explicitly. 
The purpose of a destructor is typically to "clean up" before the object's data is deallocated. 
Most commonly, this involves deallocating *all data* that was dynamically allocated by the object, but there can occasionally be other use-cases too. 
If a class doesn't use any dynamically allocated memory, the destructor may not be explicitly defined, and a default "do-nothing" destructor is used.

#### 2.1.4 Implementing Class Methods

Implementing class methods is a fairly straight-forward process.
Once the header file has been created, and all relevant methods declared, all you need to do is import that header into a `.cc` or `.cpp` source file and start writing.
For today, we have provided you with a ready-made source file to fill in. 
However, when you inevitably go to create your own classes, there are some important points to keep in mind.
The most important is that all methods must be properly scoped.

For example, if you've declared the method `uint find(char);` within the `MyString` class, when you go to implement this method, you must specify that the function you are defining is in fact a method of the `MyString` class, like so:

```c++
uint MyString::find(char) {}
```

Note that we still need to specify the return type and parameter type, even though these were specified in the method declaration.
The most important thing to note is the `MyString::` scope specifier, which is what allows the compiler to know that your implementation is itself a method.

#### 2.1.5 Creating and Using Objects

Classes are created using their constructors, and they can be used much like any STL object you may have encountered.

For example:

```c++

int main(void) {
    MyString empty_string;
    MyString hello("Hello");

    std::cout << hello.find('H') << std::endl;
    return 0;
}
```

Your only constraint is what methods you've implemented. 
C++ allows you to create highly complex objects that can go so far as overloading operators (+, -, /, %, etc). 
This "operator overloading" allows developers to make their classes function much like native objects in a language.

### 2.2 Dynamic Memory

Unlike memory on the stack, which is allocated and deallocated automatically as your program operates, dynamic memory was designed to be completely controlled by the developer. 
Much like a manual car, you must handle all operations explicitly. 
Normally referred to as the "heap", if you wish to dynamically allocate a variable you must explicitly use the `new` operator, likewise, when you are done with this variable, you must call `delete`, otherwise the program will suffer from memory leaks, where memory is never deallocated.

As you will see in today's lab, almost all class data members are dynamically allocated so that they can be saved from method call to method call without having to explicitly pass around the data.

If you want more details on dynamic memory allocation, this [document](https://www.tutorialspoint.com/cplusplus/pdf/cpp_dynamic_memory.pdf) provides a quick introduction.

## 3. The Starter Code

### 3.1 Descriptions of functions

```c++
    class MyString {
        private:
	    // declare all your data members here
	    
        public:
            // constructors and destructor
            MyString();
            MyString(const char *);
            ~MyString();

            // other functions
            unsigned int len();

            void set(int, char);
            char get(int);
            
            const char *c_str();
            
            void reverse();
            
            unsigned int find_first(char);
            unsigned int find_first(const char *);
            unsigned int find_last(char);
            unsigned int find_last(const char *);
            
            int compare(const char *);
            
            void append(char);
            void append(const char *);
    }
```

- `MyString()` --  Default constructor; Should store an empty string.

- `MyString(const char *)` --  Copy constructor; Copy the contents of the input string into the class's data member.

- `~MyString()` --  Destructor; Should deallocate any dynamically allocated memory that the class uses.

- `len()` --  Returns the length of string. This is the number of characters in the string, excluding the null terminator.

- `set(int, char)` -- Sets the character at the given index to the character provided.

- `get(int)` -- Returns the character at the given index.

- `c_str()` --  Returns a pointer to a character array of the object's string.

- `reverse()` --  Reverse the string. "hello" should turn into "olleh". If you would like a challenge try to do it in-place (cannot create another array).

- `find_first(char)` --  Find the first occurrence of this character, and return the index. Return `-1` if it can't be found.

- `find_first(const char *)` --  Find the first occurrence of the input string. Return the index of the starting character. Return the `-1` if it can't be found.

- `find_last(char)` --  Find the last occurrence of this character, and return the index. Return the `-1` if it can't be found.

- `find_last(const char *)` --  Find the last occurrence of the input string. Return the index of the starting character. Return the `-1` if it can't be found.

- `compare(const char *)` --  Return a negative number if the object's string is greater, zero if they are equal, and a positive number if the input string is greater. *(a string is greater than another if the first differing character has a larger ascii value than the other string)*

- `append(char)` -- Append a single character onto the end of the string.

- `append(const char *)` --  Concatenate the input string to the object's string.

## 4. Instructions

Today you will need to implement all functions declared in the header file for the `MyString` class.

> You can start writing any function you want, but most tests rely on the constructor, and the `c_str()` function, so it would probably be best to write those functions first.

You need to modify two files, `mystring.cpp` and `mystring.hpp`. 
**The only modification** needed for the `mystring.hpp` file is to add the private data members you will use.

For testing, we are using a Unit Testing Framework called [catch2](https://github.com/catchorg/Catch2). 
It should tell you how many tests you are passing, which test failed, and what your output is compared to the expected output.  

You can compile your program using:

```bash
$ g++ -g tests.cpp mystring.cpp -o mystring
```

This bash command compiles our tests, with our implementations, and outputs them to a program called "mystring".

There are a number of flags you may wish to use when running your tests. To see them all, run your program as follows:

```bash
$ ./mystring -h
```

One example of a potentially helpful flag is `-s`, which displays the tests you pass, along with the ones you fail.

### 5. Submitting your work

For today's lab, you must submit your source file, along with any test cases you came up with to further test your implementations.
Note that creating new test cases is not a requirement today, but it is greatly encouraged.

> If you haven't written any new tests and you finish the lab early, try to break your implementations with clever edge cases.
