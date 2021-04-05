#include "RBTree.hpp"
#include <cstring>
#include <iostream>

// Node::red
template <class T_KEY, class T_ITEM>
const bool Node<T_KEY, T_ITEM>::red = true;

// Node::black
template <class T_KEY, class T_ITEM>
const bool Node<T_KEY, T_ITEM>::black = false;

// Скрытый конструктор умолчания для листа
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM>::Node() {
    left = right = p = this;
    color = Node::black;
}

// Лист в о-сти видимости Node
template <class T_KEY, class T_ITEM>
static Node<T_KEY, T_ITEM> nil_node_ = Node<T_KEY,T_ITEM>();

// Лист в о-сти видимости Node
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM> *const Node<T_KEY, T_ITEM>::nil_node = &nil_node_<T_KEY,T_ITEM>;

// Конструктор для создания новых Node
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM>::Node(const T_KEY& ukey, const T_ITEM& uitem, bool ucolor) : key(ukey), item(uitem) {
    color = ucolor;
    left = right = p = nil_node;
};

// Конструктор копирования Node
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM>::Node(const Node& src, Node *up) {
    memcpy(this, &src, sizeof(Node));
    p = up;
    left = right = nil_node;
}

// Лист в о-сти видимости RBTree
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM> *const RBTree<T_KEY, T_ITEM>::nil_node = Node<T_KEY, T_ITEM>::nil_node;

// Конструктор умолчания RBTree
template <class T_KEY, class T_ITEM>
RBTree<T_KEY, T_ITEM>::RBTree() {
    root = RBTree<T_KEY, T_ITEM>::nil_node;
}

// Вспомогательная ф-ция для КК RBTree
template <class T_KEY, class T_ITEM>
static Node<T_KEY,T_ITEM> *copy(const Node<T_KEY,T_ITEM> *src) {
    Node<T_KEY,T_ITEM> *root;
    Node<T_KEY,T_ITEM> *dst;

    if (src == Node<T_KEY,T_ITEM>::nil_node) {
        return Node<T_KEY,T_ITEM>::nil_node;
    }
    dst = root = new Node<T_KEY,T_ITEM>(*src, Node<T_KEY,T_ITEM>::nil_node);
    while (src != Node<T_KEY,T_ITEM>::nil_node) {
        if (src->left != Node<T_KEY,T_ITEM>::nil_node && dst->left == Node<T_KEY,T_ITEM>::nil_node) {
            dst = dst->left = new Node<T_KEY,T_ITEM>(*(src->left), dst);
            src = src->left;
        } else if (src->right != Node<T_KEY,T_ITEM>::nil_node && dst->right == Node<T_KEY,T_ITEM>::nil_node) {
            dst = dst->right = new Node<T_KEY,T_ITEM>(*(src->right), dst);
            src = src->right;
        } else {
            dst = dst->p;
            src = src->p;
        }
    }
    return root;
}
// Конструктор копирования RBTree
template <class T_KEY, class T_ITEM>
RBTree<T_KEY, T_ITEM>::RBTree(const RBTree& tree) {
    root = copy(tree.root);
}

// Вспомогательная ф-ция для ~RBTree
template <class T_KEY, class T_ITEM>
static void delete_node(Node<T_KEY, T_ITEM> *node) {
    if (node->left != Node<T_KEY, T_ITEM>::nil_node) {
        delete_node(node->left);
    }
    if (node->right != Node<T_KEY, T_ITEM>::nil_node) {
        delete_node(node->right);
    }
    delete node;
}

template <class T_KEY, class T_ITEM>
RBTree<T_KEY, T_ITEM>::~RBTree() {
    if (root != nil_node) {
        delete_node(root);
    }
}

template <class T_KEY, class T_ITEM>
RBTree<T_KEY, T_ITEM>& RBTree<T_KEY, T_ITEM>::operator=(const RBTree& src) {
    if (this == &src) {
        return *this;
    }
    if (root != nil_node) {
        delete_node(root);
    }
    root = copy(src.root);
    return *this;
}

// Вернуть узел(Node *) по ключу(T_KEY)
template <class T_KEY, class T_ITEM>
Node<T_KEY, T_ITEM> *RBTree<T_KEY, T_ITEM>::get_node(const T_KEY& key) const {
    Node<T_KEY, T_ITEM> *x = root;

    while (x != nil_node && x->key != key) {
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

// Вспомогательная ф-ция для RBTree::insert()
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::left_rotate(Node<T_KEY, T_ITEM> *x) {
    Node<T_KEY, T_ITEM> *y = x->right;

    x->right = y->left;
    if (y->left != nil_node) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == nil_node) {
        root = y;
    } else {
        if (x == x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }
    }
    y->left = x;
    x->p = y;
}

// Вспомогательная ф-ция для RBTree::insert()
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::right_rotate(Node<T_KEY, T_ITEM> *y) {
    Node<T_KEY, T_ITEM> *x = y->left;

    y->left = x->right;
    if (x->right != nil_node) {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == nil_node) {
        root = x;
    } else {
        if (y == y->p->left) {
            y->p->left = x;
        } else {
            y->p->right = x;
        }
    }
    x->right = y;
    y->p = x;
}

// Вспомогательная ф-ция для RBTree::insert()
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::insert_fixup(Node<T_KEY, T_ITEM> *z) {
    Node<T_KEY, T_ITEM> *y;

    while (z->p->color == Node<T_KEY, T_ITEM>::red && z != root) {
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y != nil_node && y->color == Node<T_KEY, T_ITEM>::red) {
                z->p->color = Node<T_KEY, T_ITEM>::black;
                y->color = Node<T_KEY, T_ITEM>::black;
                z->p->p->color = Node<T_KEY, T_ITEM>::red;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(z);
                }
                z->p->color = Node<T_KEY, T_ITEM>::black;
                z->p->p->color = Node<T_KEY, T_ITEM>::red;
                right_rotate(z->p->p);
            }
        } else {
            y = z->p->p->left;
            if (y != nil_node && y->color == Node<T_KEY, T_ITEM>::red) {
                z->p->color = Node<T_KEY, T_ITEM>::black;
                y->color = Node<T_KEY, T_ITEM>::black;
                z->p->p->color = Node<T_KEY, T_ITEM>::red;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(z);
                }
                z->p->color = Node<T_KEY, T_ITEM>::black;
                z->p->p->color = Node<T_KEY, T_ITEM>::red;
                left_rotate(z->p->p);
            }
        }
    }
    root->color = Node<T_KEY, T_ITEM>::black;
}

