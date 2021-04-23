#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>


class DoublyLinkedList {

    public:
        struct elementOfList {
            int data;
            elementOfList *next;
            elementOfList *previous;
        };

        void listMenu();
        void createListFromFile(std::string file);


    private:
        int listSize = 0;
        elementOfList *node = 0;
        elementOfList *head = 0;
        elementOfList *tail = 0;


        void push(int data, int index);
        void pushEnd(int data);
        void pushFront(int data);
        void pushOnRandomPosition(int data);

        void pop(int data);
        void popFront();
        void popEnd();
        void popRandomElement();

        void showElementsFromHead();
        void showElementsFromTail();

        bool findElement(int data);
};


void DoublyLinkedList::pushEnd(int data){                   //dodajemy ostatni element na koniec listy
    node = new elementOfList;
    node -> data = data;

    if (head == 0){                       //przypadek kiedy dodany wyraz to pierwszy element
        head = node;
        node -> previous = 0;
    }

    else{                                 //pozostale przypadku
        tail -> next = node;
        node -> previous = tail;
    }

    tail = node;
    node -> next = 0;
    this -> listSize ++;
}

void DoublyLinkedList::pushFront(int data){
    node = new elementOfList;
    if (head == 0){
        this -> pushEnd(data);         //gdy dodawany wyraz to pierwszy element listy uzywamy przypadku z funkcji pushBack
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

void DoublyLinkedList::push(int data, int index){
    node = new elementOfList;
    node -> data = data;

    if(index >= listSize){
        this-> pushEnd(data);
    }

    else if(index == 0){
        this->pushFront(data);
    }

    else{
        int counter = 0;
        elementOfList * temporary = head;

        while (true) {

            if (counter == index-1) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed dodawanym nodem
                break;
            }

            temporary = temporary -> next; //element znajdujacy za nowo dodanym nodem
            counter++;
        }
        elementOfList *helper = temporary -> next; //helper to element ktory chwilowo znjaduje sie w miejscu, wktory chcemy dodac element

        node -> previous = temporary;              //proces zmiany pozycji elementu helper w celu dodania nowego elementu na zadana pozycje
        node -> next = helper;

        helper -> previous = node;
        temporary -> next = node;

        listSize++;
    }


}

void DoublyLinkedList::pushOnRandomPosition(int data){

    srand(time(NULL));
    int x = rand() %5;
    int counter = 0;

    std::cout << std::endl;
    std::cout << "Wylosowana pozycja jest rowna = " << x;

    node = new elementOfList;
    node -> data = data;
    elementOfList * temporary = head;


    if (x >= listSize){     //Jeśli wylosowany numer jest wiekszy od wielkosci listy dodajemy go na niej koniec
        this -> pushEnd(data);
    }

    else if(x == 0){
        this -> pushFront(data);
    }

    else {

        while (true) {

            if (counter == x-1) {  //konczymy petle w momencie, ktorym temporary jest elementem znajdującym się przed dodawanym nodem
                break;
            }

            temporary = temporary -> next;
            counter++;
        }
        elementOfList *helper = temporary -> next; //helper to element ktory znajduje sie za elementem losowo dodanym

        node -> previous = temporary;
        node -> next = helper;

        helper -> previous = node;
        temporary -> next = node;

        listSize++;
    }

}

void DoublyLinkedList::showElementsFromHead(){

    if (head != 0) {

        elementOfList *actualElement = head;
        int data = actualElement -> data;
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

            actualElement = actualElement -> next;
            data = actualElement -> data;
        }
    }



    else{
        std::cout<<"Lista jest pusta!";
    }
}

void DoublyLinkedList::showElementsFromTail() {

    if (head != 0) {

        elementOfList *actualElement = tail;
        int data = actualElement -> data;
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

            actualElement = actualElement -> previous;
            data = actualElement -> data;
        }
    }

    else{
        std::cout<<"Lista jest pusta!";
    }
}

void DoublyLinkedList::popFront(){

    if(listSize == 0){
        std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
    }

    else if(listSize == 1){
        this -> popEnd();
    }

    else{
        elementOfList * helper = head;
        head = head ->next;
        head ->previous = 0;
        helper -> next = 0;
        delete helper;
        this -> listSize --;
    }
}

