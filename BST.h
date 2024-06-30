#include <iostream>
#include <queue>
#include <algorithm>
#include "stack"

using namespace std;
//inorderTraversal
// — обход узлов в отсортированном порядке,
//preorderTraversal
// — обход узлов в порядке: вершина, левое поддерево, правое поддерево,
//postorderTraversal
// — обход узлов в порядке: левое поддерево, правое поддерево, вершина.

template<typename T>
struct Node {
    T val;
    Node* left;
    Node* right;

    Node(T v) : val(v), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insertHelper(Node<T>* root, T val) {
        if (root == nullptr) {
            return new Node<T>(val);
        }
        if (val < root->val) {
            root->left = insertHelper(root->left, val);
        } else if (val > root->val) {
            root->right = insertHelper(root->right, val);
        }
        return root;
    }

    Node<T>* searchHelper(Node<T>* root, T val) {
        if (root == nullptr || root->val == val) {
            return root;
        }
        if (val < root->val) {
            return searchHelper(root->left, val);
        }
        return searchHelper(root->right, val);
    }
    Node<T>* extractSubtree(Node<T>* root, T val) {
        if (root == nullptr) return nullptr;
        if (root->val == val) {

            Node<T>* newRoot = new Node<T>(root->val);
            newRoot->left = root->left;
            newRoot->right = root->right;

            delete root;
            return newRoot;
        } else {
            Node<T>* leftSubtree = extractSubtree(root->left, val);
            if (leftSubtree != nullptr) return leftSubtree;
            Node<T>* rightSubtree = extractSubtree(root->right, val);
            return rightSubtree;
        }
    }

    Node<T>* deleteHelper(Node<T>* root, T val) {
        if (root == nullptr) return root;
        if (val < root->val) {
            root->left = deleteHelper(root->left, val);
        } else if (val > root->val) {
            root->right = deleteHelper(root->right, val);
        } else {

            if (root->left == nullptr) {
                Node<T>* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                delete root;
                return temp;
            }
            Node<T>* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteHelper(root->right, temp->val);
        }
        return root;
    }

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }


    Node<T>* buildTreeFromInorderPreorder(const std::vector<T>& inorder, int inStart, int inEnd,
                                          const std::vector<T>& preorder, int& preIndex, std::unordered_map<T, int>& inMap) {
        if (inStart > inEnd) {
            return nullptr;
        }

        T currentVal = preorder[preIndex++];
        Node<T>* node = new Node<T>(currentVal);

        if (inStart == inEnd) {
            return node;
        }

        int inIndex = inMap[currentVal];

        node->left = buildTreeFromInorderPreorder(inorder, inStart, inIndex - 1, preorder, preIndex, inMap);
        node->right = buildTreeFromInorderPreorder(inorder, inIndex + 1, inEnd, preorder, preIndex, inMap);

        return node;
    }

