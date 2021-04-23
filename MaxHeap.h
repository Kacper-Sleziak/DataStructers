#include <iostream>
#include <math.h>
#include <fstream>

class MaxHeap {

    public:
        void heapMenu();
        void createHeapFromFile(std::string file);

    private:
        int hSize = 0;
        int *array;
        int i = 0;

    void push(int data);
    void showElements();
    bool isKidGraterThanParent(int parent, int kid);
    void pop(int index);
    bool findElement(int data);

};

void MaxHeap::push(int data) {

    hSize ++;

    if (hSize == 1){                                                 //kiedy lista jest pusta tworzymy nowy wyraz
        this->array = new int[this->hSize];
        array[i] = data;
    }

    else {
        array[i] = data;

        int *previouPointer = this -> array;                           //rekolacja tablicy
        int *newPointer = new int[this -> hSize];
        this->array = newPointer;

        memcpy(this -> array, previouPointer, hSize * sizeof(int));

        delete[] previouPointer;
        previouPointer = 0;
        newPointer = 0;

        if (this->i != 0) {                                     //sortowanie jeśli wyraz array[i] nie jest korzeniem
            int parentIndex = (this -> i - 1) / 2;
            int kidIndex = this -> i;

            while (true) {
                if (!isKidGraterThanParent(array[parentIndex], array[kidIndex])) {
                    std::cout<<"xd1"<<std::endl;
                    break;
                }

                int helper;                                         //zamiana miejscami dziecka z rodzicem
                helper = array[parentIndex];
                array[parentIndex] = array[kidIndex];
                array[kidIndex] = helper;

                kidIndex = parentIndex;

                if (kidIndex <= 0) {//kiedy dziecko jest korzeniem koczymy
                    break;
                }
                parentIndex = (kidIndex - 1) / 2;
            }
        }
    }
        i++;
}

void MaxHeap::showElements(){

    if (hSize == 0){
        std::cout<<"Kopiec jest Pusty!";
    }
    else{
        for (int j = 0; j < hSize; j++) {
            std::cout << array[j];
            std::cout << "  ";
        }
    }
}

bool MaxHeap::isKidGraterThanParent(int parent, int kid){
    if (kid > parent){
        return true;
    }

    else{
        return false;
    }
}


void MaxHeap::pop(int index){

    if (hSize <= 0){
        std::cout<<"Kopiec jest pusty!";
    }

    else{
        int *newArray = new int[this -> hSize - 1 ];

        if(index >= i-1){                           //w przypadku gdy index elementu do usniecia jest wiekszy
        }                                           //badz rowny najwyzszemu indeksowi
                                                    //to usuwamy ostatni element kopca
        else{
            array[index] = array[i - 1];

            int parentIndex = index;
            int leftKidIndex = 2 * index + 1;
            int rightKidIndex = 2 * index + 2;

            int graterKidIndex;

            while (true) {

                if(rightKidIndex >= this -> i-1 and leftKidIndex >= this -> i-1){       //kiedy nie ma juz wartości do porównywania
                    break;
                }

                if (rightKidIndex > this -> i - 1) {                        //przypadek kiedy prawe dziecko nie istnieje
                    graterKidIndex = leftKidIndex;
                }

                else if (array[leftKidIndex] >= array[rightKidIndex]){
                    graterKidIndex = leftKidIndex;
                }

                else {
                    graterKidIndex = rightKidIndex;
                }

                if (!isKidGraterThanParent(array[parentIndex], array[graterKidIndex])) {    //przypadek kiedy dzieci sa w koncu mniejsze od rodzica
                    break;
                }


                int helper = array[parentIndex];
                array[parentIndex] = array[graterKidIndex];
                array[graterKidIndex] = helper;


                parentIndex = graterKidIndex;                   //po zamianie miejsce
                leftKidIndex = 2 * parentIndex + 1;             //index wiekszego dziecka to teraz index rodzica
                rightKidIndex = 2 * parentIndex + 2;            //obliczamy indexy dzieic nowego rodzica

            }
        }

        for(int i=0; i<hSize-1; i++){               //kopiujemy elementy do nowo relakowanej tablicy
            newArray[i] = this->array[i];
        }

        int *oldArray = this -> array;                //ustawiamy nowa tablice kopca
        this -> array = newArray;

        delete oldArray;
        this -> hSize--;
        this -> i--;
    }
}

void MaxHeap::createHeapFromFile(std::string file) {

std::fstream myfile(file, std::ios_base::in);

int data;
while (myfile >> data)
{
    if (!myfile.fail()) {
        this -> push(data);
    }

    else {
        break;
    }
}
}

bool MaxHeap::findElement(int data){
    for(int i=0 ; i< this -> hSize; i++){
        if(array[i] == data)
            return true;
        }
    return false;
}


void MaxHeap::heapMenu(){
    int x;

    while (x != 4) {
        std::cout << "Wcisnij 1 aby dodac element do kopca" << std::endl;
        std::cout << "Wcisnij 2 aby usunac element z kopca" << std::endl;
        std::cout << "Wcisnij 3 aby znalezc element" << std::endl;
        std::cout << "Wcisnij 4 aby wyjsc z programu" << std::endl;

        std::cout << std::endl;
        std::cout << "index: " << this -> i <<std::endl;
        std::cout << "Aktualny stan kopca: " << std::endl;
        this -> showElements();

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Wybierz numer: ";
        std::cin >> x;


        if (x == 1) {
            int data;
            std::cout << std::endl;
            std::cout << "Podaj wartosc ktora chcesz dodac do kopca: ";
            std::cin >> data;
            std::cout << std::endl;

            this -> push(data);
        }

        else if (x == 2) {
            int data;
            std::cout << std::endl;
            std::cout << "Podaj index: ";
            std::cin >> data;
            std::cout << std::endl;

            this->pop(data);
        }

        else if(x == 3){
            int data;
            std::cout << std::endl;
            std::cout << "wartosc elementu, ktory chcesz znalezc ";
            std::cin >> data;
            std::cout << std::endl;

            if (this->findElement(data) == true){
                std::cout<<"Znaleziono Element";
                std::cout << std::endl;
                std::cout << std::endl;
            }

            else{
                std::cout<<"Nie Znaleziono Elementu!";
                std::cout << std::endl;
                std::cout << std::endl;
            }

        }

        else if(x == 4){
        }

        else{
            std::cout<<"Wybrales zly numer!"<<std::endl;
        }
    }

}





