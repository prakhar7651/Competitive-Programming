#include <cstddef>
#include <iostream>

template<class T>
class AVLNode{
    
    public:

        AVLNode(const T& value) : data(value) , left(NULL) , right(NULL) , height(1) {}
        ~AVLNode() {}

        T data;
        int height;

        AVLNode* parent;
        AVLNode* left;
        AVLNode* right;

        int getHeight();
        int getBF();
};

template<class T>
int AVLNode<T>::getHeight(){
    if(this == NULL)
        return 0;
    return this -> height;
}

template<class T>
int AVLNode<T>::getBF(){
    if(this == NULL)
        return 0;
    return this -> left -> getHeight() - this -> right -> getHeight();
}

template<class T>
class AVLTree{

    public:

        AVLNode<T>* root;
        int size;

        AVLTree(bool (*_cmp)(T , T)) : cmp(_cmp) , root(NULL) , size(0){}
        ~AVLTree() {}
        
        AVLNode<T>* leftRotate(AVLNode<T>* y);
        AVLNode<T>* rightRotate(AVLNode<T>* x);

        AVLNode<T>* balanceAfterInsert(AVLNode<T>* node , T key);
        AVLNode<T>* balanceAfterDelete(AVLNode<T>* node);
        
        AVLNode<T>* findMin(AVLNode<T>* node);
        AVLNode<T>* findMax(AVLNode<T>* node);

        AVLNode<T>* successor(AVLNode<T>* node);
        AVLNode<T>* predecessor (AVLNode<T>* node);

        void insert(T key);
        void remove(T key);
        AVLNode<T>* search(T key);

    private:
        bool (*cmp)(T , T); // returns true if arg1 < arg2
        AVLNode<T>* _insert(AVLNode<T>* node , T key);
        AVLNode<T>* _remove(AVLNode<T>* node , T key);
        AVLNode<T>* _search(AVLNode<T>* node , T key);

};

template<class T>
void preorder(AVLNode<T>* node);

template<class T>
void inorder(AVLNode<T>* node);

template<class T>
AVLNode<T>* AVLTree<T>::_insert(AVLNode<T>* node , T key){
    if(node == NULL){
        size++;
        return new AVLNode<T>(key);
    }
    
    if(cmp(key , node -> data))
        if(node -> left)
            node -> left = _insert(node -> left , key);
        else{
            node -> left = new AVLNode<T>(key);
            node -> left -> parent = node;            
        }
    else if(cmp(node -> data , key))
            if(node -> right)
                node -> right = _insert(node -> right , key);
            else{
                node -> right = new AVLNode<T>(key);
                node -> right -> parent = node;
            }

    return balanceAfterInsert(node , key);
}

template<class T>
AVLNode<T>* AVLTree<T>::_remove(AVLNode<T>* node , T key){

    if(node == NULL)
        return node;
    
    else if(node -> data > key)
        node -> left = _remove(node -> left , key);
    else if(node -> data < key)
        node -> right = _remove(node -> right , key);
    else if(node -> left && node -> right){
        AVLNode<T>* temp = findMin(node -> right);
        node -> data = temp -> data;
        node -> right = _remove(node -> right , temp -> data);
    }
    else{
        
        AVLNode<T>* temp = node;

        if(node -> left == NULL && node -> right)
            node = node -> right;
        else if(node -> right == NULL && node -> left)
            node = node -> left;

        if(temp != node){
            if(temp -> parent == NULL)
                node -> parent = NULL;
            else{
                if(temp -> parent -> left == temp)
                    temp -> parent -> left = node;
                else
                    temp -> parent -> right = node;
                node -> parent = temp -> parent;
            }
        }
        else{
            if(temp -> parent != NULL)
                if(temp -> parent -> left == temp)
                    temp -> parent -> left = NULL;
                else
                    temp -> parent -> right = NULL;
            node = NULL;
        }
        delete temp;
    }

    if(node == NULL)
        return node;

    return balanceAfterDelete(node);
}

template<class T>
AVLNode<T>* AVLTree<T>::_search(AVLNode<T>* node , T key){
    if(node == NULL)
        return node;
    if(node->data == key)
        return node;
    if(node->data > key)
        return _search(node->left , key);
    return _search(node->right , key);
}

