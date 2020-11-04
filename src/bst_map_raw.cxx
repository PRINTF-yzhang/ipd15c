#include "bst_map_raw.hxx"


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
    if(*this == &other)
        return *this;
    delet_nodes_(root_);
    root_ = copy_nodes_(other.root_);
    return *this;
}


Bst_map::~Bst_map()
{
    std::vector<node_ptr> stack;

    if (root_) stack.push_back(root_);

    while (!stack.empty()) {
        node_ptr victim = stack.back();
        stack.pop_back();

        if (victim->left) stack.push_back(victim->left);
        if (victim->right) stack.push_back(victim->right);

        delete victim;
    }
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

void Bst_map::delet_nodes_(Bst_map::Node_ *pNode) {
    delete root_;
}

Bst_map::node_ptr Bst_map::copy_nodes_(Bst_map::node_ptr others) {
    Bst_map::node_ptr copyMap = NULL;
    if(others){
        copyMap->key = others->key;
        copyMap->value = others->value;
        copyMap->left = copy_nodes_(others->left);
        copyMap->right = copy_nodes_(others->right);

    }
    return copyMap;
}
