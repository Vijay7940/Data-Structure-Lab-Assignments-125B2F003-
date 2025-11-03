#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int count; // handling duplicate entries
};

class BST {
private:
    Node* root;

    // Method to create a new node
    Node* createNode(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->count = 1;
        return newNode;
    }

    // Recursive method to insert a node
    Node* insertNode(Node* node, int value) {
        if (node == NULL) {
            return createNode(value);
        }
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value);
        } else {
            // increase count if duplicate value found 
            node->count++;
            cout << "Duplicate entry. Count increased to " << node->count << endl;
        }
        return node;
    }

    // Method to find node min value (used in deletion)
    Node* findMin(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // Recursive method to delete a node
    Node* deleteNode(Node* node, int value) {
        if (node == NULL) {
            return NULL;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node found
            if (node->count > 1) {
                node->count--;
                cout << "Duplicate count decreased to " << node->count << endl;
                return node;
            }

            // Case 1: If No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            // Case 2: If One child (right)
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Case 3: If One child (left)
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 4: If Two children replace with inorder successor
            else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->count = temp->count; // Copy duplicate count
                node->right = deleteNode(node->right, temp->data);
            }
        }
        return node;
    }

    // Recursive method to search a node
    bool searchNode(Node* node, int value) {
        if (node == NULL) {
            return false;
        }
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }

    // Recursive method for inorder traversal (Left - Root - Right)
    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->data;
            if (node->count > 1) {
                cout << "(" << node->count << ")";
            }
            cout << " ";
            inorder(node->right);
        }
    }

    // Recursive method for preorder traversal (Root - Left - Right)
    void preorder(Node* node) {
        if (node != NULL) {
            cout << node->data;
            if (node->count > 1) {
                cout << "(" << node->count << ")";
            }
            cout << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Recursive method for postorder traversal (Left - Right - Root)
    void postorder(Node* node) {
        if (node != NULL) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data;
            if (node->count > 1) {
                cout << "(" << node->count << ")";
            }
            cout << " ";
        }
    }

    // Recursive method to calculate depth (height) of the tree
    int depth(Node* node) {
        if (node == NULL) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
    }

    // Recursive method to create mirror image
    void mirror(Node* node) {
        if (node == NULL) return;
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        mirror(node->left);
        mirror(node->right);
    }

    // Recursive method to copy the tree
    Node* copyTree(Node* node) {
        if (node == NULL) return NULL;
        Node* newNode = createNode(node->data);
        newNode->count = node->count;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    // Recursive method to display parent nodes with children
    void displayParentNodes(Node* node) {
        if (node == NULL || (node->left == NULL && node->right == NULL)) return;

        cout << "Parent: " << node->data << " -> Children: ";
        if (node->left != NULL) cout << "Left=" << node->left->data << " ";
        if (node->right != NULL) cout << "Right=" << node->right->data;
        cout << endl;

        displayParentNodes(node->left);
        displayParentNodes(node->right);
    }

    // Recursive method to display only leaf nodes
    void displayLeafNodes(Node* node) {
        if (node == NULL) return;
        if (node->left == NULL && node->right == NULL) {
            cout << node->data << " ";
            return;
        }
        displayLeafNodes(node->left);
        displayLeafNodes(node->right);
    }

    // Method for level-order (breadth-first) traversal
    void levelOrder(Node* node) {
        if (node == NULL) return;
        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                cout << current->data;
                if (current->count > 1) cout << "(" << current->count << ")";
                cout << " ";

                if (current->left != NULL) q.push(current->left);
                if (current->right != NULL) q.push(current->right);
            }
            cout << endl;
        }
    }

    // Recursive method to delete all nodes (used in destructor)
    void destroyTree(Node* node) {
        if (node != NULL) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BST() {
        root = NULL;
    }

    // Destructor to ensure no memory leak
    ~BST() {
        destroyTree(root);
    }

    // method to insert a value
    void insert(int value) {
        root = insertNode(root, value);
    }

    // method to remove a value
    void remove(int value) {
        root = deleteNode(root, value);
    }

    // method to search for a value
    bool search(int value) {
        return searchNode(root, value);
    }

    // methods for traversals
    void displayInorder() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }

    // method to get tree depth
    int getDepth() {
        return depth(root);
    }

    // method to create mirror image
    void createMirror() {
        mirror(root);
    }

    // method to create a deep copy of the tree
    BST* createCopy() {
        BST* newTree = new BST();
        newTree->root = copyTree(root);
        return newTree;
    }

    // method to display parent nodes with children
    void showParentNodes() {
        cout << "Parent nodes with children:" << endl;
        displayParentNodes(root);
    }

    // method to display leaf nodes
    void showLeafNodes() {
        cout << "Leaf nodes: ";
        displayLeafNodes(root);
        cout << endl;
    }

    // method for level-wise display
    void showLevelWise() {
        levelOrder(root);
    }
};

// -------------------- MAIN METHOD --------------------
int main() {
    BST tree;
    BST* copiedTree = NULL;
    int choice, value;
    
    cout << "\n=== Binary Search Tree Menu ===\n";
    cout << "1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Preorder Traversal\n";
    cout << "6. Postorder Traversal\n7. Display Depth\n8. Display Parent Nodes\n9. Display Leaf Nodes\n";
    cout << "10. Level-wise Display\n11. Create Mirror\n12. Create Copy\n13. Exit\n";

    while (true) {
        
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.remove(value);
            cout <<"Successfully Deleted" << endl;
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (tree.search(value) ? "Found" : "Not Found") << endl;
            break;
        case 4:
            tree.displayInorder();
            break;
        case 5:
            tree.displayPreorder();
            break;
        case 6:
            tree.displayPostorder();
            break;
        case 7:
            cout << "Depth of tree: " << tree.getDepth() << endl;
            break;
        case 8:
            tree.showParentNodes();
            break;
        case 9:
            tree.showLeafNodes();
            break;
        case 10:
            tree.showLevelWise();
            break;
        case 11:
            tree.createMirror();
            cout << "Mirror created successfully.\n";
            break;
        case 12:
            if (copiedTree != NULL) delete copiedTree;
            copiedTree = tree.createCopy();
            cout << "Tree copied successfully. Copied tree inorder: ";
            copiedTree->displayInorder();
            break;
        case 13:
            if (copiedTree != NULL) delete copiedTree;
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}


