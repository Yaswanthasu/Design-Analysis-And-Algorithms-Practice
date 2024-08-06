#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the BST
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Function to create a new BST node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
Node* insert(Node* root, int key) {
    // If the tree is empty, return a new node
    if (root == NULL) return createNode(key);

    // Otherwise, recur down the tree
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    // Return the (unchanged) node pointer
    return root;
}

// Function to search for a key in the BST
Node* search(Node* root, int key) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key) return root;

    // Key is greater than root's key
    if (root->key < key) return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

// Function for in-order traversal of the BST
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Main function to test the BST implementation
int main() {
    Node* root = NULL;
    int n, key;

    // Input number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Insert elements into the BST
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter element %d : ",i+1);
        scanf("%d", &key);
        root = insert(root, key);
    }

    // Display the BST
    printf("In-order traversal of the BST:\n");
    inOrder(root);
    printf("\n");

    // Search for a key
    printf("Enter key to search: ");
    scanf("%d", &key);
    Node* result = search(root, key);
    if (result != NULL) {
        printf("Key %d found in the BST.\n", key);
    } else {
        printf("Key %d not found in the BST.\n", key);
    }

    // Free allocated memory (not shown here for simplicity)
    // Implement a function to free the entire tree if needed

    return 0;
}

