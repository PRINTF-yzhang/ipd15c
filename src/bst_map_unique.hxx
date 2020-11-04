#pragma once

#include <cstddef>
#include <memory>

// A map from `std::size_t` to `double`.
class Bst_map
{
public:
    using key_t = std::size_t;
    using value_t = double;

    // Constructs the empty map.
    Bst_map();

    // Copy constructor.
    Bst_map(Bst_map const&);

    // Copy-assignment operator.
    Bst_map& operator=(Bst_map const&);

    // Associates the given key with the given value in this map.
    void insert(key_t key, value_t value);

    // Finds out the value associated with the given key, or `nullptr` if
    // not present.
    const value_t* lookup(key_t key) const;

    // Removes the association with the given key.
    void remove(key_t key);

    // How many keys are mapped?
    size_t size() const;

private:
    struct Node_;
    using node_ptr = std::unique_ptr<Node_>;

    std::size_t size_;
    node_ptr    root_;




    std::unique_ptr<Node_> copy_nodes_(std::unique_ptr<Node_> others);
};

struct Bst_map::Node_
{
    key_t    key;
    value_t  value;
    node_ptr left;
    node_ptr right;
};