void DoublyLinkedList::popEnd(){

    if(listSize == 0){
        std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
    }

    else if(listSize == 1){                                 //przypadek kiedy usywamy ostatni element
        elementOfList *helper;
        helper = this -> head;
        head = 0;
        tail = 0;

        delete helper;
        this -> listSize --;
    }

    else{
        elementOfList * helper = tail;
        tail = tail -> previous;
        helper -> previous = 0;
        tail -> next = 0;
        delete helper;
        this -> listSize --;
    }
}

void DoublyLinkedList::popRandomElement(){

    srand(time(NULL));
    int x = rand() %500000 + 1;
    int counter = 0;

    elementOfList * elementToDelete = head;

    std::cout<<std::endl;
    std::cout<<"Wielkosc list jest rowna = "<<this -> listSize;

    if(head == 0){
        std::cout<<"Nie moża wykonać operacji usuwania ponieważ lista jest pusta!";
    }

    else {

        if (x >=this -> listSize - 1) {     //Jeśli wylosowany numer jest wiekszy od wielkosci listy to usuwamy ostatnia liczbe
            this -> popEnd();
        }

        else if (x == 0) {          //jesli wylosowany emenet jest glowa
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

            elementToDelete->previous->next = elementToDelete->next;
            elementToDelete->next->previous = elementToDelete->previous;

            elementToDelete->next = 0;
            elementToDelete->previous = 0;
            delete elementToDelete;
            elementToDelete = 0;

            this -> listSize--;
        }
    }
}

void DoublyLinkedList::pop(int data){

    if (listSize == 0){
        std::cout<<"Lista jest pusta!"<<std::endl;
    }

    else {
        elementOfList *temporary = head;

        while (true) {

            if (temporary -> data == data) {

                if (listSize == 1) {
                    this -> popEnd();
                    break;
                }

                else if (temporary == head) {
                    this -> popFront();
                    break;
                }

                else if (temporary == tail) {
                    this->popEnd();
                    break;
                }

                else {
                    temporary->previous->next = temporary->next;
                    temporary->next->previous = temporary->previous;
                    temporary->previous = 0;
                    temporary->next = 0;
                    delete temporary;
                    this -> listSize--;
                    break;
                }
            }

            temporary = temporary->next;

            if (temporary == 0) {
                std::cout << "Nie znaleziono takiego elementu!";
                break;
            }
        }
    }

}

bool DoublyLinkedList::findElement(int data){
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

void DoublyLinkedList::createListFromFile(std::string file) {

    std::fstream myfile(file, std::ios_base::in);

    int data;
    while (myfile >> data)
        //while (myfile.good())
    {
        if (!myfile.fail()) {
            this -> pushEnd(data);
        }

        else {
            break;
        }
    }
}

void DoublyLinkedList::listMenu(){

    int x;

    while (x != 6) {
        std::cout<<std::endl;
        std::cout << "Wcisnij 0 aby stworzyc liste z pliku" << std::endl;
        std::cout << "Wcisnij 1 aby znalezc element o podanej wartosci" << std::endl;
        std::cout << "Wcisnij 2 aby dodac element na zadana pozycje" << std::endl;
        std::cout << "Wcisnij 3 aby usunac podana wartosc" << std::endl;
        std::cout << "Wcisnij 4 aby wyjsc z programu" << std::endl;

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

        if (x == 0) {
            std::string file;
            std::cout << std::endl;
            std::cout << "Podaj plik, z ktorgo chcesz stworzyc drzewo: ";
            std::cin >> file;
            std::cout << std::endl;

            this->createListFromFile(file);
        }

        else if(x == 1){
            int data;

            std::cout << std::endl;
            std::cout << "Podaj wartosc elementy ktory chcesz znalezc: ";
            std::cin >> data;

            if(this->findElement(data) == true){

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

        else if(x == 2){

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

        else if (x == 3) {

            int data;
            std::cout << std::endl;
            std::cout << "Podaj wartosc ktora chcesz usunac: ";
            std::cin >> data;
            std::cout << std::endl;

            this->pop(data);
        }

        else if (x == 4){
            std::cout<<std::endl;
        }

        else{
            std::cout<<"Wybrales zly numer!"<<std::endl;
        }
    }

}


