#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <stdexcept>
#include "vector.hpp"

#define DICTIONARY_ALLOCATED_BLOCK 0x10


template<typename KeyType, typename ValueType>
struct Node
{
    KeyType key;
    ValueType value;
    Node<KeyType, ValueType> * left;
    Node<KeyType, ValueType> * right;

    ~Node()
    {
        left = nullptr;
        right = nullptr;
    }
};


// this is a dictionary type.
// it is an associative container that contains key-value pairs.
// This dictionary is built on  a BinarySearchTree, with the 
// key type being the "weight" for our tree.  This means the tree 
// will maintain order based on the keys.
template<typename KeyType, typename ValueType>
class Dictionary
{
private:

    Node<KeyType, ValueType> * _root = nullptr;
    
    // IMPLEMENT
    Node<KeyType, ValueType> * findKey(const KeyType & key, Node<KeyType, ValueType> * startingNode) const;
    // IMPLEMENT
    Node<KeyType, ValueType> * findParent(Node<KeyType, ValueType> *searchedNode, Node<KeyType, ValueType> *currentNode) const;

    // IMPLEMENT
    void DeletePostOrder(Node<KeyType, ValueType> * startingNode);
    // IMPLEMENT
    bool RecursiveInsert(const KeyType & key, const ValueType & value, Node<KeyType, ValueType> * node);
    // IMPLEMENT
    void InOrderKeys(Vector<KeyType> & keys, Node<KeyType, ValueType> *currentNode) const;

public:

    Dictionary() = default;
    ~Dictionary();

    // inserts the key/value pair into the tree.
    // returns true if successful, false if NOT successful.
    // THIS TREE CONTAINS ONLY UNIQUE IDS SO YOU CAN ONLY INSERT 
    // VALUES THAT HAVE NO KEYS CURRENTLY IN THE LIST
    // In order for this to work you must implement 
    //  RecursiveInsert
    bool Insert(const KeyType & key, const ValueType & value);

    // removes the key in question
    // returns false if the key did not exist
    // returns true if it did
    // In order for this to work 
    // In order for this to work you must implement 
    //  findKey() AND findParent()
    bool Remove(const KeyType & key);

    // returns a Vector of all keys in the list.
    Vector<KeyType> Keys() const;

    // returns if the dictionary is empty
    bool IsEmpty() const;

    // Checks if a key exists in the tree
    bool Contains(const KeyType & key) const;

    // finds the value with the assosiated key. 
    ValueType At(const KeyType & key) const;
};

// Calls DeletePostOrder on the Root
template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary()
{
    DeletePostOrder(_root);
}

// inserts a New Node with the desired key / value into the Binary Search Tree.
// returns true if its successful, and false if not.
template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Insert(const KeyType & key, const ValueType & value)
{
    // case 1: root is null
    if(_root == nullptr)
    {    
        _root = new Node<KeyType, ValueType>();
        _root->key = key;
        _root->value = value;
        return true;
    }

    // case2, use recursive insert to insert the new Node
    return RecursiveInsert(key, value, _root);
}

