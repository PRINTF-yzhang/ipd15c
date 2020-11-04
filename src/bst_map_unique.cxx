#include "bst_map_unique.hxx"

#include <vector>


Bst_map::Bst_map()
        : size_(0)
        , root_(nullptr)
{ }


Bst_map::Bst_map(Bst_map const& other)
        : size_(other.size_)
        ,root_(copy_nodes_(other.root_))
{ }


Bst_map& Bst_map::operator=(Bst_map const& other)
{
    size_ = other.size_;
    delet_nodes_(root_);
    root_ = copy_nodes_(other.root_);
}


void Bst_map::insert(Bst_map::key_t key, Bst_map::value_t value)
{
    node_ptr *currp = &root_;

    while (*currp) {
        if (key < (*currp)->key) {
            currp = &(*currp)->left;
        } else if (key > (*currp)->key) {
            currp = &(*currp)->right;
        } else {
            (*currp)->value = value;
            return;
        }
    }

    *currp = node_ptr(new Node_{key, value, nullptr, nullptr});
    ++size_;
}


Bst_map::value_t const* Bst_map::lookup(Bst_map::key_t key) const
{
    const node_ptr* currp = &root_;

    while (*currp) {
        if (key < (*currp)->key) {
            currp = &(*currp)->left;
        } else if (key > (*currp)->key) {
            currp = &(*currp)->right;
        } else {
            return &(*currp)->value;
        }
    }

    return nullptr;
}


void Bst_map::remove(Bst_map::key_t key)
{
    node_ptr *currp = &root_;

    while (*currp) {
        if (key < (*currp)->key) {
            currp = &(*currp)->left;
        } else if (key > (*currp)->key) {
            currp = &(*currp)->right;
        } else {
            node_ptr& curr = *currp;

            // if curr has both children,
            //
            //      curr      =>     S
            //   /        \        /   \
            //  L          R      L     R
            //            /            /
            //           .            .
            //          .            .
            //         .            .
            //        S           SR...
            //         \
            //          SR...
            if (curr->left && curr->right) {
                node_ptr* sp = &curr->right;
                while ((*sp)->left) {
                    sp = &(*sp)->left;
                }

                node_ptr& s = *sp;

                std::swap(curr->left, s->left);
                std::swap(curr->right, s->right);
                std::swap(curr, s);
                s = std::move(s->right);
            }
            // if curr has a left child only, replace it with that child
            else if (curr->left) {
                curr = std::move(curr->left);
            }
            // if curr has no left child, replace it with the right child
            else {
                curr = std::move(curr->right);
            }

            --size_;

            return;
        }
    }
}


size_t Bst_map::size() const
{
    return size_;
}




std::unique_ptr<Bst_map::Node_> Bst_map::copy_nodes_(std::unique_ptr<Bst_map::Node_> uniquePtr) {
    std::unique_ptr<Bst_map::Node_> copyMap = NULL;
    if(uniquePtr){
        copyMap->key = uniquePtr->key;
        copyMap->value = uniquePtr->value;

        copyMap->left = copy_nodes_(uniquePtr->left);
        copyMap->right = copy_nodes_(uniquePtr->right);
    }
    return copyMap;
}

