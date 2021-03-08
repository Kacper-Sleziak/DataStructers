#include <iostream>


class Stack {
    public:

        struct elementOfStack{
            int data;
            elementOfStack * next; //wskaznik na element znajdujący się pod spodem;
        };

        elementOfStack * temporary = 0;
        elementOfStack * element = 0;

        void push(int data){
            element = new elementOfStack;
            element -> data = data;

            if(temporary == 0){
                temporary = element;
                temporary -> next = 0;
            }

            else{
                element -> next = temporary;
                temporary = element;
            }
        }

        void pop(){

            if (temporary == 0){
                std::cout<<std::endl;
                std::cout<<"W stosie nie ma elementow do usuniecia!";
                std::cout<<std::endl;
            }

            else {
                if (temporary->next != 0) {
                    temporary = temporary->next;
                } else {
                    temporary = 0;
                }
            }
        }

        void showElements(){

            if (temporary == 0){
                std::cout<<"Stos jest pusty!";
            }

            else{

                elementOfStack * actualElement = temporary;
                std::cout<<"----"<<std::endl;

                while (true) {
                    std::cout << actualElement->data << std::endl;

                    if (actualElement->next == 0) {
                        std::cout<<"----";
                        break;
                    }

                    actualElement = actualElement->next;

                }
            }

        }

        void panel(){

            int x;

            while (x != 3){

                std::cout<<"Wcisnij 1 aby dodac element do stosu"<<std::endl;
                std::cout<<"Wcisnij 2 aby usunac element ze stosu"<<std::endl;
                std::cout<<"Wcisnij 3 aby wyjsc z programu"<<std::endl;

                std::cout<<std::endl;
                std::cout<<"Aktualny stan stosu: "<<std::endl;
                this -> showElements();

                std::cout<<std::endl;
                std::cout<<std::endl;
                std::cout<<"Wybierz numer: ";
                std::cin>>x;

                if(x == 1){
                    int data;
                    std::cout<<std::endl;
                    std::cout << "Podaj wartosc ktora chcesz dodac ze stosu: ";
                    std::cin >> data;
                    std::cout << std::endl;

                    this -> push(data);
                }

                else if (x == 2){
                    this -> pop();
                }

                else if (x == 3){

                }

                else {
                    std::cout<<std::endl;
                    std::cout<<"Wybrales zly numer!";
                    std::cout<<std::endl;
                }
        }   }
    };


