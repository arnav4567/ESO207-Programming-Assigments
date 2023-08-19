How to run the .cpp file : The sets S1 and S2 are specified in the Test() function, so we can specify our input in that function by modifying it.

Two points to keep in mind while making a custom input:
1. The sets S1 and S2 should be sorted in ascending order.
2. The minimum element of one set should be greater than the maximum element of the other.


###Brief Overview of the Code

We have 2 custom data types in our code -

1. twothreenode - This is a node in the 2-3 tree.
2. returnfrominsert - This struct has been defined to facilitate the return of multiple fields from a function.

Also, the following functions have been used in our code -

1. MakeSingleton(x) makes a single node having the field y (of struct node)= x.
2. getHeight(T) returns the height of the tree rooted at T.
3. makeTwoNode(m, T1, T2) returns the pointer to the two-node having its two subtrees as T1 and T2(in that order). m is the minimum element in T2 here.
4. makeRoot(U,T,rightMin) - rightMin is the minimum value in the right subtree. A new root having this configuration(U, T) is made from this function.
5. InsertNode -Inserts the newly made node(s) into the tree.
6. Merge - This is the function called first on the two trees. It iterates to the location to which the tree has to be inserted. It binds all the above 3 functions and uses them as and when required.
7. Extract - Used to print the elements of the set represented by T, in ascending order.
8. Test - This specifies the input ( here, the sets S1 and S2) and prints the elements of the final set.


Only the Test() function is called in main(). The Test() function serves as a driver for the rest of the functions.  
