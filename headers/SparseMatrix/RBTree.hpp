#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <ostream>
#include <cstddef>

/*
    T_KEY должен поддерживать операции сравнения <, >, ==
*/
template <class T_KEY, class T_ITEM>
struct Node
{
    static const bool                   red;
    static const bool                   black;
    static Node<T_KEY, T_ITEM> *const   nil_node;

    Node<T_KEY, T_ITEM>                 *left;
    Node<T_KEY, T_ITEM>                 *right;
    Node<T_KEY, T_ITEM>                 *p;
    T_KEY                               key;
    T_ITEM                              item;
    bool                                color;

    Node(const T_KEY&, const T_ITEM&, bool = red);
    Node(const Node&, Node * = nil_node);
    void run();
    //private:
    Node();
};

template <class T_KEY, class T_ITEM>
class RBTree
{
    Node<T_KEY, T_ITEM> *root;
    
    void left_rotate(Node<T_KEY, T_ITEM> *);
    void right_rotate(Node<T_KEY, T_ITEM> *);
    void insert_fixup(Node<T_KEY, T_ITEM> *);

    void transplant(Node<T_KEY, T_ITEM> *, Node<T_KEY, T_ITEM> *);
    void remove_fixup(Node<T_KEY, T_ITEM> *);

    public:
    static Node<T_KEY, T_ITEM> *const nil_node;
    
    RBTree();
    RBTree(const RBTree&);
    ~RBTree();
    RBTree& operator=(const RBTree&);

    void insert(Node<T_KEY, T_ITEM> *);
    Node<T_KEY,T_ITEM> *insert(const T_KEY&, const T_ITEM&);
    void remove(Node<T_KEY, T_ITEM> *);
    void remove(const T_KEY&);

    Node<T_KEY, T_ITEM> *get_node(const T_KEY&) const;
    void run();
};

#include "../../templates/SparseMatrix/RBTree.tcc"

#endif