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

    Node() = default;

    ~Node()
    {
        left = nullptr;
        right = nullptr;
    }

    Node(const Node<KeyType, ValueType> & other)
    {
        key = other.key;
        value = other.value;
        right = other.right;
        left = other.left;
    }

    Node& operator=(const Node<KeyType, ValueType> & other)
    {
        key = other.key;
        value = other.value;
        right = other.right;
        left = other.left;
        return *this;
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
    
    Node<KeyType, ValueType> * findKey(const KeyType & key, Node<KeyType, ValueType> * startingNode) const;
    Node<KeyType, ValueType> * findParent(Node<KeyType, ValueType> *searchedNode, Node<KeyType, ValueType> *currentNode) const;

    void DeletePostOrder(Node<KeyType, ValueType> * startingNode);
    bool RecursiveInsert(const KeyType & key, const ValueType & value, Node<KeyType, ValueType> * node);
    void InOrderKeys(Vector<KeyType> & keys, Node<KeyType, ValueType> *currentNode) const;

public:

    Dictionary();
    ~Dictionary();

    // inserts the key/value pair into the tree.
    // returns true if successful, false if NOT successful.
    // THIS TREE CONTAINS ONLY UNIQUE IDS SO YOU CAN ONLY INSERT 
    // VALUES THAT HAVE NO KEYS CURRENTLY IN THE LIST
    bool Insert(const KeyType & key, const ValueType & value);


    // removes the key in question
    // returns false if the key did not exist
    // returns true if it did
    bool Remove(const KeyType & key);

    // creates a vector of keys.  This alows a loopable 
    // pattern through a normal mechanism of: 
    // for(int i = 0; i < keys.Size(); i ++)
    // { 
    //      ValueType someValueFromKey = Dictionary.At(keys.At(i));
    // }
    Vector<KeyType> Keys() const;

    // returns if the dictionary is empty
    bool IsEmpty() const;

    // Checks if a key exists in the tree
    bool Contains(const KeyType & key) const;

    // finds the value with the assosiated key. 
    ValueType At(const KeyType & key) const;
};


template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary()
{

}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary()
{
    DeletePostOrder(_root);
}


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
        if(foundNode == _root)
        {
            delete foundNode;
            _root = nullptr;
            return true;
        }

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

    // Case 2: 1 Child right
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
    // Case 2: 1 Child left
    if(foundNode->left != nullptr && foundNode->right == nullptr)
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
    Node<KeyType, ValueType> * next = foundNode->right;
    if(next->left == nullptr && next->right == nullptr)
    {
        foundNode->value = next->value;
        foundNode->key = next->key;
        delete next;
        return true;
    }
    if(next->left != nullptr)
    {
        Node<KeyType, ValueType> *leftCurrent = foundNode->right;
        Node<KeyType, ValueType> *leftCurrentN = leftCurrent->left;
        while(leftCurrentN->left != nullptr)
        {
            leftCurrent = leftCurrentN;
            leftCurrentN = leftCurrentN->left;
        }
        foundNode->value = leftCurrentN->value;
        foundNode->key = leftCurrentN->key;
        delete leftCurrentN;
        return true;
    }
    else
    {
        Node<KeyType, ValueType> *temp = foundNode->right;
        foundNode->value = temp->value;
        foundNode->key = temp->key;
        foundNode->right = temp->right;
        delete temp;
        return true;
    }
    
    return false;
}

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

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::IsEmpty() const
{   
    return _root == nullptr;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Contains(const KeyType & key) const
{
    return findKey(key, _root) != nullptr;
}

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

template<typename KeyType, typename ValueType>
Node<KeyType, ValueType> * Dictionary<KeyType, ValueType>::findKey(const KeyType & key, Node<KeyType, ValueType> * startingNode) const
{
    // got a null node somehow
    if(startingNode == nullptr)
    {
        return nullptr;
    }

    if(startingNode->key == key)
    {
        return startingNode;
    }

    // left and right nodes are null
    if(startingNode->left == nullptr && startingNode->right == nullptr)
    {
        return nullptr;
    }

    if(startingNode-> key > key)
    {
        if(startingNode->left != nullptr)
        {
            return findKey(key, startingNode->left);
        }
    }

    if(startingNode->key < key)
    {
        if(startingNode->right != nullptr)
        {
            return findKey(key, startingNode->right);
        }
    }

    // catch point where if we've gotten here something is wrong.
    return nullptr;
}
template<typename KeyType, typename ValueType>
Node<KeyType, ValueType> * Dictionary<KeyType, ValueType>::findParent(Node<KeyType, ValueType> *searchedNode, Node<KeyType, ValueType> *currentNode) const
{
    if(searchedNode == _root)
    {
        return nullptr;
    }

    if(currentNode == nullptr)
    {
        return nullptr;
    }

    if(currentNode->left != nullptr)
    {
        if(currentNode->left == searchedNode)
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
        if(currentNode->right == searchedNode)
        {
            return currentNode;
        }
        if(currentNode->key < searchedNode->key)
        {
            return findParent(searchedNode, currentNode->right);
        }
    }

    // somehow we got here and we shouldn't have.
    return nullptr;
}


template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::DeletePostOrder(Node<KeyType, ValueType> * startingNode)
{
    if(startingNode == nullptr)
    {
        return;
    }  

    DeletePostOrder(startingNode->left);
    startingNode->left = nullptr;
    DeletePostOrder(startingNode->right);
    startingNode->right = nullptr;
    delete startingNode;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::RecursiveInsert(const KeyType & key, const ValueType & value, Node<KeyType, ValueType> * node)
{
    // null check hit - something wrong happened
    if(node == nullptr)
    {
        return false;
    }
    // immediately exit.
    if(key == node->key)
    {
        return false;
    }
    
    // check left
    if(key < node->key)
    {
        if(node->left == nullptr)
        {
            Node<KeyType, ValueType> * newNode = new Node<KeyType, ValueType>();
            newNode->key = key;
            newNode->value = value;
            node->left = newNode;
            return true;
        }
        return RecursiveInsert(key, value, node->left);
    }

    // check right
    if(key > node->key)
    {
        if(node->right == nullptr)
        {
            Node<KeyType, ValueType> * newNode = new Node<KeyType, ValueType>();
            newNode->key = key;
            newNode->value = value;
            node->right = newNode;
            return true;
        }
        return RecursiveInsert(key, value, node->right);    
    }


    // shouldn't ever get here
    return false;
}


template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::InOrderKeys(Vector<KeyType> & keys, Node<KeyType, ValueType> * currentNode) const
{
    if(currentNode == nullptr)
    {
        return;
    }  

    InOrderKeys(keys, currentNode->left);

    keys.Insert(currentNode->key);

    InOrderKeys(keys, currentNode->right);
    
}

#endif