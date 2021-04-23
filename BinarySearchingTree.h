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

        void createTreeFromFile(std::string file);         //funkcja wyswietla menu
        void bstMenu();

    private:
            int treeSize = 0;
            node *actualNode = 0;                           //wskaznik na galaz na, ktorej aktualnie operujemy (galaz pomocnicza)
            node *root = 0;                                 //wskaznik na korzen

    void push(int data);                                    //funkcja dodaje galaz do drzewa
    void removeNode(node *nodeToDelete);                    //funckja usuwa dana galaz z drzewa
    void pop(int data);                                     //funkcja sprawdz czy dana wartosc jest w drzewie i wywoluje funkcje removeNode(

    node *searchAlgorithm(int data, node *actualNode);      //funkcja zwraca znaleziona galaz badz 0 w przypadku gdy nie jest znaleziona
    node *searchValue(int data);
    bool isParentGraterThanKid(node *parent, node *kid);    //funckja zwraca wartosc True gdy klucz galezi w pierwsyzm argumencie jest wiekszy badz rowny

    void printBT();
    void printBT(const std::string &prefix, const node *node, bool isLeft);
    void printBT(const node *node);


};

void BinarySearchingTree::push(int data) {

    actualNode = new node;          //do wskaznika przypisujemy nowa stworzona galaz
    actualNode->key = data;         //wartosc danej galezi

    if (treeSize == 0) {            //przypadek kiedy dodajemy pierwszy element
        root = actualNode;

        actualNode->parent = 0;
        actualNode->leftKid = 0;
        actualNode->rightKid = 0;
    }
    else
    {                          //inne przypadki
        node *temporary = root;

        while (true) {                                  //szukamy miejsca gdzie mozemy dodac nowa galaz
            if (data > temporary->key) {
                if (temporary->rightKid == 0) {
                    temporary->rightKid = actualNode;

                    actualNode->parent = temporary;
                    actualNode->leftKid = 0;
                    actualNode->rightKid = 0;
                    break;
                }

                temporary = temporary->rightKid;
            }
            else {
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

void BinarySearchingTree::removeNode(node *nodeToDelete) {

    if (nodeToDelete->leftKid == 0 and nodeToDelete->rightKid == 0) { //przypadek kiedy gałąź nie ma dzieci

        if (nodeToDelete->parent == 0) {
            root = 0;
        }

        else {                                                       //zmieniamy wskazniki rodzica, usnietej galezi
            if (nodeToDelete->key >= nodeToDelete->parent->key) {
                nodeToDelete->parent->rightKid = 0;
            }

            else{
                nodeToDelete->parent->leftKid = 0;
            }
        }
        delete nodeToDelete;
    }

    else if(nodeToDelete ->leftKid != 0 and nodeToDelete -> rightKid != 0) { //przypadek kiedy galaz ma dwojke dzieci
        node *nodeMinimum = nodeToDelete -> rightKid;
        node *nodeToPin = nodeToDelete;

        while (true){

            if (nodeMinimum -> leftKid != 0){        //szukanie minimum w prawym poddrzewiu
                nodeToPin = nodeMinimum;
                nodeMinimum = nodeMinimum -> leftKid;
            }

            else{
                break;
            }
        }
        if (nodeToPin != nodeToDelete) {                    //przypadek kiedy galaz do ktorej przypimany nie jest galezia, ktora chcemy usunac

            if (nodeMinimum->rightKid != 0) {               //przypadek kiedy minumum ma prawe dziecko
                nodeToPin->leftKid = nodeMinimum->rightKid;
            }

            else {
                nodeToPin->leftKid = 0;
            }
        }

        else{
            if(nodeMinimum -> rightKid != 0){
                nodeToPin -> rightKid = nodeMinimum ->rightKid;
                nodeToPin -> rightKid -> parent = nodeToPin;
            }

            else if(nodeMinimum -> leftKid !=0){
                nodeToPin -> rightKid = nodeMinimum ->leftKid;
                nodeToPin -> rightKid -> parent = nodeToPin;
            }

            else{
                nodeToPin->rightKid = 0;
            }
        }

        nodeToDelete -> key = nodeMinimum -> key;
        nodeMinimum->parent = 0;
        nodeMinimum->leftKid = 0;
        nodeMinimum->rightKid = 0;
        delete nodeMinimum;
    }

    else{                                              //przypadek kiedy ma jedno dziecko
        node * nodeToReplace;

        if (nodeToDelete->rightKid == 0) {              //przypadek kiedy galaz ma tylko lewe dziecko
            nodeToReplace = nodeToDelete->leftKid;
        }

        else{                                          //przypadek kiedy galaz ma tylko prawe dziecko
            nodeToReplace = nodeToDelete->rightKid;
        }


        if (nodeToDelete == root){                      //przypadek kiedy galaz sie korzeniem
            nodeToReplace -> parent = 0;
            root = nodeToReplace;
        }

        else {

            node *nodeToPin = nodeToDelete->parent;     //galaz do ktorej chcemy przypiac ,,wolna" galaz

            if (nodeToReplace->key > nodeToPin->key) {       //przypadek kiedy nodeToReplace bedzie prawym dzieckiem
                nodeToPin->rightKid = nodeToReplace;
            }

            else {                                           //przypadek kiedy nodeToReplace bedzie lewym dzieckiem
                nodeToPin->leftKid = nodeToReplace;
            }

            nodeToReplace -> parent = nodeToPin;
        }

        nodeToDelete ->parent = 0;
        nodeToDelete -> leftKid =0;
        nodeToDelete ->rightKid =0;

        delete nodeToDelete;
    }

    treeSize--;
}


void BinarySearchingTree::pop(int data) {
    while (true) {
        node *nodeToDelete = searchValue(data);
        if (nodeToDelete != 0) {        //jesli wartosc zostala znaleziona, usuwamy ja i szukamy czy innych galezi o takim samym kluczu
            removeNode(nodeToDelete);
        }
        else{                           //jesli galezi nie znaleziono to przerywamy szukanie
            std::cout<<"Nie ma takiej wartosci w drzewie!";
            std::cout<<std::endl;
            break;
        }
    }
}

BinarySearchingTree::node *BinarySearchingTree::searchAlgorithm(int data, node *actualNode) {

    if (actualNode->key > data and actualNode->leftKid != 0) {
        searchAlgorithm(data, actualNode->leftKid);
    }

    else if (actualNode->key < data and actualNode->rightKid != 0) {
        searchAlgorithm(data, actualNode->rightKid);
    }

    else if (actualNode->key == data) {
        return actualNode;
    }

    else
    {
        return 0;
    }
}

BinarySearchingTree::node *BinarySearchingTree::searchValue(int data) {
    if (root == 0) {
        return 0;
    }

    else{
        return searchAlgorithm(data, root);
    }
}

void BinarySearchingTree::printBT(const std::string &prefix, const node *node,
             bool isLeft) {            //Wysiwetlanie napisane niesamodzienie
    if (node != 0) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--->" : "|--->");


        std::cout << node->key << std::endl;


        printBT(prefix + (isLeft ? "|   " : "    "), node->leftKid, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->rightKid, false);
    }
}

void BinarySearchingTree::printBT(const node *node) //trzeba zaczac z korzeń
{
    printBT("", node, false);
}

void BinarySearchingTree::printBT() {
    printBT(root);
}

bool BinarySearchingTree::isParentGraterThanKid(node *parent, node *kid) {
    if (parent->key < kid->key) {
        return false;
    } else {
        return true;
    }
}

void BinarySearchingTree::createTreeFromFile(std::string file) {

    std::fstream myfile(file, std::ios_base::in);

    int data;
    while (myfile >> data)
        //while (myfile.good())
    {
        if (!myfile.fail()) {
            this->push(data);
        }

        else {
            break;
        }
    }
}
    void BinarySearchingTree::bstMenu() {

        int x;

        while (x != 3) {
            std::cout << "Wcisnij 0 aby stworzyc drzewo z pliku" << std::endl;
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

            if (x == 0) {
                std::string file;
                std::cout << std::endl;
                std::cout << "Podaj plik, z ktorgo chcesz stworzyc drzewo: ";
                std::cin >> file;
                std::cout << std::endl;

                this->createTreeFromFile(file);
            }

            else if (x == 1) {
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
                std::cout << "Podaj wartosc, ktora chcesz usunac: ";
                std::cin >> data;
                std::cout << std::endl;

                this->pop(data);
            }
            else if (x == 3) {
                std::cout << std::endl;
                std::cout << std::endl;
            }
            else {
                std::cout << "Wybrales zly numer!" << std::endl;
            }
        }
    }

