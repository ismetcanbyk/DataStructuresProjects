#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include "stack.h"




Stack s1,s2;

void randomTime(int kisiSayisi , int kisiIslem[]) {
	int random;
	
	srand(time(0));
	
	for (int i = 0; i < kisiSayisi; i++) {
		random = 30 + (rand() % 270);
		kisiIslem[i] = random;
	}
}

void enQueue(int data)
{
	s1.push(data);
}


int deQueue()
{
	// iki stackin bos olma durumu
	if (s1.empty() && s2.empty()) {
		cout << "Butun islemler bitti !";
		exit(0);
	}

	// s2 bossa s1 i s2 ye tasir
	if (s2.empty()) {
		while (!s1.empty()) {
			s2.push(s1.ust());
			s1.pop();
		}
	}

	//x s2 nin degerlerini doner
	int x = s2.ust();
	s2.pop();
	return 0;
};




int main() {
	int kisiSayisi ;
	int topSure = 0;
	
	cout << "Kisi Sayisi : ";
	cin >> kisiSayisi;

	int* kisiIslem = new int[kisiSayisi];
	
	randomTime(kisiSayisi, kisiIslem);

	


	cout << endl;

	cout << "Sira Bekleyen Kisiler";

	cout << endl << endl;
	
	for (int i = 0; i < kisiSayisi; i++)
	{
		cout << "kisi id : " << i << "  islem suresi : " << kisiIslem[i] << endl;
		
	}

	for (int i = 0; i <kisiSayisi ; i++)
	{
		enQueue(kisiIslem[i]);
		topSure += kisiIslem[i];
	}

	
	cout << endl;

	s1.sorting(kisiSayisi);

	cout << endl;
	cout << "top islem suresi : " << topSure << endl;
	cout << endl;

	cout << "Ortalama islem suresi : " << topSure / kisiSayisi << endl;
	cout << endl;

	cout << endl;

	for (int i = 0; i < kisiSayisi; i++)
	{
		deQueue();
	}

	


	return 0;
};








