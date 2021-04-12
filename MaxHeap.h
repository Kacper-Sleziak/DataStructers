#include <iostream>

class MaxHeap {

    public:

        int hSize = 0;
        int * tab = new int[hSize];
        int i = 0;

        void push(int data) {
            hSize ++;
            tab[i] = data;


            if (i != 0) {    //sortowanie jeśli wyraz tab[i] nie jest korzeniem
                int parentIndex = (i-1)/2;
                int kidIndex = i;

                while (true) {
                        if (!isKidGraterThanParent(tab[parentIndex], tab[kidIndex])) {
                            break;
                        }

                        int helper;
                        helper = tab[parentIndex];
                        tab[parentIndex] = tab[kidIndex];
                        tab[kidIndex] = helper;

                        kidIndex = parentIndex;

                        if(kidIndex <= 0){
                            break;
                        }

                        parentIndex = (kidIndex - 1)/2;
                }
            }

                i++;
        }

        void showElements(){

            if (hSize == 0){
                std::cout<<"Kopiec jest Pusty!";
            }
            else{
                for (int j = 0; j < hSize; j++) {
                    std::cout << "Array[" << j << "] = ";
                    std::cout << tab[j];
                    std::cout << "  ";

                }
            }
        }

        bool isKidGraterThanParent(int parent, int kid){
            if (kid > parent){
                return true;
            }

            else{
                return false;
            }
        }


        int pop(int index){
            if(index == i){
                hSize --;
            }
            else if(hSize == 0){
                std::cout<<"Kopiec jest pusty!";
            }

            else{
                tab[index] = tab[i-1];
                i--;
                hSize --;

                int parentIndex = index;
                int leftKidIndex = 2*index + 1;
                int rightKidIndex = 2*index + 2;

                std::cout<<std::endl;
                std::cout<<tab[parentIndex]<<std::endl;
                std::cout<<tab[leftKidIndex]<<std::endl;
                std::cout<<tab[rightKidIndex]<<std::endl;

                while (true){

                    if (leftKidIndex >= hSize){
                        break;
                    }

                    int graterKidIndex;

                    if(rightKidIndex >= hSize){
                        graterKidIndex = leftKidIndex;
                    }

                    else if (tab[leftKidIndex] >= tab[rightKidIndex]){
                        graterKidIndex = leftKidIndex;
                    }

                    else{
                        graterKidIndex = rightKidIndex;
                    }

                    if(!isKidGraterThanParent(tab[parentIndex], tab[graterKidIndex])){
                        break;
                    }

                    std::cout<<tab[parentIndex]<<std::endl;
                    std::cout<<tab[graterKidIndex]<<std::endl;

                    int helper;
                    tab[parentIndex] = tab[graterKidIndex];


                    parentIndex = graterKidIndex;
                    leftKidIndex = 2*index + 1;
                    rightKidIndex = 2*index +2;
                }

            }
        }

        void menu(){

            int x;

            while (x != 3) {
                std::cout << "Wcisnij 1 aby dodac element do kopca" << std::endl;
                std::cout << "Wcisnij 2 aby usunac element z kopca" << std::endl;
                std::cout << "Wcisnij 3 aby wyjsc z programu" << std::endl;

                std::cout << std::endl;
                std::cout << "Aktualny stan kopca : " << std::endl;
                this->showElements();

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

                    this->push(data);
                }

                else if (x == 2) {
                    int data;
                    std::cout << std::endl;
                    std::cout << "Podaj index elementu, ktory chcesz usunac z kopca ";
                    std::cin >> data;
                    std::cout << std::endl;

                    this->pop(data);
                }

                else if(x == 3){
                }

                else{
                    std::cout<<"Wybrales zly numer!"<<std::endl;
                }
            }

        }
};