// removes the required node with a key equal to the key in question.
// Returns false if the delete was not successfull, true otherwise.
// HINT: Use "Find Node" and "Find Parent" functions to simplify this code
template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Remove(const KeyType & key)
{
    Node<KeyType, ValueType> *foundNode = findKey(key, _root);
    // key not found
    if(foundNode == nullptr)
    {
        return false;
    }

    // case 1: Leaf Node
    if(foundNode->left == nullptr && foundNode->right == nullptr)
    {
        Node<KeyType, ValueType> * parent = findParent(foundNode, _root);
        if(parent != nullptr)
        {
            if(parent->left == foundNode)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        delete foundNode;
        return true;
    }

    // Case 2: 1 Child
    if(foundNode->left == nullptr && foundNode->right != nullptr)
    {
        // handle root differently
        if(foundNode == _root)
        {
            _root = foundNode->right;
            delete foundNode;
            return true;
        }
        // otherwise find parent
        Node<KeyType, ValueType> *parent = findParent(foundNode, _root);
        if(parent->left == foundNode)
        {
            parent->left = foundNode->right;
        }
        else
        {
            parent->right = foundNode->right;
        }
        delete foundNode;
        return true;
    }
    else if(foundNode->left != nullptr && foundNode->right == nullptr)
    {
        // handle root differently
        if(foundNode == _root)
        {
            _root = foundNode->left;
            delete foundNode;
            return true;
        }
        // otherwise find parent
        Node<KeyType, ValueType> *parent = findParent(foundNode, _root);
        if(parent->left == foundNode)
        {
            parent->left = foundNode->left;
        }
        else
        {
            parent->right = foundNode->left;
        }
        delete foundNode;
        return true;
    }

    // case 3: 2 children
    // first handle special case 
    if(foundNode->right->left == nullptr)
    {
        foundNode->value = foundNode->right->value;
        foundNode->key = foundNode->right->key;
    }


    Node<KeyType, ValueType> *nextNode = foundNode->right;
    Node<KeyType, ValueType> *parentNode = foundNode;
    while(nextNode->left != nullptr)
    {
        parentNode = nextNode;
        nextNode = nextNode->left;
    }

    // copy the values from this NextNode to our foundNode
    KeyType tmpKey = foundNode->key;
    foundNode->value = nextNode->value;
    foundNode->key = nextNode->key;

    // parentNode->left = foundNode->right;


    delete nextNode;
    return true;
}


// PROVIDED FOR YOU
// 1)   creates a vector of keys
// 2)   calls InOrderKeys on the root and adds all keys of the tree into the 
//      vector of Keys.
template<typename KeyType, typename ValueType>
Vector<KeyType> Dictionary<KeyType, ValueType>::Keys() const
{
    Vector<KeyType> keys;
    InOrderKeys(keys, _root);

    return keys;
}

// PROVIDED FOR YOU
template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::IsEmpty() const
{   
    return _root == nullptr;
}

// PROVIDED FOR YOU
template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Contains(const KeyType & key) const
{
    return findKey(key, _root) != nullptr;
}

// PROVIDED FOR YOU
template<typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::At(const KeyType & key) const
{
    Node<KeyType, ValueType> * foundNode = findKey(key, _root);
    if(foundNode == nullptr)
    {
        return ValueType();
    }
    return foundNode->value;
}

// recursively goes through the nodes in order
// every key gets added to the Keys function using: 
// keys.Insert(KEY IN QUESTION)
// remember our InOrder traversal!
template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::InOrderKeys(Vector<KeyType> & keys, Node<KeyType, ValueType> * currentNode) const
{
    if(currentNode == nullptr)
    {
        return;
    }
    InOrderKeys(keys,currentNode->left);
    keys.Insert(currentNode->key);
    InOrderKeys(keys,currentNode->right);
}


// This function returns the node where the "key" can be found.
// returns nullptr if the key cannot be found.
// "currentNode" is the node you are currently looking at.
// if the current node's key is the key in question, return "currentNode"
template<typename KeyType, typename ValueType>
Node<KeyType, ValueType> * Dictionary<KeyType, ValueType>::findKey(const KeyType & key, Node<KeyType, ValueType> * currentNode) const
{
    if(currentNode == nullptr)
    {
        return nullptr;
    }
    if(currentNode->key == key)
    {
        return currentNode;
    }
    if(currentNode->key > key)
    {
        return findKey(key,currentNode->left);
    }
    if(currentNode->key < key)
    {
        return findKey(key,currentNode->right);
    }
    return nullptr;
}

// traverses through the tree to find the parent of "searchedNode"
// "searchedNode" is the node that you are looking to find the parent of
// "currentNode" is the node that you are currently looking at and comparing too.
// this function returns nullptr if a parent isn't able to be found, otherwise
// it returns the "currentNode" when that node is the parent of "searchedNode"
template<typename KeyType, typename ValueType>
Node<KeyType, ValueType> * Dictionary<KeyType, ValueType>::findParent(Node<KeyType, ValueType> *searchedNode, Node<KeyType, ValueType> *currentNode) const
{
    if(currentNode == nullptr)
    {
        return nullptr;
    }
    if(searchedNode == _root)
    {
        return nullptr;
    }
    if(currentNode->left != nullptr)
    {
        if(currentNode->left->key == searchedNode->key)
        {
            return currentNode;
        }
        if(currentNode->key > searchedNode->key)
        {
            return findParent(searchedNode, currentNode->left);
        }
    }
    if(currentNode->right != nullptr)
    {
        if(currentNode->right->key == searchedNode->key)
        {
            return currentNode;
        }
        if(currentNode->key < searchedNode->key)
        {
            return findParent(searchedNode, currentNode->right);
        }
    }
    return nullptr;
}

// removes all nodes in POST ORDER format
// remember your keyword "delete" for deleting a node.
template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::DeletePostOrder(Node<KeyType, ValueType> * startingNode)
{
    if(startingNode == nullptr)
    {
        return;
    }
    DeletePostOrder(startingNode->left);
    DeletePostOrder(startingNode->right);
    delete startingNode;
}

// handles inserting of a node into the tree.
// Remember, nodes to the left are greater, nodes to the right are less than.
// returns true if the insert was successful
// returns false ONLY if we tried to add an item with a duplicate key to our dictionary.
template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::RecursiveInsert(const KeyType & key, const ValueType & value, Node<KeyType, ValueType> * node)
{
    if(key < node->key)
    {
        if(node->left == nullptr)
        {
            node->left = new Node<KeyType, ValueType>();
            node->left->key = key;
            node->left->value = value;
            return true;
        }
        else
        {
            return RecursiveInsert(key,value,node->left);
        }
    }
    else if (key > node->key)
    {
        if(node->right == nullptr)
        {
            node->right = new Node<KeyType, ValueType>();
            node->right->key = key;
            node->right->value = value;
            return true;
        }
        else
        {
            return RecursiveInsert(key,value,node->right);
        }
    }
    return false;
}


#endif