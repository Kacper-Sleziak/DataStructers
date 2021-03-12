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
        node * temporary = root;
        actualNode -> data = data;

        if(treeSize == 0){
            root = actualNode;
        }

        else {
            while (true){
                if (data > temporary -> data){
                    if (temporary -> rightKid == 0){
                        temporary -> rightKid = actualNode;
                        actualNode -> parent = temporary;
                        break;
                    }

                    temporary = temporary -> rightKid;
                }

                else{
                    if(temporary -> leftKid == 0){
                        temporary -> leftKid = actualNode;
                        actualNode -> parent = temporary;
                        break;
                    }
                    temporary = temporary -> leftKid;
                }
            }
        }
        treeSize ++;
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

