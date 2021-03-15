#include <iostream>
#include <string>

// do obsługi drzewa używa się wyłącznie funkcji
// push(data) dodaje gałąź
// pop(data) usuwa gałąź
// printBT() wyświetla utworzone drzewo

class BinarySearchingTree {

public:

    struct node {
        int data;
        node *parent;
        node *leftKid;
        node *rightKid;
    };


    int treeSize = 0;

    node *actualNode = 0;
    node *root = 0;

    void push(int data) {

        actualNode = new node; //do wskaznika przypisujemy nowa stworzona galaz
        actualNode->data = data;

        if (treeSize == 0) {
            root = actualNode;

            actualNode->parent = 0;
            actualNode->leftKid = 0;
            actualNode->rightKid = 0;
        } else {
            node *temporary = root;
            while (true) {
                if (data > temporary->data) {
                    if (temporary->rightKid == 0) {
                        temporary->rightKid = actualNode;

                        actualNode->parent = temporary;
                        actualNode->leftKid = 0;
                        actualNode->rightKid = 0;
                        break;
                    }

                    temporary = temporary->rightKid;
                } else {
                    if (temporary->leftKid == 0) {
                        temporary->leftKid = actualNode;

                        actualNode->parent = temporary;
                        actualNode->leftKid = 0;
                        actualNode->rightKid = 0;
                        break;
                    }
                    temporary = temporary->leftKid;
                }
            }
        }
        treeSize++;
    }

    void removeNode(node *nodeToDelete) {

        if (nodeToDelete->leftKid == 0 and nodeToDelete->rightKid == 0) { //przypadek kiedy gałąź nie ma dzieci

            if (nodeToDelete == root) {
                root = 0;
            }
            else {
                if (nodeToDelete->data > nodeToDelete->parent->data) {
                    nodeToDelete->parent->rightKid = 0;
                }

                else {
                    nodeToDelete->parent->leftKid = 0;
                }

            }
            nodeToDelete->parent =0;
            delete nodeToDelete;
        }

        else if ((nodeToDelete->rightKid != 0 and nodeToDelete->leftKid == 0)
        or (nodeToDelete->rightKid == 0 and nodeToDelete->leftKid != 0)){

            node *nodeToReplace; //galaz ktora chcemy przeniesc w inne miejsce

            if (nodeToDelete->rightKid != 0 and nodeToDelete->leftKid == 0) {
                nodeToReplace = nodeToDelete->rightKid;
            }

            else if(nodeToDelete->rightKid == 0 and nodeToDelete->leftKid != 0){
                nodeToReplace = nodeToDelete->leftKid;
            }



            if (nodeToDelete == root) {
                root = nodeToDelete->leftKid;
            }

            else {
                node *actualNode = nodeToDelete->parent;   //aktualnie sprawdzona galaz pod katem przypiecia wczesniejszej galezi

                while (true){
                    if (actualNode -> data < nodeToReplace -> data){
                        if(actualNode -> rightKid == 0){
                            nodeToReplace ->parent = actualNode;
                            actualNode -> rightKid = nodeToReplace;
                            break;
                        }
                        else{
                            actualNode = actualNode -> rightKid;
                        }
                    }

                    else{
                        if(actualNode -> leftKid == 0){
                            nodeToReplace -> parent = actualNode;
                            actualNode -> leftKid = nodeToReplace;
                            break;
                        }

                        else{
                            actualNode = actualNode -> leftKid;
                        }
                    }


                }
            }
            nodeToDelete -> parent = 0;
            nodeToDelete -> rightKid = 0;
            nodeToDelete -> leftKid = 0;
            delete nodeToDelete;

            }
            else { //uzywam rekurencji, zeby sprowadzić usuwanie do, któregos z wcześniejszych przypadków

                nodeToDelete->data = nodeToDelete->rightKid->data;
                nodeToDelete = nodeToDelete->rightKid;
                nodeToDelete ->parent->rightKid =0;

                removeNode(nodeToDelete);
            }

            treeSize--;
        }

        void pop(int data) {
            while (true) {
                node *nodeToDelete = searchValue(data);

                if (nodeToDelete != 0) {
                    removeNode(nodeToDelete);
                } else {
                    break;
                }
            }
        }

        node *searchAlgorithm(int data, node *actualNode) {

            if (actualNode->data > data and actualNode->leftKid != 0) {
                searchAlgorithm(data, actualNode->leftKid);
            } else if (actualNode->data < data and actualNode->rightKid != 0) {
                searchAlgorithm(data, actualNode->rightKid);
            } else if (actualNode->data == data) {
                return actualNode;
            } else {
                return 0;
            }
        }


        node *searchValue(int data) {
            return searchAlgorithm(data, root);
        }

        void printBT(const std::string &prefix, const node *node, bool isLeft) {
            if (node != 0) {
                std::cout << prefix;

                std::cout << (isLeft ? "|--->" : "|--->");

                // print the value of the node
                std::cout << node->data << std::endl;

                // enter the next tree level - left and right branch
                printBT(prefix + (isLeft ? "|   " : "    "), node->leftKid, true);
                printBT(prefix + (isLeft ? "|   " : "    "), node->rightKid, false);
            }
        }

        void printBT(const node *node) //trzeba zaczac z korzeń
        {
            printBT("", node, false);
        }

        void printBT() {
            printBT(root);
        }

        bool isParentGraterThanKid(node *parent, node *kid) {
            if (parent->data < kid->data) {
                return false;
            } else {
                return true;
            }
        }
    };

