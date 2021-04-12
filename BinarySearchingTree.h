#include <iostream>
#include <string>

// do obsługi drzewa używa się wyłącznie funkcji
// push(key) dodaje gałąź
// pop(key) usuwa gałąź
// printBT() wyświetla utworzone drzewo

class BinarySearchingTree {

public:

    struct node {
        int key;
        node *parent;
        node *leftKid;
        node *rightKid;
    };


    int treeSize = 0;

    node *actualNode = 0;
    node *root = 0;

    void push(int data) {

        actualNode = new node; //do wskaznika przypisujemy nowa stworzona galaz
        actualNode->key = data;

        if (treeSize == 0) {
            root = actualNode;

            actualNode->parent = 0;
            actualNode->leftKid = 0;
            actualNode->rightKid = 0;
        }
        else {
            node *temporary = root;

            while (true) {
                if (data > temporary->key) {
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

            if (nodeToDelete -> parent ==0) {
                root = 0;
            }

            else {
                if (nodeToDelete->key >= nodeToDelete->parent->key) {
                    nodeToDelete->parent->rightKid = 0;
                }

                else {
                    nodeToDelete->parent->leftKid = 0;
                }

            }
            delete nodeToDelete;
        }

        else if ((nodeToDelete->rightKid != 0 and nodeToDelete->leftKid == 0)   //przypadek kiedy galaz ma jedno dziecko
            or (nodeToDelete->rightKid == 0 and nodeToDelete->leftKid != 0)){

            node *nodeToReplace; //galaz ktora chcemy przeniesc w inne miejsce

            if (nodeToDelete->rightKid != 0 and nodeToDelete->leftKid == 0) {
                nodeToReplace = nodeToDelete->rightKid;
            }

            else if(nodeToDelete->rightKid == 0 and nodeToDelete->leftKid != 0){
                nodeToReplace = nodeToDelete->leftKid;
            }




            if (nodeToDelete -> parent == 0) {  //kiedy galaz do usuniecia jest jednoczesnie korzeniem
                if(nodeToDelete -> rightKid ==0 and nodeToDelete -> leftKid !=0){
                    root = nodeToDelete -> leftKid;
                    nodeToDelete -> leftKid -> parent = 0;
                }

                else{
                    root = nodeToDelete -> rightKid;
                    nodeToDelete -> rightKid -> parent = 0;
                }
            }

            else {  //inne przypadki

                node *actualNode = nodeToDelete->parent;   //aktualnie sprawdzona galaz pod katem przypiecia wczesniejszej galezi

                if(actualNode ->key < nodeToDelete ->key){   //na 0 ustawiamy dziecko, ktore zostanie usuniete w nastepnym kroku
                    actualNode -> rightKid = 0;
                }

                else{
                    actualNode->leftKid =0;
                }

                while (true){
                    if (actualNode -> key < nodeToReplace -> key){
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

            else { //uzywam rekurencji, zeby sprowadzić usuwanie do, któregos z wcześniejszych przypadków( 2 dzieci)

                nodeToDelete->key = nodeToDelete->rightKid->key;
                nodeToDelete = nodeToDelete->rightKid;
                nodeToDelete ->parent->rightKid =0;

//                std::cout<<"Galoz do usuniecia"<< nodeToDelete ->key;
//                std::cout<<"Galaz do przesuniecia"<<nodeToDelete->rightKid->key;


                removeNode(nodeToDelete);

            }
            treeSize--;
            }

        void pop(int data) {
            while (true) {
                node *nodeToDelete = searchValue(data);
                if (nodeToDelete != 0) {
                    removeNode(nodeToDelete);
                }
                else {
                    break;
                }
            }
        }

        node *searchAlgorithm(int data, node *actualNode) {

            if (actualNode->key > data and actualNode->leftKid != 0) {
                searchAlgorithm(data, actualNode->leftKid);
            }
            else if (actualNode->key < data and actualNode->rightKid != 0) {
                searchAlgorithm(data, actualNode->rightKid);
            }
            else if (actualNode->key == data) {
                return actualNode;
            }
            else {
                return 0;
            }
        }


        node *searchValue(int data) {
            if (root == 0){
                return 0;
            }
            else {
                return searchAlgorithm(data, root);
            }
        }

        void printBT(const std::string &prefix, const node *node, bool isLeft) {
            if (node != 0) {
                std::cout << prefix;

                std::cout << (isLeft ? "|--->" : "|--->");


                std::cout << node->key << std::endl;


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
            if (parent->key < kid->key) {
                return false;
            } else {
                return true;
            }
        }

    void menu(){

        int x;

        while (x != 3) {
            std::cout << "Wcisnij 1 aby dodac element do drzewa BST" << std::endl;
            std::cout << "Wcisnij 2 aby usunac element z drzewa BST" << std::endl;
            std::cout << "Wcisnij 3 aby wyjsc z programu" << std::endl;

            std::cout << std::endl;
            std::cout << "Aktualny stan drzewa BST: " << std::endl;
            this->printBT();

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Wybierz numer: ";
            std::cin >> x;

            if (x == 1) {
                int data;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora chcesz dodac do drzewa BST: ";
                std::cin >> data;
                std::cout << std::endl;

                this->push(data);
            }

            else if (x == 2) {
                int data;
                std::cout << std::endl;
                std::cout << "Podaj index elementu, ktory chcesz usunac z drzewa BST ";
                std::cin >> data;
                std::cout << std::endl;

                this->pop(data);
            }

            else if(x == 3){
            }

            else{
                std::cout<<"Wybrales zly numer!"<<std::endl;
            }
        }

        }
    };

