In this folder you can find our implementation of a Binary Search Tree.

In the include folder the file btree.h contains the implementation of the classes BTree, BNode, Iterator and ConstIterator, and the declarations of the functions.
In the src folder the file btree.cc contains our implementation of the functions of the BTree and BNode classes.
In the Doxygen folder you can find the Doxy file to generate the code documentation.
In the test folder there is the analysis of the find function after and before the tree is balanced.
In the main folder the file main_int.cc tests all the basic functions of the code using mainly integer keys.

You can compile the code using the provided Makefile:
writing "make" you will obtain an executable file main_test in the main folder and an executables testlognikOMP and testlog.x in the test folder.
Writing "make doc" you will obtain the Doxygen documentation of the file.
Writing "make clean" you can clean all the unnecessary files
