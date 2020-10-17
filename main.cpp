#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include<bits/stdc++.h>
#include <queue>

using namespace std;

//Binary Tree
typedef int EType;

typedef struct tnode {
    EType data;
    struct tnode *left;
    struct tnode *right;
    int height;
} TNode;

typedef struct tnode *BTREE;

tnode *newBinaryNode(int val) {
    tnode *temp = new tnode;
    temp->left = temp->right = NULL;
    temp->data = val;
    temp->height = 1;
    return temp;
}



void preorder(BTREE T);

void postorder(BTREE T);

void inorder(BTREE T);

int height(BTREE T);

void show_node(BTREE T);

using namespace std;


void preorder(BTREE T) {
    if (T != NULL) {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}

void postorder(BTREE T) {
    if (T != NULL) {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}

void inorder(BTREE T) {
    if (T != NULL) {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}


int getheight(BTREE T) {
    int left_h, right_h, max;
    if (T == NULL)
        return -1;
    else {
        left_h = getheight(T->left);
        right_h = getheight(T->right);
        if (left_h > right_h)
            max = left_h;
        else
            max = right_h;
        return (max + 1);
    }
}

int getBinaryTbalance(BTREE binary) {
    if (binary == NULL)

        return 0;

    return getheight(binary->left) - getheight(binary->right);
}






void show_node(BTREE T) {
    cout << T->data << ", ";
}


//My DS
//Rooted Tree

typedef struct RootedTreeNode {
    EType data;
    vector<RootedTreeNode *> children;
} RootedTreeNode;


typedef struct RootedTreeNode *RootedTree;

RootedTreeNode *newRootedNode(int val) {
    RootedTreeNode *temp = new RootedTreeNode;

    temp->data = val;
    return temp;
}

//AVL tree

int height(BTREE Node) {
    if (Node == NULL)

        return 0;

    return Node->height;
}

BTREE rightRotate(BTREE node) {
    BTREE tmp = node->left;
    BTREE tmp2 = tmp->right;

    tmp->right = node;
    node->left = tmp2;

    node->height = 1 + max(height(node->left), height(node->right));

    tmp->height = 1 + max(height(tmp->left), height(tmp->right));

    return tmp;
}

BTREE leftRotate(BTREE node) {
    BTREE tmp = node->right;
    BTREE tmp2 = tmp->left;

    tmp->left = node;
    node->right = tmp2;

    node->height = 1 + max(height(node->left), height(node->right));
    tmp->height = 1 + max(height(tmp->left), height(tmp->right));

    return tmp;
}

int getBalance(BTREE N) {
    if (N == NULL)

        return 0;

    return height(N->left) - height(N->right);
}

BTREE insertAVL(BTREE AVLnode, int val) {

    if (AVLnode == NULL) {
        return (newBinaryNode(val));
    }


    if (AVLnode->data > val)
        AVLnode->left = insertAVL(AVLnode->left, val);

    else if (AVLnode->data < val)
        AVLnode->right = insertAVL(AVLnode->right, val);

    AVLnode->height = max(height(AVLnode->right), height(AVLnode->left)) + 1;


    int NodeBalance = getBalance(AVLnode);

    // Left left
    if (NodeBalance > 1 && val < AVLnode->left->data)

        return rightRotate(AVLnode);

    // Right right
    if (NodeBalance < -1 && val > AVLnode->right->data)

        return leftRotate(AVLnode);

    // Left right
    if (NodeBalance > 1 && val > AVLnode->left->data) {

        AVLnode->left = leftRotate(AVLnode->left);

        return rightRotate(AVLnode);
    }

    // Right left
    if (NodeBalance < -1 && val < AVLnode->right->data) {

        AVLnode->right = rightRotate(AVLnode->right);

        return leftRotate(AVLnode);
    }
    return AVLnode;
}


//Program
void print_matrix(int **C, int m) {
    for (int r = 0; r < m; r++) {
        for (int s = 0; s < m; s++) {
            cout << C[r][s] << "\t";
        }
        cout << endl;
    }
}

bool hasIsolatedNode(int **C, int m) {
    bool hasIsolatedNode;
    for (int i = 0; i < m; ++i) {
        hasIsolatedNode = true;
        for (int j = 0; j < m; ++j) {
            if (hasIsolatedNode && C[i][j] == 1)
                hasIsolatedNode = false;
        }
        if (hasIsolatedNode) {
            cout << "The matrix has one or more isolated nodes and doesn't represent a tree.\n";
            return true;
        }
    }
    return false;
}

bool check_adjacency(int **C, int m) {


    for (int r = 0; r < m; r++) {

        if (C[r][r] != 0)
            return false;
        for (int s = r + 1; s < m; s++) {
            if (C[r][s] != C[s][r])
                return false;

        }

    }

    return true;
}

void getRootedTreeNumbers(RootedTree tmp2, vector<int> &vec) {
    vec.push_back(tmp2->data);
    for (int j = 0; j < tmp2->children.size(); ++j) {
        getRootedTreeNumbers(tmp2->children[j], vec);
    }

}

void printBinaryTree(BTREE tree) {
    cout << "Node data :" << tree->data << endl;
    cout << "left data :";
    if (tree->left == NULL) {
        cout << "NULL   ";
    } else {
        cout << tree->left->data << "   ";
    }
    cout << "right data :";
    if (tree->right == NULL) {
        cout << "NULL\n";
    } else {
        cout << tree->right->data << '\n';
    }
    cout << '\n';
    if (tree->left != NULL) {
        printBinaryTree(tree->left);
    }
    if (tree->right != NULL) {
        printBinaryTree(tree->right);
    }
}



void inorderBinaryTree(BTREE T, vector<int> &vec) {
    if (T != NULL) {
        inorderBinaryTree(T->left, vec);
        vec.push_back(T->data);
        inorderBinaryTree(T->right, vec);
    }
}

BTREE BinaryTreeToAVLTREE(BTREE &avlTree,BTREE binaryTree) {

    vector<int> vec ;//= {1, 2, 3, 6, 5, 4};
    inorderBinaryTree(binaryTree,vec);
    cout<<"Traverse the binary tree inorder: ";
    for (int j = 0; j < vec.size(); ++j) {
        cout<<vec[j]<<", ";
    }
    cout<<endl<<endl;


    for (int i = 0; i < vec.size(); ++i) {
        avlTree = insertAVL(avlTree, vec[i]);
    }

    return avlTree;
}


RootedTreeNode *searchRTreeNode(RootedTree T, int data) {
    if (T == NULL)
        return NULL;
    if (T->data == data)
        return T;
    else {
        for (int i = 0; i < T->children.size(); i++) {
            if (T->children[i]->data == data)
                return T->children[i];
        }
        for (int i = 0; i < T->children.size(); i++) {
            return searchRTreeNode(T->children[i], data);
        }
    }
    return NULL;
}


bool hasCycles(int **D, int m) {
    /*
    to check cycles, when u add children of node A u should remove its (node B) parent from its connection with node A
    then add B to the vector
    then if we found another parent to the node B which is son of A (As it's found in the vector) it's cyclic
    */
    int **C;
    int i, j, r, current;
    C = (int **) malloc(m * sizeof(int *));

    if (C == NULL) {
        cout << "Out from memory";
        return 4;
    }


    for (r = 0; r < m; r++) {
        C[r] = (int *) malloc(m * sizeof(int));

        if (C[r] == NULL) {
            cout << "Out from memory";
            return 2;
        }
    }
    for (j = 0; j < m; ++j) {
        for (i = 0; i < m; ++i) {
            C[j][i] = D[j][i];
        }
    }
    vector<int> visited;

    stack<int> toBeVisited;

    toBeVisited.push(0);
    while (!toBeVisited.empty()) {
        current = toBeVisited.top();
        toBeVisited.pop();
        for (i = 0; i < m; i++) {
            if (i == current)
                continue;
            if (C[current][i] == 1) {


                //found cycle
                if (find(visited.begin(), visited.end(), i) != visited.end()) {
                    return true;
                }
                    //new number
                else {
                    toBeVisited.push(i);
                    visited.push_back(i);
                    //So that we make node 'i' does not consider 'current' as a child
                    C[i][current] = 0;
                }
            }
        }
    }
    return false;

}

BTREE insertChildren(BTREE binary, EType data, RootedTree R) {
    if (binary->data == data) {
        binary->left = newBinaryNode(R->children[0]->data);
        BTREE tmp = binary->left;
        for (int i = 1; i < R->children.size(); ++i) {
            tmp->right = newBinaryNode(R->children[i]->data);
            tmp = tmp->right;
        }
    } else if (binary->left != NULL)
        binary->left = insertChildren(binary->left, data, R);

    else if (binary->right != NULL)
        binary->right = insertChildren(binary->right, data, R);

    return binary;
}

BTREE insertBtreeFromRootedTree(RootedTree R) {
    BTREE binaryTree = newBinaryNode(R->data);
    queue<RootedTree> Q;
    Q.push(R);
    //we inserted the first node

    RootedTree tmp;

    while (!Q.empty()) {
        tmp = Q.back();
        Q.pop();
        if (!tmp->children.empty()) {
            binaryTree = insertChildren(binaryTree, tmp->data, tmp);
        }
        for (int i = 0; i < tmp->children.size(); ++i) {
            Q.push(tmp->children[i]);
        }
    }
    return binaryTree;

}

//ROOTED TREE

void printRootedTree(RootedTreeNode *tmp2) {


    cout << "Node is : " << tmp2->data << endl;

    if (tmp2->children.empty())
        cout << "The node has no children.";
    else {
        cout << "children are :";
        for (int j = 0; j < tmp2->children.size(); ++j) {
            cout << tmp2->children[j]->data << " ";
        }
    }

    cout << endl;
    for (int j = 0; j < tmp2->children.size(); ++j) {
        printRootedTree(tmp2->children[j]);
    }


}

RootedTree convert_to_rootedtree(int **C, int m, int root) {

    RootedTreeNode *tmp = newRootedNode(root + 1);

    RootedTree rootedtree = tmp;

    stack<int> toBeVisited;

    int i;
    for (i = 0; i < m; i++) {
        if (i == root)
            continue;
        if (C[root][i] == 1) {
            toBeVisited.push(i);
            tmp->children.push_back(newRootedNode(i + 1));

            //remove the root from the children's children
            C[i][root] = 0;
        }
    }

    int current;
    while (!toBeVisited.empty()) {
        current = toBeVisited.top();
        toBeVisited.pop();

        for (i = 0; i < m; i++) {
            if (i == current)
                continue;
            if (C[current][i] == 1) {
                searchRTreeNode(rootedtree, current + 1)->children.push_back(newRootedNode(i + 1));
                C[i][current] = 0;

                toBeVisited.push(i);
            }
        }
    }

    return rootedtree;
}

int main() {

    int **C;
    int r, s, m;

    cout << "Enter the number of nodes:";
    cin >> m;
    m = 6;

    if (m < 2)
        return 1;

    cout<<"Enter the matrix\n";

    //memory allocation

    C = (int **) malloc(m * sizeof(int *));

    if (C == NULL) {
        cout << "Out from memory";
        return 4;
    }


    for (r = 0; r < m; r++) {
        C[r] = (int *) malloc(m * sizeof(int));

        if (C[r] == NULL) {
            cout << "Out from memory";
            return 2;
        }
    }

    bool adjacency = true;

    //input integers
    for (r = 0; r < m; r++) {
        for (s = 0; s < m; s++) {
            cin >> C[r][s];
            if (C[r][s] != 0 && C[r][s] != 1) {
                adjacency = false;
            }

        }
    }




    //print integers
    print_matrix(C, m);

    if(hasIsolatedNode(C,m))
        return 1;
    // check if it's an Adjacency Matrix
    if (!adjacency || !check_adjacency(C, m)) {
        cout << "The matrix is not adjacent\n";
        return 1;
    } else {

        cout << "The matrix is adjacent matrix\n";

        if (hasCycles(C, m)) {
              cout<<"The adjacent matrix has cycles\n";
        } else {
            cout<<"The adjacent matrix has no cycles\n";
        }

        //input root
        int root;
        cout << "Please enter the desired root for the rooted tree:";
        cin >> root;

        //root must be from 1 to m
        if (root > m || root <= 0) {
            cout << "Root is not in range\n";
            return 1;
        }
        //convert into rooted tree
        RootedTree rootedTree = convert_to_rootedtree(C, m, root - 1);
        cout<<"\nThe rooted tree based on root '"<<root<<"' data are: \n";
        printRootedTree(rootedTree);

        //convert into binary tree
        BTREE binaryTree = insertBtreeFromRootedTree(rootedTree); //convert_to_binary(rootedTree, m);
        cout<<"\n \n \nThe binary tree data:\n";
        printBinaryTree(binaryTree);

        int balance = getBinaryTbalance(binaryTree);
        if(balance<-1 || balance > 1){
            cout<<"The binary tree is not balanced as the difference between the left sub-tree and right sub-tree heights is: "<<balance<<endl;
            BTREE avlTree = BinaryTreeToAVLTREE(avlTree,binaryTree);
            cout<<"Traverse the AVL tree inorder: ";
            inorder(avlTree);
            cout<<"\nTraverse the AVL tree postorder: ";
            postorder(avlTree);
            cout<<"\nTraverse the AVL tree preorder: ";
            preorder(avlTree);
        }
        else{
            cout<<"The binary tree is balanced as the difference between the left sub-tree and right sub-tree heights is: "<<balance<<endl;
        }


    }



    return 0;
}
