/*
 * The exercise is in src/bst_map_{raw,unique}.cxx. The goal is to implement
 * the copy constructor and copy-assignment operator for one or the other, so
 * that `Bst_map`s become safely copyable.
 */

/*
 * 15.c.1
 * BST map interface and representation
 * Binary search tree map
 * the public interface
 * the representation
 * public: insert(); lookup(); remove(); size();
 * private: struct Node_{ key ; value; Node_* left; Node_* right ); size_; root_;
 *
 *
 * 15.c.2
 * implementing tree operations
 *
 */

//void Bst_map::insert(Bst_map::key_t key, Bst_map::value_t value)
//{
//    node_ptr *currp = &root_;
//
//    while (*currp) {
//        if (key < (*currp)->key) {  // If the given key is smaller than
//      // node's key then go to left subtree
//            currp = &(*currp)->left;
//        } else if (key > (*currp)->key) {
//     //If the given key is greater than
//    // node's key then go to right subtree
//            currp = &(*currp)->right;
//        } else {
//            (*currp)->value = value;
//            return;
//        }
//    }
//    //    // If BST doesn't exist
//    // create a new node as root
//    // or it's reached when
//    // there's no any child node
//    // so we can insert a new node here
//    *currp = node_ptr(new Node_{key, value, nullptr, nullptr});
//    ++size_;
//}


/*
 * 15.c.3
 * implementing remove
 * no children
 *           50                            50
           /     \         remove(20)      /   \
          30      70       --------->    30     70
         /  \    /  \                     \    /  \
       20   40  60   80                   40  60   80
one children

 *            50                            50
           /     \         remove(30)      /   \
          30      70       --------->    40     70
            \    /  \                          /  \
            40  60   80                       60   80
both children

 *           50                              60
           /     \         remove(50)      /   \
          40      70       --------->    40    70
                 /  \                            \
                60   80                           80
 */
