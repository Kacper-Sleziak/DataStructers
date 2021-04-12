#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

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

    void push(int data, int index){
        node = new elementOfList;
        node -> data = data;

        if(index >= listSize){
            this-> pushEnd(data);
        }

        else{
            int counter = 0;
            elementOfList * temporary = head;

            while (true) {

                if (counter == index-1) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed dodawanym nodem
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

    void showElementsFromHead(){

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

    void showElementsFromTail() {

        if (head != 0) {

            elementOfList *actualElement = tail;
            int data = actualElement->data;
            std::cout << std::endl;

            std::cout << "----" << std::endl;

            while (true) {
                std::cout << data;
                std::cout << " ";

                if (actualElement->previous == 0) {
                    std::cout << std::endl;
                    std::cout << "----";
                    break;
                }

                actualElement = actualElement->previous;
                data = actualElement->data;
            }
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

        if(head == 0){
            std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
        }

        else {

            if (x >=listSize - 1) {     //Jeśli wylosowany numer jest wiekszy od wielkosci listy to usuwamy ostatnia liczbe
                this->popEnd();
            }
            else if (x == 0) {          //jesli wylosowany emenet jest glowa
                this->popFront();
            }

            else {
                while (true) {

                    if (counter == x) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed nodem
                        break;
                    }

                    elementToDelete = elementToDelete->next;
                    counter++;
                }

                elementToDelete->previous->next = elementToDelete->next;
                elementToDelete->next->previous = elementToDelete->previous;

                elementToDelete->next = 0;
                elementToDelete->previous = 0;
                delete elementToDelete;
                elementToDelete = 0;

                listSize--;
            }
        }
    }

    void pop(int data){

        elementOfList * temporary = head;

        while (true){

            if(temporary -> data == data){

                if(temporary == head){
                    this -> popFront();
                    break;
                }

                else if (temporary == tail){
                    this -> popEnd();
                    break;
                }

                else{

                    temporary->previous->next = temporary->next;
                    temporary->next->previous = temporary->previous;
                    temporary->previous = 0;
                    temporary->next = 0;
                    delete temporary;
                    listSize--;
                    break;
                }
            }

            temporary = temporary -> next;

            if(temporary == 0){
                std::cout<<"Nie znaleziono!";
                break;
            }

        }


    }

    bool finElement(int data){
        elementOfList * temporary = head;

        while (true){
            if (temporary -> data == data){
                return true;
            }
            temporary = temporary -> next;

            if (temporary == 0){
                break;
            }
        }
        return false;
    }

    void createListFromFile(std::string file){

        std::fstream myfile(file, std::ios_base::in);

        int data;
        while (myfile >> data)
        //while (myfile.good())
        {
            if(data != '*'){

                this->pushEnd(data);
            }

            else {
                break;
            }
        }
        getchar();
    }

    void menu(){

        int x;

        while (x != 10) {
            std::cout<<std::endl;

            std::cout << "Wcisnij 1 aby dodac element na poczatek listy" << std::endl;
            std::cout << "Wcisnij 2 aby dodac element na koniec listy" << std::endl;
            std::cout << "Wcisnij 3 aby dodac element w losowe miejsce listy" << std::endl;

            std::cout << "Wcisnij 4 aby usunac element z poczataku listy" << std::endl;
            std::cout << "Wcisnij 5 aby usunac element z konca listy" << std::endl;
            std::cout << "Wcisnij 6 aby usunac element z losowego miejsca listy" << std::endl;

            std::cout << "Wcisnij 7 aby znalezc element o podanej wartosci" << std::endl;

            std::cout << "Wcisnij 8 aby dodac element na zadana pozycje" << std::endl;

            std::cout << "Wcisnij 9 aby usunac podana wartosc" << std::endl;

            std::cout << "Wcisnij 10 aby wyjsc z programu" << std::endl;

            std::cout << std::endl;
            std::cout << "Aktualny stan listy od przodu: ";
            this->showElementsFromHead();

            std::cout<<std::endl;
            std::cout << "Aktualny stan listy od tylu: ";
            this->showElementsFromTail();

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

            else if(x == 7){
                int data;

                std::cout << std::endl;
                std::cout << "Podaj wartosc elementy ktory chcesz znalezc: ";
                std::cin >> data;

                if( this -> finElement(data) == true){

                    std::cout<<std::endl;
                    std::cout << "Znaleziono Element";
                    std::cout<<std::endl;
                }

                else{

                    std::cout<<std::endl;
                    std::cout << "Nie Znaleziono Elementu!";
                    std::cout<<std::endl;
                }
            }

            else if(x == 8){

                int data;
                int index;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora chcesz dodac: ";
                std::cin >> data;
                std::cout << std::endl;
                std::cout << "Podaj index: ";
                std::cin >> index;
                std::cout << std::endl;

                this->push(data, index);
            }

            else if (x == 9) {

                int data;
                std::cout << std::endl;
                std::cout << "Podaj wartosc ktora chcesz usunac: ";
                std::cin >> data;
                std::cout << std::endl;

                this->pop(data);
            }

            else if (x == 10){

            }

            else{
                std::cout<<"Wybrales zly numer!"<<std::endl;
            }
        }

    }
};


