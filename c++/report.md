##Binary Search Tree report

The aim of this exam was to implement and test a Binary Search Tree in c++ language.
Our code implementation is divided into three parts: an header btree.h located inside the include folder, in which are defined the classes BTree and BNode and the their functions, and a source file btree.cc, located inside the src folder, in which the longer functions are implemented. The code is then used and tested in the files main_int.cc and testlog.cc.

The BTree class is templated on the key type, the value type and the comparison operator between keys, and so is the BNode class.

#BNode components
The primary componenet of the tree is the class BNode, defined inside the BTree class (..). A BNode contains:
an std::pair made by a key and an associated value, which is templated on the key type and value type;
two unique pointers to the left and right childs;
a raw pointer to the next node, which is then used by the Iterator...keep on reading to know more!
By doing this the only definition needed inside the tree is the unique pointer to the first node inserted, called root node.
The BNode class owns two different constructors:
one made only for the root node, which requires only the insertion of an std::pair;
one made for all the other nodes, whihc requires a pair and a pointer to the next node.
The BNode class contains some private methods which are mostly recursive and are used by other BTree public methods.

#BTree components
Inside the BTree class we defined and implemented the following data members:
a root unique pointer, as already said;
an instance of the comparison operator;
a BTree constructor, which needs an std::pair and a comparions operator, which for the moment is set to default; (ref?)
a BTree destructor, which calls the "clear()" method;
The Btree is provided with a copy semantic, which copies the tree using a BNode recursive function and construcs a new tree;
There are also the BTree move constructor and move assignment, which instead use the built-in std::move.

Inside the BTree we defined the class Iterator and ConstIterator; these objects contain a pointer to BNode, thanks to their methods they can be used to access every element of the tree in order, starting from the leftmost node and incrementing until the end of the tree.

Then, inside the source file we implement the following:
a function used to insert a new BNode using a new key-value type, which recursively calls a BNode insert function;
a function which prints out the tree, following the order of the keys (which uses the ConstIterator)
a function to balance the tree, which stores the tree in a vector following the order of the keys, then empties the tree using clear(), and then refills it in a recursive way using a private function, searching everytime the middle point of a given subvector.
A functions to check if the tree is balanced, which recursively computes the difference of the sub-trees depth.
(erase..)

