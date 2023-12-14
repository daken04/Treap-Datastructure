# Treap Data Structure

## Problem Statement

Implement a treap with implicit indexing, combining features of a binary search tree (BST) and a heap. The treap maintains both ordering and prioritization of elements using randomized priorities.

### Underlying Implementation

The underlying implementation of a treap relies on a randomized structure where each node has a key and priority, allowing for logarithmic time complexity operations. It does not rely on strict balance conditions but maintains balanced performance on average.

### Implicit Indexing

In the context of a treap, implicit indexing means that elements are identified and ordered within the structure based on their positions, without explicitly assigned index values. This simplifies the treap's design and is used for efficient operations on the elements.

### Operations

1. **`bool empty()`**
   - Expected Time Complexity: O(1)
   - Returns if the treap is empty or not
   - Print `true` or `false` on a new line

2. **`int size()`**
   - Expected Time Complexity: O(1)
   - Returns the size of the treap
   - Print the returned value on a new line

3. **`void clear()`**
   - Expected Time Complexity: O(n)
   - Releases all acquired memory and clears the treap
   - Don’t print anything

4. **`int insert(T val)`**
   - Expected Time Complexity: O(log n)
   - Inserts `val` into the treap and returns the index
   - Print the returned value on a new line

5. **`bool erase(int index)`**
   - Expected Time Complexity: O(log n)
   - Deletes the value at the given index and returns true if the index was valid, else returns false
   - Print the returned value on a new line

6. **`int indexOf(T val)`**
   - Expected Time Complexity: O(log n)
   - Returns the index of `val` if it exists; otherwise, returns -1
   - Print the returned value on a new line

7. **`T atIndex(int index)`**
   - Expected Time Complexity: O(log n)
   - Returns the value at the given index if valid; otherwise, returns the default value of `T`
   - Print the returned value on a new line (operator<< is guaranteed to work with given T)

8. **`treap<T>* merge(treap<T> *t2)`**
   - Expected Time Complexity: O(log n)
   - Merges `t1` and `t2` when called as `t1->merge(t2)`, where `t1` and `t2` are treap<T> pointers. (You can assume that all the values in `t1` will be less than or equal to all the values in `t2`).
   - Returns the pointer to the new merged treap
   - Don’t print anything

9. **`std::pair<treap<T>*, treap<T>*> split(int index)`**
   - Expected Time Complexity: O(log n)
   - Splits the treap at the given index, such that the elements before the given index are in the first treap and the elements from the index (and afterwards) are in the second treap
   - Returns the pair of pointers to the new treaps
   - Don’t print anything

10. **`bool erase(int first, int last)`**
    - Expected Time Complexity: O(log n)
    - Deletes the values between the given indices (inclusive) and returns true if the whole index range was valid (completely inside the treap); else, returns false
    - Print the returned value on a new line

11. **`treap<T>* slice(int first, int last)`**
    - Expected Time Complexity: O(log n)
    - Returns a pointer to the new treap consisting of values between the given indices (inclusive) if the index range was valid; else, returns nullptr
    - Don’t print anything
    - For testing, you need to consider the sliced treap for further commands instead of the original treap.

12. **`int lower_bound(T val)`**
    - Expected Time Complexity: O(log n)
    - Returns the number of elements strictly less than `val`
    - Print the returned value on a new line

13. **`int upper_bound(T val)`**
    - Expected Time Complexity: O(log n)
    - Returns the number of elements less than or equal to `val`
    - Print the returned value on a new line

14. **`int count(T val)`**
    - Expected Time Complexity: O(log n)
    - Returns the number of elements equal to `val`
    - Print the returned value on a new line

15. **`std::vector<T> to_array()`**
    - Expected Time Complexity: O(n)
    - Returns the vector of values in sorted order
    - Print each element space-separated

### Input Format

There is an infinitely running menu-driven main function. Each time the user inputs an integer corresponding to the serial number of the operation listed above, the code takes necessary arguments related to the selected operation and executes the respective method. Finally, the program must exit with status code 0 when 0 is provided as a choice.
