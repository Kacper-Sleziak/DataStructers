#include <iostream>

class List {
    public:

        struct elementOfList{
            int data;
            elementOfList *next;
        };

        elementOfList *node = 0;
        elementOfList *temporary = 0;
        elementOfList *head = 0;

        void pushEnd(int data){
           node = new elementOfList;
           node -> data = data;

           if (head == 0){
               head = node;
           }

           else{
               temporary -> next = node;
           }

           temporary = node;
           node -> next = 0;
        }

        void pushFront(int data){
            node = new elementOfList;
            if (head == 0){
                this->pushEnd(data);
            }

            else {
                node = new elementOfList;
                node->next = head;
                node->data = data;
                head = node;
                node = temporary;
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

        void pop(int dataToDelete){
            elementOfList *actualElement = head;
            elementOfList *previousElement = 0;
            int data;


            while (true){


                data = actualElement -> data;

                if(data == dataToDelete) {  //warunek usunięcia

                    if(actualElement -> next == 0){  //przypadek kiedy usuwamy ostatni element listy
                        temporary = previousElement;
                        node = previousElement;
                        delete actualElement;
                        actualElement -> next = 0;
                        actualElement = previousElement;
                        actualElement -> next = 0;


                    }

                    else if(previousElement != 0) {        //przypadek ogólny
                        previousElement->next = actualElement->next;
                        delete actualElement;
                        actualElement->next = 0;
                        actualElement = previousElement;
                    }

                    else{                              //przypadek kiedy usuwamy pierwszy element listy
                        head = actualElement -> next;
                        delete actualElement;
                        actualElement->next = 0;

                    }
                }

                previousElement = actualElement;
                actualElement = actualElement->next;

                if(actualElement == 0){
                    break;
                }
            }

        }

        void menu() {

            int x;

            while (x != 4) {

                std::cout << "Wcisnij 1 aby dodac element na poczatek listy" << std::endl;
                std::cout << "Wcisnij 2 aby dodac element na koniec listy" << std::endl;
                std::cout << "Wcisnij 3 aby usunac element z listy" << std::endl;
                std::cout << "Wcisnij 4 aby wyjsc z programu" << std::endl;

                std::cout << std::endl;
                std::cout << "Aktualny stan listy: " << std::endl;
                this->showElements();

                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "Wybierz numer: ";
                std::cin >> x;

                if (x == 1) {
                    int data;
                    std::cout << std::endl;
                    std::cout << "Podaj wartosc ktora chcesz dodac na poczatek listy: ";
                    std::cin >> data;
                    std::cout << std::endl;

                    this->pushFront(data);
                }

                else if (x == 2) {
                    int data;
                    std::cout << std::endl;
                    std::cout << "Podaj wartosc ktora chcesz dodac na koniec listy: ";
                    std::cin >> data;
                    std::cout << std::endl;

                    this->pushEnd(data);
                }

                else if (x == 3) {
                    int data;
                    std::cout << std::endl;
                    std::cout << "Podaj wartosc ktora chcesz usunac z listy: ";
                    std::cin >> data;
                    std::cout << std::endl;

                    this->pop(data);
                }

                else if(x == 4){

                }

                else{
                    std::cout<<"Wybrales zly numer!"<<std::endl;
                }

            }
        }
    };






