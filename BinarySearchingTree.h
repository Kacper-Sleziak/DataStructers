#include <iostream>
#include <string>


class BinarySearchingTree {

    public:

    struct node{
        int data;
        node * parent;
        node * leftKid;
        node * rightKid;
    };


    int treeSize = 0;

    node * actualNode = 0;
    node * root = 0;

    void push(int data){

        actualNode = new node; //do wskaznika przypisujemy nowa stworzona galaz
        actualNode -> data = data;

        if(treeSize == 0){
            root = actualNode;

            actualNode -> parent = 0;
            actualNode -> leftKid = 0;
            actualNode -> rightKid = 0;
        }


        else {
            node * temporary = root;
            while (true){
                if (data > temporary -> data){
                    if (temporary -> rightKid == 0){
                        temporary -> rightKid = actualNode;

                        actualNode -> parent = temporary;
                        actualNode -> leftKid = 0;
                        actualNode -> rightKid = 0;
                        break;
                    }

                    temporary = temporary -> rightKid;
                }

                else{
                    if(temporary -> leftKid == 0){
                        temporary -> leftKid = actualNode;

                        actualNode -> parent = temporary;
                        actualNode -> leftKid = 0;
                        actualNode -> rightKid = 0;
                        break;
                    }
                    temporary = temporary -> leftKid;
                }
            }
        }
        treeSize ++;
    }

    void pop(int data){
        while (true){
            node * nodeToDelte = this -> searchValue(data);

            if (nodeToDelte != 0){
                if(nodeToDelte -> leftKid == 0 and nodeToDelte -> rightKid == 0) { //przypadek kiedy gałąź nie ma dzieci

                    if (nodeToDelte->data > nodeToDelte->parent->data) {
                        nodeToDelte->parent->rightKid = 0;
                    } else {
                        nodeToDelte->parent->leftKid = 0;
                    }
                    delete nodeToDelte;
                }

                else if(nodeToDelte -> leftKid !=0 and nodeToDelte ->rightKid ==0 ){ //kiedy gałąź ma tylko lewe dziecko
                    nodeToDelte->leftKid->parent = nodeToDelte ->parent;
                    delete nodeToDelte;
                }

                else if(nodeToDelte -> rightKid !=0 and nodeToDelte ->leftKid ==0 ){ //kiedy gałąź ma tylko prawe dziecko
                    nodeToDelte->rightKid->parent = nodeToDelte -> parent;
                    delete nodeToDelte;
                }

                else{ //pozostałe przypadki

                }

                treeSize --;
            }

            else{
                break;
            }
        }
    }

    node* searchAlgorithm(int data, node * actualNode) {

        if (actualNode->data > data and actualNode->leftKid != 0) {
            searchAlgorithm(data, actualNode->leftKid);
        }

        else if (actualNode-> data  < data and actualNode->rightKid != 0) {
                searchAlgorithm(data, actualNode->rightKid);
        }

       else if (actualNode -> data == data) {
            return actualNode;
        }

       else {
            return 0;
        }
    }


    node *searchValue(int data){
        return searchAlgorithm(data, root);
    }


    void movingOnTree(){
        preOder(root);
    }

    void preOder(node* node){           //algorytm chodzienia po drzewie
        std::cout<<node -> data<<"  ";

        if(node -> leftKid !=0){
            preOder(node->leftKid);
        }
        else if(node -> rightKid !=0){
            preOder(node -> rightKid);
        }

    }

};