public:
    BST(const std::vector<T>& inorder, const std::vector<T>& preorder) {
        if (inorder.size() != preorder.size() || inorder.empty()) {
            throw std::invalid_argument("Invalid input: The inorder and preorder traversals must have the same non-zero length.");
        }

        std::unordered_map<T, int> inMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inMap[inorder[i]] = i;
        }

        int preIndex = 0;
        root = buildTreeFromInorderPreorder(inorder, 0, inorder.size() - 1, preorder, preIndex, inMap);
    }

    BST() : root(nullptr) {}
    BST(const std::vector<T>& vec){
        for(size_t i = 0; i < vec.size(); ++i){
            this->insert(vec[i]);
        }
    }
    BST(std::vector<T>&& vec){
        for(size_t i = 0; i < vec.size(); ++i){
            this->insert(vec[i]);
        }
    }
    BST(const std::initializer_list<T>& list) : root(nullptr) {
        for(const auto& item : list) {
            insert(item);
        }
    }
    BST(std::initializer_list<T>&& list) : root(nullptr) {
        for(const auto& item : list) {
            insert(item);
        }
    }


    T getRoot() {
        return root->val;
    }

    std::vector<T> bfs() {
        std::vector<T> result;
        if (root == nullptr) return result;

        std::queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();
            result.push_back(current->val);

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }

        return result;
    }

    void insert(T val) {
        root = insertHelper(root, val);
    }

    void delete_element(T val) {
        root = deleteHelper(root, val);
    }

    Node<T>* search(T val) {
        return searchHelper(root, val);
    }

    std::vector<T> inorderTraversal() {
        std::vector<T> result;
        if (root == nullptr) return result;

        std::stack<Node<T>*> stack;
        Node<T>* current = root;

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            result.push_back(current->val);
            current = current->right;
        }

        return result;
    }

    template<typename U, typename Func>
    BST<U> map(Func func) {
        BST<U> newTree;
        std::vector<U> values = inorderTraversal();
        for (U val : values) {
            newTree.insert(func(val));
        }
        return newTree;
    }


    BST<T> where(bool (*predicate)(T)) {
        BST<T> newTree;
        std::vector<T> values = inorderTraversal();
        for (T val : values) {
            if (predicate(val)) {
                newTree.insert(val);
            }
        }
        return newTree;
    }
    BST<T> extractSubtree(const T& val) {
        BST<T> newTree;
        Node<T>* subtreeRoot = extractSubtree(root, val);
        if (subtreeRoot != nullptr) {
            newTree.root = subtreeRoot;
        }
        return newTree;
    }
    bool operator == (BST<T>& other) {
        std::vector<T> thisValues = inorderTraversal();
        std::vector<T> otherValues = other.inorderTraversal();
        return thisValues == otherValues;
    }
    /// ОБХОДЫ
    /// КЛП ОБХОД
    std::vector<T> preorderTraversal() {
        std::vector<T> result;
        preorderTraversalHelper(root, result);
        return result;
    }

    void preorderTraversalHelper(Node<T>* root, std::vector<T>& result) {
        if (root == nullptr) return;
        result.push_back(root->val);
        preorderTraversalHelper(root->left, result);
        preorderTraversalHelper(root->right, result);
    }
    /// КПЛ ОБХОД
    std::vector<T> preRightLeftTraversal() {
        std::vector<T> result;
        preRightLeftTraversalHelper(root, result);
        return result;
    }

    void preRightLeftTraversalHelper(Node<T>* root, std::vector<T>& result) {
        if (root == nullptr) return;
        result.push_back(root->val);
        preRightLeftTraversalHelper(root->right, result);
        preRightLeftTraversalHelper(root->left, result);
    }
    /// ЛПК ОБХОД
    std::vector<T> postorderTraversal() {
        std::vector<T> result;
        postorderTraversalHelper(root, result);
        return result;
    }

    void postorderTraversalHelper(Node<T>* root, std::vector<T>& result) {
        if (root == nullptr) return;
        postorderTraversalHelper(root->left, result);
        postorderTraversalHelper(root->right, result);
        result.push_back(root->val);
    }
    /// ЛКП ОБХОД
    std::vector<T> postLeftRightTraversal() {
        std::vector<T> result;
        postLeftRightTraversalHelper(root, result);
        return result;
    }

    void postLeftRightTraversalHelper(Node<T>* root, std::vector<T>& result) {
        if (root == nullptr) return;
        postLeftRightTraversalHelper(root->left, result);
        postLeftRightTraversalHelper(root->right, result);
        result.push_back(root->val);
    }
    /// ПЛК ОБХОД
    std::vector<T> inorderTraversal1() {
        std::vector<T> result;
        inorderTraversalHelper(root, result);
        return result;
    }

    void inorderTraversalHelper(Node<T>* root, std::vector<T>& result) {
        if (root == nullptr) return;
        inorderTraversalHelper(root->left, result);
        result.push_back(root->val);
        inorderTraversalHelper(root->right, result);
    }

};
// 5 10 15 16 22 30
// 15 10 5 22 16 30