// Вставить узел в RBTree
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::insert(Node<T_KEY, T_ITEM> *z) {
    Node<T_KEY, T_ITEM> *y = nil_node;
    Node<T_KEY, T_ITEM> *x = root;

    while (x != nil_node) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            x->item = z->item;
            return ;
        }
    }
    z->p = y;
    if (y == nil_node) {
        root = z;
    } else {
        if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
    z->left = nil_node;
    z->right = nil_node;
    z->color = Node<T_KEY, T_ITEM>::red;
    insert_fixup(z);
}

// Вставить значение(item) по ключу(key)
template <class T_KEY, class T_ITEM>
Node<T_KEY,T_ITEM> *RBTree<T_KEY, T_ITEM>::insert(const T_KEY& key, const T_ITEM& item) {
    Node<T_KEY, T_ITEM> *node = new Node<T_KEY, T_ITEM>(key, item);
    insert(node);
    return node;
}

// Вспомогательная ф-ция для RB_Tree::remove
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::transplant(Node<T_KEY, T_ITEM> *u, Node<T_KEY, T_ITEM> *v) {
    if (u->p == nil_node) {
        root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    v->p = u->p;
}

// Вспомогательная ф-ция для RB_Tree::remove
template <class T_KEY, class T_ITEM>
static Node<T_KEY, T_ITEM> *min(Node<T_KEY, T_ITEM> *x) {
    while (x->left != Node<T_KEY, T_ITEM>::nil_node) {
        x = x->left;
    }
    return x;
}

// Вспомогательная ф-ция для RB_Tree::remove
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::remove_fixup(Node<T_KEY, T_ITEM> *x) { 
    Node<T_KEY, T_ITEM> *w;

    while (x != root && x->color == Node<T_KEY, T_ITEM>::black) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == Node<T_KEY, T_ITEM>::red) {
                w->color = Node<T_KEY, T_ITEM>::black;
                x->p->color = Node<T_KEY, T_ITEM>::red;
                left_rotate(x->p);
                w = x->p->right;
            }
            if (w->left->color == Node<T_KEY, T_ITEM>::black && w->right->color == Node<T_KEY, T_ITEM>::black) {
                w->color = Node<T_KEY, T_ITEM>::red;
                x = x->p;
            } else {
                if (w->right->color == Node<T_KEY, T_ITEM>::black) {
                    w->left->color = Node<T_KEY, T_ITEM>::black;
                    w->color = Node<T_KEY, T_ITEM>::red;
                    right_rotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = Node<T_KEY, T_ITEM>::black;
                w->right->color = Node<T_KEY, T_ITEM>::black;
                left_rotate(x->p);
                x = root;
            }
        } else {
            w = x->p->left;
            if (w->color == Node<T_KEY, T_ITEM>::red) {
                w->color = Node<T_KEY, T_ITEM>::black;
                x->p->color = Node<T_KEY, T_ITEM>::red;
                right_rotate(x->p);
                w = x->p->left;
            }
            if (w->right->color == Node<T_KEY, T_ITEM>::black && w->left->color == Node<T_KEY, T_ITEM>::black) {
                w->color = Node<T_KEY, T_ITEM>::red;
                x = x->p;
            } else {
                if (w->left->color == Node<T_KEY, T_ITEM>::black) {
                    w->right->color = Node<T_KEY, T_ITEM>::black;
                    w->color = Node<T_KEY, T_ITEM>::red;
                    left_rotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = Node<T_KEY, T_ITEM>::black;
                w->left->color = Node<T_KEY, T_ITEM>::black;
                right_rotate(x->p);
                x = root;
            }
        }
    }
    x->color = Node<T_KEY, T_ITEM>::black;
}

// Удалить конкретный узел(Node)
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::remove(Node<T_KEY, T_ITEM> *z) {
    Node<T_KEY, T_ITEM> *y = z;
    Node<T_KEY, T_ITEM> *x;
    bool color = y->color;

    if (z == nil_node) {
        return ;
    }
    if (z->left == nil_node) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil_node) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = min(z->right);
        color = y->color;
        x = y->right;
        if (y->p == z) {
            x->p = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (color == Node<T_KEY, T_ITEM>::black) {
        remove_fixup(x);
    }
    delete z;
}

// Удалить по ключу(key)
template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::remove(const T_KEY& key) {
    Node<T_KEY, T_ITEM> *todel = get_node(key);

    if (todel == nil_node) {
        return ;
    }
    remove(todel);
}

template <class T_KEY, class T_ITEM>
void Node<T_KEY, T_ITEM>::run() {
    std::cout << "Key: " << key << " Parent_key: " << p->key;
    std::cout << " Color: " << (color == red ? "red" : "black") << std::endl;
    if (left != nil_node) {
        left->run();
    }
    if (right != nil_node) {
        right->run();
    }
}

template <class T_KEY, class T_ITEM>
void RBTree<T_KEY, T_ITEM>::run() {
    root->run();
}