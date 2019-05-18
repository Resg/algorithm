#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cassert>

template <class T>
struct IsLess {
public:
    bool operator()(const T &one, const T &other) {
        return one < other;
    }
};


template <class T, class compr = IsLess<T>>
class Nod
{
public:
    Nod *parent;
    Nod *right;
    Nod *left;
    T key;
    bool been;
    Nod(): key(NULL), parent(nullptr), right(nullptr), left(nullptr), been(false) {}
    Nod(const T &value): parent(nullptr), right(nullptr), left(nullptr), key(value), been(false) {}
};

template <class T, class compr = IsLess<T>>
class BinTree
{
private:
    Nod<T>* root;
    size_t size;
public:
    BinTree(): root(nullptr), size(0) {}

    BinTree(const T &value): size(1) {
        root = new Nod<T>(value);
    }
    ~BinTree() {
        Nod<T> *ptr = root;
        while (root) {
            if (ptr->left) {
                if (!ptr->left->left && !ptr->left->right) {
                    delete ptr->left;
                    ptr->left = nullptr;
                }
                else {
                    ptr = ptr->left;
                }
            }
            else if(ptr->right) {
                if (!ptr->right->left && !ptr->right->right) {
                    delete ptr->right;
                    ptr->right = nullptr;
                }
                else {
                    ptr = ptr->right;
                }
            }
            else {
                if (ptr == root) {
                    delete ptr;
                    root = nullptr;
                }
                ptr = ptr->parent;
            }


        }
    }

    void add(const T &value) {
        if (!root) {
            root = new Nod<T>(value);
            return;
        }
        Nod<T> *ptr = root;
        while (true) {
            if (ptr->key<=value) {
                if (ptr->right) {
                    ptr = ptr->right;
                }
                else {
                    ptr->right = new Nod<T>(value);
                    ptr->right->parent = ptr;
                    size++;
                    return;
                }
            }
            else {
                if (ptr->left) {
                    ptr = ptr->left;
                }
                else {
                    ptr->left = new Nod<T>(value);
                    ptr->left->parent = ptr;
                    size++;
                    return;
                }
            }
        }
    }
    std::vector<T> preOrder() {
        std::vector<T> result;
        std::unordered_set<Nod<T>*> been;
        Nod<T> *ptr = root;
        while (result.size() < size+1) {
            if (been.find(ptr) == been.end()) {
                result.push_back(ptr->key);
                been.insert(ptr);
            }
            if (ptr->left) {
                if (been.find(ptr->left) == been.end()) {
                    ptr = ptr->left;
                    continue;
                }

            }
            if (ptr->right) {
                if (been.find(ptr->right) == been.end()) {
                    ptr = ptr->right;
                    continue;
                }
            }
            if (!ptr->left && !ptr->right) {
                ptr = ptr->parent;
                continue;
            }
            ptr = ptr->parent;
        }
        return result;
    }
};

int main()
{
    size_t N = 0;
    std::cin >> N;
    int value = 0;
    BinTree<int> tree;
    for (size_t i = 0; i < N; i++) {
        std::cin >> value;
        tree.add(value);
    }
    std::vector<int> result = tree.preOrder();
    for (auto i : result)
        std::cout << i << ' ';
    return 0;
}
