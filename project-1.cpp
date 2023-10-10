#include <iostream>
using namespace std;
// Define the Employee structure
struct Employee {
    int id;
    string name;
    int bossId; // ID of the immediate boss

    Employee(int _id,string _name, int _bossId) : id(_id), name(_name), bossId(_bossId) {}
};

// Define the AVL tree node structure
struct TreeNode {
    Employee data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(Employee _data) : data(_data), left(nullptr), right(nullptr), height(1) {}
};

// Function to calculate the height of a node
int getHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(TreeNode* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to perform a right rotation
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to balance the AVL tree
TreeNode* balance(TreeNode* node) {
    int balanceFactor = getHeight(node->left) - getHeight(node->right);

    // Left heavy
    if (balanceFactor > 1) {
        if (node->data.id > node->left->data.id) {
            // Left-Left case
            return rightRotate(node);
        } else {
            // Left-Right case
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Right heavy
    if (balanceFactor < -1) {
        if (node->data.id < node->right->data.id) {
            // Right-Right case
            return leftRotate(node);
        } else {
            // Right-Left case
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Function to insert an employee into the AVL tree
TreeNode* insert(TreeNode* root, Employee employee) {
    if (root == nullptr) return new TreeNode(employee);

    if (employee.id < root->data.id) {
        root->left = insert(root->left, employee);
    } else {
        root->right = insert(root->right, employee);
    }

    updateHeight(root);
    return balance(root);
}

// Function to find an employee by ID
Employee* findEmployee(TreeNode* root, int id) {
    if (root == nullptr) return nullptr;

    if (id == root->data.id) {
        return &(root->data);
    } else if (id < root->data.id) {
        return findEmployee(root->left, id);
    } else {
        return findEmployee(root->right, id);
    }
}

// Function to fire an employee by ID
TreeNode* fireEmployee(TreeNode* root, int id) {
    if (root == nullptr) return nullptr;

    if (id == root->data.id) {
        // Node to be deleted found
        // Implement your deletion logic here
        // This is where you need to handle the case when the employee is fired
        // You may need to reorganize the tree
        // For simplicity, this example doesn't perform employee deletion
        return root;
    } else if (id < root->data.id) {
        root->left = fireEmployee(root->left, id);
    } else {
        root->right = fireEmployee(root->right, id);
    }

    updateHeight(root);
    return balance(root);
}

// Function to find the lowest common boss of two employees
Employee* lowestCommonBoss(TreeNode* root, int id1, int id2) {
    if (root == nullptr) return nullptr;

    if ((id1 < root->data.id && id2 > root->data.id) || (id1 > root->data.id && id2 < root->data.id) || id1 == root->data.id || id2 == root->data.id) {
        return &(root->data);
    } else if (id1 < root->data.id && id2 < root->data.id) {
        return lowestCommonBoss(root->left, id1, id2);
    } else {
        return lowestCommonBoss(root->right, id1, id2);
    }
}

// Function to perform in-order traversal of the AVL tree
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    inOrderTraversal(root->left);
    cout << "ID: " << root->data.id << ", Name: " << root->data.name << ", Boss ID: " << root->data.bossId << endl;
    inOrderTraversal(root->right);
}

int main() {
    TreeNode* root = nullptr;

    // Inserting employees into the AVL tree
    root = insert(root, Employee(1, "John", 0));
    root = insert(root, Employee(2, "Alice", 1));
    root = insert(root, Employee(3, "Bob", 1));
    root = insert(root, Employee(4, "Carol", 2));
    root = insert(root, Employee(5, "David", 2));
    root = insert(root, Employee(6, "Eve", 3));      
          


    // Printing the employees in the organizational hierarchy
    cout << "Organizational Hierarchy:" << endl;
    inOrderTraversal(root);

    // Finding an employee by ID
    Employee* foundEmployee = findEmployee(root, 3);
    if (foundEmployee != nullptr) {
        cout << "Found Employee: ID: " << foundEmployee->id << ", Name: " << foundEmployee->name << endl;
    } else {
        cout << "Employee not found." << endl;
    }

    // Finding the lowest common boss of two employees
    Employee* lcb = lowestCommonBoss(root, 4, 5);
    if (lcb != nullptr) {
        cout << "Lowest Common Boss: ID: " << lcb->id << ", Name: " << lcb->name << endl;
    } else {
        cout << "Lowest Common Boss not found." << endl;
    }

    // Firing an employee (not implemented in this example)


    return 0;
}
