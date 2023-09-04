#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>
#include <vector>
#include <cstdlib>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
private:
    struct Node { //make Struct Node for binary tree with left and right nodes and constructor
        KeyType key;
        std::vector<ValueType> values;
        Node* left;
        Node* right;

        Node(const KeyType& k, const ValueType& v)
            : key(k), left(nullptr), right(nullptr)
        {
            values.push_back(v);
        }
    };

public:
    class Iterator
    {
    public:
        Iterator()
        : current(nullptr), index(0)
        {}

        Iterator(Node* n)
        : current(n), index(0)
        {}

        ValueType& get_value() const // if valid, return value
        {
            if (!is_valid()) {
                std::exit(EXIT_FAILURE);
            }
            return current->values[index];
        }

        bool is_valid() const
        {
            return (current != nullptr);
        }

        void advance() //iterate through the tree
        {
            if (!is_valid()) {
                std::exit(EXIT_FAILURE);
            }
            if (index == current->values.size()-1) {
                current = nullptr;
            }
            else{
                ++index;
            }
        }

    private:
        Node* current;
        int index;
    };

    TreeMultimap()
        : m_root(nullptr)
    {}

    ~TreeMultimap()
    {
        destroy(m_root); //calls my destructor with one parameter to the root node.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr) {
            m_root = new Node(key, value); //if empty tree
        }
        else {
            Node* node = search(m_root, key); // call search helper function
            if (node == nullptr) {
                node = m_root;
                while ((key < node->key && node->left != nullptr) || (key >= node->key && node->right != nullptr)) { //loop while end of the binary tree
                    if (key < node->key) { // if key is less than the value of the node, move left becuase (binary tree is always ordered)
                        node = node->left;
                    }
                    else {
                        node = node->right;
                    }
                }
                if (key < node->key) {
                    node->left = new Node(key, value);
                }
                else {
                    node->right = new Node(key, value);
                }
            }
            else {
                node->values.push_back(value);
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* node = search(m_root, key);
        if (node != nullptr) {
            return Iterator(node);
        }
        return Iterator();
    }

private:
    Node* m_root;
    
    //recursive functions in private to ensure conciseness of my code and time complexit of O(V)
    void destroy(Node* node) //O(Log N) Post-Order traversal to free all my dynamically allocated memory.
    {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    Node* search(Node* node, const KeyType& key) const //O(Log N)to recusively traverse an ordered binary tree.
    {
        if (node == nullptr || node->key == key) {
            return node;
        }
        else if (key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }
};

#endif
