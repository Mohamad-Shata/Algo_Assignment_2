#include <iostream>
using namespace std;

// Define colors for the Red-Black Tree
enum Color { RED, BLACK };

// Define the structure for the Red-Black Tree Node
struct Node {
    int data;
    Node *left, *right, *parent;
    Color color;

    Node(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    Node *root, *TNULL;

    // Rotate left
    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Rotate right
    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Fix the Red-Black Tree properties after insertion
void fixInsert(Node *k) {
        Node *u; // Uncle node
        while (k->parent != nullptr && k->parent->color == RED) { // Check if parent exists and is RED
            if (k->parent == k->parent->parent->right) { // Parent is a right child
                u = k->parent->parent->left; // Uncle node
                if (u != nullptr && u->color == RED) { // Case 1: Uncle is RED
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent; // Move up the tree
                } else {
                    if (k == k->parent->left) { // Case 2: k is a left child
                        k = k->parent;
                        rightRotate(k); // Rotate parent
                    }
                    // Case 3: k is a right child
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else { // Parent is a left child
                u = k->parent->parent->right; // Uncle node
                if (u != nullptr && u->color == RED) { // Case 1: Uncle is RED
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent; // Move up the tree
                } else {
                    if (k == k->parent->right) { // Case 2: k is a right child
                        k = k->parent;
                        leftRotate(k); // Rotate parent
                    }
                    // Case 3: k is a left child
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break; // Exit if k reaches the root
        }
        root->color = BLACK; // Ensure root is always BLACK
    }


    // Insert a node
    void insert(int key) {
        Node *node = new Node(key);
        Node *y = nullptr;
        Node *x = root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        fixInsert(node);
    }

    // Inorder fixup (Helper function for delete)
    void fixDelete(Node *x) {
        Node *s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if ((s->left == TNULL || s->left->color == BLACK) &&
                    (s->right == TNULL || s->right->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right == TNULL || s->right->color == BLACK) {
                        if (s->left != TNULL) s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->right != TNULL) s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if ((s->right == TNULL || s->right->color == BLACK) &&
                    (s->left == TNULL || s->left->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left == TNULL || s->left->color == BLACK) {
                        if (s->right != TNULL) s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->left != TNULL) s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }



    // Delete a node
    void deleteNode(Node *z) {
        Node *y = z;
        Node *x;
        Color yOriginalColor = y->color;

        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

    // Transplant function
    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // Find the minimum node
    Node* minimum(Node *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }


    // Public insert function
    void insertValue(int key) {
        insert(key);
    }

    // Public delete function
void deleteValue(int key) {
    Node *z = search(root, key);
    if (z == TNULL) {
        cout << "Key " << key << " not found in the tree." << endl;
        return;
    }
    deleteNode(z);
}


    // Search a node
    Node* search(Node *node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Print the tree (In-order traversal)
    void inorderHelper(Node *node) {
        if (node != TNULL) {
            inorderHelper(node->left);
            cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

    void inorder() {
        inorderHelper(root);
    }
};

int main() {
    RedBlackTree tree;
    tree.insertValue(10);
    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(15);

    cout << "Inorder traversal of the Red-Black Tree: ";
    tree.inorder();

    cout << "\nDeleting node 20\n";
    tree.deleteValue(20);
    tree.inorder();

    return 0;
}
