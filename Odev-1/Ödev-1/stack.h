#pragma once
#include <iostream>

using namespace std;



struct eleman {
    int veri;
    eleman* sonraki;
};


int stackboyutu = 0;

class Stack {
    eleman* ust = new eleman;
    int stackboyutu = 0;
private:

public:

    //stack e ekleme 
    void push(int data)
    {

        eleman* yeni = new eleman;
        yeni->veri = data;
        yeni->sonraki = ust;
        ust = yeni;
        //cout << data << " stack'e eklendi." << endl;
        stackboyutu++;
    }

    //Stackten cikarma
    void pop()
    {
        if (stackboyutu != 0)
        {
           // cout << "Eleman: " << ust->veri << " silindi." << endl;
            ust = ust->sonraki;
            stackboyutu--;
        }
        else cout << "Stack bos!" << endl;
    }

    //Stack e en son eklenen veriyi dondurur
    int top() {
        return ust->veri;
    }

    int temp;

    
    //Stack in bos olup olamdigini kontrol eder.
    bool empty() {
        if (ust->veri < 0 || ust == NULL) {
            
            return true;
        }
        return false;
    }
};