template<class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* root){

    AVLNode<T>* new_root = root -> left;
    root -> left = new_root -> right;
    new_root ->  right = root;

    if(root -> left)
        root -> left -> parent = root;
    
    if(root -> parent == NULL)
        new_root -> parent = NULL;
    else{
        if(root -> parent -> left == root)
            root -> parent -> left = new_root;
        else
            root -> parent -> right = new_root;
        new_root -> parent = root -> parent;
    }

    root -> parent = new_root;

    root -> height = std::max((root -> left)->getHeight() , (root -> right)->getHeight()) + 1;
    new_root -> height = std::max((new_root -> left)->getHeight() , (new_root -> right)->getHeight()) + 1;

    return new_root;
}

template<class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* root){

    AVLNode<T>* new_root = root -> right;
    root -> right = new_root -> left;
    new_root -> left = root;

    if(root -> right)
        root -> right -> parent = root;

    if(root -> parent == NULL){
        new_root -> parent = NULL;
    }
    else{
        if(root -> parent -> left == root)
            root -> parent -> left = new_root;
        else
            root -> parent -> right = new_root;
        new_root -> parent = root -> parent;
    }

    root -> parent = new_root;
    

    root -> height = std::max(root -> left -> getHeight() , root -> right -> getHeight()) + 1;
    new_root -> height = std::max(new_root -> left -> getHeight() , new_root -> right -> getHeight()) + 1;

    return new_root;
}

template<class T>
AVLNode<T>* AVLTree<T>::balanceAfterInsert(AVLNode<T>* node , T key){

    node -> height = 1 + std::max(node -> left -> getHeight() , node -> right -> getHeight());
    int bf = node -> getBF();

    // Left Left Case
    if(bf > 1 && cmp(key , node -> left -> data))
        return rightRotate(node);

    // Left Right Case
    if(bf > 1 && cmp(node -> left -> data , key)){
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }

    // Right Left Case
    if(bf < -1 && cmp(key , node -> right -> data)){
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }

    // Right Right Case
    if(bf < -1 && cmp(node -> right -> data , key))
        return leftRotate(node);

    return node;

}

template<class T>
AVLNode<T>* AVLTree<T>::balanceAfterDelete(AVLNode<T>* node){

    node -> height = 1 + std::max(node -> left -> getHeight() , node -> right -> getHeight());
    int bf = node -> getBF();

    if(abs(bf) <= 1)
        return node;

    AVLNode<T>* y;
    if(node -> left -> getHeight() > node -> right -> getHeight())
        y = node -> left;
    else
        y = node -> right;

    AVLNode<T>* z;
    if(y -> left -> getHeight() > y -> right -> getHeight()) 
        z = y -> left;
    else
        z = y -> right;

    if(y == node -> left)
        if(z == y -> left)
            return rightRotate(node);
        else{
            node -> left = leftRotate(node -> left);
            return rightRotate(node);
        }
    else
        if(z == y -> left){
            node -> right = rightRotate(node -> right);
            return leftRotate(node);
        }
        else
            return leftRotate(node);
    return node;
}

template<class T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node){
    if(node == NULL)
        return node;
    if(node -> left == NULL)
        return node;
    return findMin(node -> left);
}

template<class T>
AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* node){
    if(node == NULL)
        return node;
    if(node -> right == NULL)
        return node;
    return findMax(node -> right);
}

template<class T>
AVLNode<T>* AVLTree<T>::successor(AVLNode<T>* node){
    if(node -> right)
        return findMin(node -> right);
    while(node -> parent){
        if(node -> parent -> left == node)
            return node -> parent;
        node = node -> parent;
    }
    return NULL;
}

template<class T>
AVLNode<T>* AVLTree<T>::predecessor(AVLNode<T>* node){
    if(node -> left)
        return findMax(node -> left);
    while(node -> parent){
        if(node -> parent -> right == node)
            return node -> parent;
        node = node -> parent;
    }
    return NULL;
}

template<class T>
void AVLTree<T>::insert(T key){
    root =  _insert(root , key);
    return;
}

template<class T>
void AVLTree<T>::remove(T key){
    root = _remove(root , key);
    return;
}

template<class T>
AVLNode<T>* AVLTree<T>::search(T key){
    return _search(root , key);
}

template<class T>
void  inorder(AVLNode<T>* node){
    if(node == NULL)
        return;
    inorder(node -> left);
    std::cout << node -> data << "\n";
    inorder(node -> right);
    return;
}

template<class T>
void preorder(AVLNode<T>* node){
    if(node == NULL)
        return;
    std::cout << node -> data << "\n";
    preorder(node -> left);
    preorder(node -> right);
    return;
}