#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 100;



int stackboyutu = 0;

class Stack {
    int top; // Y���n�n en �st�ndeki eleman�n indeksi
    int data[MAX_SIZE]; // Y���n�n elemanlar�n� depolamak i�in dizi
private:
  
    public:


    void push(int value)
    {

        if (top >= MAX_SIZE - 1) { // Y���n dolu ise hata mesaj� yazd�r
            cout << "HATA: Y���n dolu!\n";
        }
        else {
            top++;
            data[top] = value;
            //cout << "eklendi : " << data[top]<<endl;
        }

        stackboyutu++;
    }
    void pop()
    {
        if (top < 0) { // Y���n bo� ise 
           
        }
        else {
            int value = data[top];
           // cout << "islemi bitti  : " << data[top]<<endl;
            top--;
        }
    }

    int ust() {
        return data[top];
    }

    int temp;

    void sorting(int length) 
    {
        int n = length;
        int* templ = new int[length];

        // orijinal dizinin elemanlar�n� ge�ici diziye kopyalama

        for (int i = 0; i < length; i++)
        {
            templ[i] = data[i+1];
        }
        
        // ge�ici diziyi s�rala
        sort(templ, templ + n);

        int topSure = 0;
 
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if (templ[i] == data[j+1]) {
                    topSure += data[j + 1];
                    cout << j  << "  nolu id ye sahip kisinin suresi : " << data[j + 1] << " ---> islem suresi : "<<topSure << endl;
                   
                    pop();
                    
                }
            }
        }
    }

  

    bool empty() {
        if (top < 0 || top == NULL) {
          
            return true;
        }
        return false;
    }
};



