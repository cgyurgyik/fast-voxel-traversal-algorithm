### About
A prototype for the implementation of Amanatides & Woo's "A Fast Voxel Traversal Algorithm" in C++. Note, this has not been tested, and is not guaranteed to be bug-free. An overview of the algorithm can be found [https://docs.google.com/document/d/1QvWw81A0T5vcMAt1WElDeSdBmsw0KJvJdYNr7XfRHfw/edit?usp=sharing](here) (WIP).

### Notes
- Instead of using ```double``` or ```float```, I've decided to use ```value_type``` which can be set to a user-specified type in ```Vec3.h```.

### References
- ["Amanatides & Woo "A Fast Voxel Traversal Algorithm"](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.42.3443&rep=rep1&type=pdf)
- [Williams, Barrus, et. al "An Efficient and Robust Ray–Box Intersection Algorithm"](http://www.cs.utah.edu/~awilliam/box/box.pdf)
