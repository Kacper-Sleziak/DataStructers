
class DoublyLinkedList {
public:

    struct elementOfList{
        int data;
        elementOfList *next;
        elementOfList *previous;
    };

    int listSize = 0;
    elementOfList *node = 0;
    elementOfList *head = 0;
    elementOfList *tail = 0;

    void pushEnd(int data){
        node = new elementOfList;
        node -> data = data;

        if (head == 0){
            head = node;
            node -> previous = 0;
        }

        else{
            tail -> next = node;
            node -> previous = tail;
        }

        tail = node;
        node -> next = 0;
        listSize ++;
    }

    void pushFront(int data){
        node = new elementOfList;
        if (head == 0){
            this->pushEnd(data);
        }

        else {
            node = new elementOfList;
            node -> data = data;
            node -> previous = 0;
            node -> next = head;

            head -> previous = node;
            head = node;

            listSize ++;
        }

    }

    void showElements(){

        if (head != 0) {

            elementOfList *actualElement = head;
            int data = actualElement->data;
            std::cout << std::endl;

            std::cout << "----" << std::endl;

            while (true) {
                std::cout << data;
                std::cout << " ";

                if (actualElement->next == 0) {
                    std::cout<<std::endl;
                    std::cout << "----";
                    break;
                }

                actualElement = actualElement->next;
                data = actualElement->data;
            }
        }

        else{
            std::cout<<"Lista jest pusta!";
        }
    }

    int getListSize(){

        return listSize;
    }

};


