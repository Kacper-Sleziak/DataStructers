#include "iostream"
//Klasa nie zawiera funkcji usuwania ostatniego oraz pierwszego elementu tablice
//nie zawiera rowniez dodawania elementu na pierwsza pozycje
//aby wykonać tego typu dzialania mozemy uzyc funkcji addByIndex oraz deleteByIndex poprzez nadanie odpowiednich argumentów

class Array {

    public:
        void arrayMenu();
        void createArrayFromFile(std::string file);

    private:
        int aSize;          //Wielkosc tablicy zadeklarowana przy jej tworzeniu
        int currentSize = 0;   //Aktualna wielkosc tablicy
        int *arr;

    void addEnd(int data);
    void showElements();
    void findElement(int data);
    void addByIndex(int data, int index);
    void deleteByIndex(int index);
};

void Array::addEnd(int data){
    this->currentSize++;

    if(currentSize == 1){
        this -> arr = new int[this -> currentSize];
    }

    else{
        int *previouPointer = this -> arr;
        int *newPointer = new int[this -> currentSize];
        this -> arr = newPointer;

        memcpy(this -> arr, previouPointer, currentSize * sizeof(int)); //wskaznik

        delete [] previouPointer;
        previouPointer = 0;
        newPointer = 0;
    }

    this -> arr[this -> currentSize - 1] = data;

}

void Array::showElements(){
    for (int i = 0; i < this ->  currentSize; i++){
        std::cout<<this -> arr[i]<<", ";
    }
}

void Array::findElement(int data){

    int helper = 0;

    for (int i = 0; i<this -> currentSize; i++){
        if (this -> arr[i] == data){
            helper = 1;
            std::cout<<"Znaleziono Element";
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
    }

    if (helper == 0){
        std::cout<<"Nie ma takiego elementu!";
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
}

void Array::addByIndex(int data, int index){

    if(this -> currentSize == 0){    //przypadek kiedy tablica jest pusta i odwolujemy sie do funkcji addEnd
        this -> addEnd(data);
    }

    else if(index < this -> currentSize){   //przypadek gdy chcemy dodac element na miejsce na, ktorym znajduje sie inny element
        currentSize ++;

        int *previouPointer = this -> arr;
        int *newPointer = new int[this -> currentSize];
        this -> arr = newPointer;

        memcpy(this -> arr, previouPointer, currentSize * sizeof(int)); //wskaznik

        delete [] previouPointer;
        previouPointer = 0;
        newPointer = 0;

        for(int i = currentSize-1; i>=index ; i--){
            this -> arr[i] = this -> arr[i-1];
        }

        arr[index] = data;
    }

    else {               //przypadek kiedy dodajemy element na miejsce, ktore nie jest aktualnie zajete
        this -> addEnd(data);
    }

}

void Array::deleteByIndex(int index){
    if (index >= this -> aSize or index >= this -> currentSize){
        std::cout<<"Index poza zakresem!";
    }

    else{

        int *previouPointer = this -> arr;                    //ustawiamy wskaznik na obcecma talblice
        this -> currentSize --;                                     //zmiejszamy wielkosc o 1
        int *newPointer = new int[this -> currentSize];     //tworzymy nowa tablice o 1 mniejsza
        this -> arr = newPointer;                             //do wskaznika arr przypisujemy wskaznik na nowa pomniejszona tablice


                                                    //kopiujemy wszystkie elementy nowej tablicy do starej z wylaczeniem
        for(int i = index; i < this -> currentSize ; i++) { //z wylaczeniem usnietego elementu
            this -> arr[i] = previouPointer[i + 1];
        }

        for(int i = 0; i < index ; i++) {
            this -> arr[i] = previouPointer[i];
        }
            delete [] previouPointer;
            previouPointer = 0;
            newPointer = 0;
        }
    }

void Array::createArrayFromFile(std::string file) {

    std::fstream myfile(file, std::ios_base::in);

    int data;
    while (myfile >> data)
        //while (myfile.good())
    {
        if (!myfile.fail()) {
            this -> addEnd(data);
        }

        else {
            break;
        }
    }
}


void Array::arrayMenu(){
    int x;
    while (x != 5) {
        std::cout << "Wcisnij 0 aby stworzyc liste z pliku" << std::endl;
        std::cout << "Wcisnij 1 aby dodac element" << std::endl;
        std::cout << "Wcisnij 2 aby znalezc element" << std::endl;
        std::cout << "Wcisnij 3 aby dodac element na zadana pozycje" << std::endl;
        std::cout << "Wcisnij 4 aby usunac element po zadanym indexie" << std::endl;
        std::cout << "Wcisnij 5 aby zakonczyc program" << std::endl;


        std::cout << std::endl;
        std::cout << "Aktualn wielkosc tablicy: " << this -> currentSize<<std::endl;
        std::cout << "Aktualny stan tablicy od przodu: " << std::endl;
        this -> showElements();

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

            this -> createArrayFromFile(file);
        }

        if (x == 1) {
            int data;
            std::cout << std::endl;
            std::cout << "Podaj wartosc ktora chcesz dodac: ";
            std::cin >> data;
            std::cout << std::endl;

            this -> addEnd(data);
        }

        else if (x == 2) {
            int data;
            std::cout << std::endl;
            std::cout << "Podaj wartosc ktora chcesz znalezc: ";
            std::cin >> data;
            std::cout << std::endl;

            this -> findElement(data);
        }

        else if(x == 3){
            int data;
            int index;
            std::cout << std::endl;
            std::cout << "Podaj index: ";
            std::cin >> index;
            std::cout<<std::endl;

            std::cout << "Podaj wartosc: ";
            std::cin >> data;
            std::cout << std::endl;

            this -> addByIndex(data, index);
        }

        else if(x==4){
            int index;
            std::cout << std::endl;
            std::cout << "Podaj index: ";
            std::cin >> index;
            std::cout<<std::endl;

            this -> deleteByIndex(index);
        }

        else if(x == 5){

        }

        else{
            std::cout<<"Wybierz prawidlowy numer!";
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
     }
}
