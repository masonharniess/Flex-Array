# Flex Array

The primitive C/C++ array is simple and efficient, but it has many problems, such as requiring a fixed size to be known at creation time. 

## Overview of the Data Structure

The flex array uses a dynamically-allocated standard C++ array to store the elements internally (referred to here as the internal array). 

The internal array may be bigger than necessary to store all elements that it currently contains, with empty space at either side of the elements (referred to here as headroom and tailroom respectively). These exist so that insertion and removal from either ends of the flex array can be done efficiently. 

The size of the internal array is referred to as the capacity of the flex array, and the number of actual elements stored is referred to as the size. 

The elements must be stored in one contiguous block with no empty space between those elements. For instance, a flex array that contains five elements ```[31, 41, 59, 26, 53]``` may look like ```[X, X, X, 31, 41, 59, 26, 53, X]``` internally, where ```X``` is used to represent empty space in the internal array. 

The example provided above has a size of 5, capacity of 9, a headroom of size 3, and a tailroom of size 1. To the end user, the 0th element is 31, the first element is 41, and so on.

## Supported Operations

### Basic Class Functions

```FlexArray()```: Default constructor. Initializes the FlexArray to have size 0 and capacity ```INITIALCAP``` (a constant equal to 5 defined in FlexArray.h).

```FlexArray(const int* arr, int size)```: Parameterised constructor. ```arr``` points to the beginning of an integer array and ```size``` represents the number of elements in the array.

```~FlexArray()```: Destructor. Releases all memory used.

```FlexArray(const FlexArray& other)```: Copy constructor. ```other``` represents the ```FlexArray``` object being copied.

```FlexArray& operator=(const FlexArray& other);``` Copy assignment operator. Assigns the contents of one ```FlexArray``` object to another.

### Printing & Size Information

```string print()```: Returns a string that lists all elements in order.

```string printAll()```: Returns a string that lists all elements in order, including empty spaces.

```int getSize()```: Returns the number of elements stored.

```int getCapacity()```: Returns the size (capacity) of the internal array. 

### Getters & Setters

```int get(int i)```: Returns the value stored in the flex array corresponding to a given index ```i```.

```bool set(int i, int v)```: Store the value ```v``` at the given index ```i```, replacing the old value stored there. If the index is within bounds, it returns ```true```. If the index is out of bounds, the function returns ```false``` and makes no changes to the flex array. 

### Structural Modifiers 

```void push_back(int v)```: Insert the integer ```v``` in the position after the last element of the flex array.

```bool pop_back()```: Remove the last element.

```void push_front(int v)```: Insert the integer ```v``` before the first element of the flex array. The new element enters the 0th position and the original element enters the 1st.

```bool pop_front()```: Remove the first element.

```bool insert(int i, int v)```: Insert the integer ```v``` at index ```i``` of the flex array.

```bool erase(int i)```: Remove the element at index ```i```. The element that was at index ```i+1``` will now be at index ```i```, and so on.
