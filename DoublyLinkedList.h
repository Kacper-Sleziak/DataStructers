#include <cstdlib>
#include <ctime>

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

    void pushOnRandomPosition(int data){

        srand(time(NULL));
        int x = rand() %5;
        int counter = 0;

        std::cout << std::endl;
        std::cout << "Wylosowana pozycja jest rowna = " << x;

        node = new elementOfList;
        node -> data = data;
        elementOfList * temporary = head;


        if (x >= listSize){     //Jeśli wylosowany numer jest wiekszy od wielkosci listy dodajemy go na niej konieniec
            this->pushEnd(data);
        }

        else if(x == 0){
            this->pushFront(data);
        }

        else {

            while (true) {

                if (counter == x-1) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed dodawanym nodem
                    break;
                }

                temporary = temporary->next;
                counter++;
            }
            elementOfList *helper = temporary->next; //helper to element ktory znajduje sie za elementem losowo dodanym

            node->previous = temporary;
            node->next = helper;

            helper->previous = node;
            temporary->next = node;

            listSize++;
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

    void popFront(){
        if(head == 0){
            std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
        }

        else{
            elementOfList * helper = head;
            head = head ->next;
            head ->previous = 0;
            helper ->next = 0;
            delete helper;
            listSize --;
        }
    }

    void popEnd(){
        if(head == 0){
            std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
        }

        else{
            elementOfList * helper = tail;
            tail = tail -> previous;
            helper -> previous = 0;
            tail -> next = 0;
            delete helper;
            listSize --;
        }
    }

    void popRandomElement(){

        srand(time(NULL));
        int x = rand() %5 + 1;
        int counter = 0;

        elementOfList * elementToDelete = head;

        std::cout<<std::endl;
        std::cout<<"Wielkosc list jest rowna = "<<listSize;

        if (x >= listSize - 1){     //Jeśli wylosowany numer jest wiekszy od wielkosci listy to usuwamy ostatnia liczbe
            this->popEnd();
        }

        else if(x == 0){
            this -> popFront();
        }

        else {
            while (true) {

                if (counter == x) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed nodem
                    break;
                }
                elementToDelete = elementToDelete->next;
                counter++;
            }

            elementToDelete->previous->next = elementToDelete -> next;
            elementToDelete ->next -> previous = elementToDelete -> previous;

            elementToDelete -> next = 0;
            elementToDelete ->previous = 0;
            delete elementToDelete;
            elementToDelete = 0;

            listSize --;
        }
    }

    void menu(){

        int x;

        while (x != 7) {
            std::cout<<std::endl;

            std::cout << "Wcisnij 1 aby dodac element na poczatek listy" << std::endl;
            std::cout << "Wcisnij 2 aby dodac element na koniec listy" << std::endl;
            std::cout << "Wcisnij 3 aby dodac element w losowe miejsce listy" << std::endl;

            std::cout << "Wcisnij 4 aby usunac element z poczataku listy" << std::endl;
            std::cout << "Wcisnij 5 aby usunac element z konca listy" << std::endl;
            std::cout << "Wcisnij 6 aby usunac element z losowego miejsca listy" << std::endl;

            std::cout << "Wcisnij 7 aby wyjsc z programu" << std::endl;

            std::cout << std::endl;
            std::cout << "Aktualny stan drzewa Listy: " << std::endl;

            this->showElements();

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Wybierz numer: ";
            std::cin >> x;

            if (x == 1) {

                int data;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora dodac na poczatek listy: ";
                std::cin >> data;
                std::cout << std::endl;

                this->pushFront(data);
            }

            else if (x == 2) {

                int data;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora dodac na koniec listy: ";
                std::cin >> data;
                std::cout << std::endl;

                this->pushEnd(data);
            }

            else if(x == 3){

                int data;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora dodac w losowe miejsce listy: ";
                std::cin >> data;
                std::cout << std::endl;

                this->pushOnRandomPosition(data);
            }

            else if (x == 4){
                this -> popFront();
            }

            else if(x == 5){
                this -> popEnd();
            }

            else if(x == 6){
                this -> popRandomElement();
            }

            else{
                std::cout<<"Wybrales zly numer!"<<std::endl;
            }
        }

    }
};


