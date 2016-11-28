#ifndef AVLTREE
#define AVLTREE
//template<class T>
#include "exception"
template<class T>
class AvlTree
{
private:
    class AvlNode
    {
    public:
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const T & theElement, AvlNode *lt, AvlNode *rt, int h = 0) : element(theElement), left(lt), right(rt), height(h) {}
    };
    AvlNode *root;
public:
    //Empty AVL tree has a null root
    AvlTree() : root(nullptr){}
    AvlTree( const AvlTree & rhs) : root(nullptr)
    {
        *this = rhs;
    }
    //Destructor
    ~AvlTree()
    {
        makeEmpty();
    }
    const T & findMin() const
    {
        if(isEmpty())
            throw "Stack underflow";
        return findMin(root);
    }
    const T & findMax() const
    {
        if(isEmpty())
            throw "Stack underflow";
        return findMax(root);
    }
    //If there is no root, Tree is empty
    bool isEmpty() const
    {
        return root == nullptr;
    }
    //Frees node memory
    void makeEmpty()
    {
        makeEmpty(root);
    }
    //Inserts object
    void insert(const T & x)
    {
        insert(x, root);
    }
    //Returns true if object is in tree
    bool inTree(T object)
    {
        return inTree(object, root);
    }
    //Returns reference to object in tree
    T& get(T object)
    {
        return get(object, root);
    }

private:
    //Returns height of tree
    int height(AvlNode *t) const
    {
        return t==nullptr ? -1 : t->height;
    }
    //Picks maximum of two integers, used for comparing tree heights
    int max(int lhs, int rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }
    //Insert uses rotates to ensure tree is balanced
    void insert(const T & x, AvlNode * & t)
    {
        if (t == nullptr)
            t = new AvlNode(x, nullptr, nullptr);
        else if (x < t->element)
        {
            insert(x, t->left);
            if (height(t->left)-height(t->right)==2)
            {
                if(x < t->left->element)
                    //Case 1
                    rotateWithLeftChild(t);
                else
                    //Case 3
                    doubleWithLeftChild(t);
            }
        }
        else if (t->element < x)
        {
            insert(x, t->right);
            if (height(t->right)-height(t->left) == 2)
            {
                if(x > t->right->element)
                    //Case 4
                    rotateWithRightChild(t);
                else
                    //Case 2
                    doubleWithRightChild(t);
            }

        }
        t->height = max(height(t->left),height(t->right))+1;
    }
    void rotateWithLeftChild(AvlNode * & k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right))+1;
        k1->height = max(height(k1->left), height(k1->right))+1;
        k2 = k1;
    }
    void rotateWithRightChild(AvlNode * & k2)
    {
        AvlNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right))+1;
        k1->height = max(height(k1->left), height(k1->right))+1;
        k2 = k1;
    }
    void doubleWithLeftChild(AvlNode * & k1)
    {
        rotateWithRightChild(k1->left);
        rotateWithLeftChild(k1);
    }
    void doubleWithRightChild(AvlNode * & k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    //Goes through left nodes to find min
    T& findMin(AvlNode * node) const
    {
        if(node->left == nullptr)
            return node->element;
        else

            return findMin(node->left);
    }
    //Goes through right nodes to find max
    T& findMax(AvlNode * node) const
    {
        if(node->right == nullptr)
            return node->element;
        else
            return findMax(node->right);
    }
    bool inTree(T object, AvlNode * node)
    {
        if (node == nullptr)
            return false;
        else if (node->element == object)
            return true;
        else if (object < node->element)
            return inTree(object, node->left);
        else
            return inTree(object, node->right);
    }
    T& get(T object, AvlNode * node)
    {
        if (node == nullptr)
            throw "This object is not in this tree.";
        else if (node->element == object)
            return node->element;
        else if (object < node->element)
            return get(object, node->left);
        else
            return get(object, node->right);
    }
    void makeEmpty(AvlNode * & node)
    {
        if (node != nullptr)
        {
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
            node = nullptr;

        }
    }
 };

#endif // AVLTREE
