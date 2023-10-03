#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    string plakaKodu;
    Node* sol;
    Node* sag;

    Node(const string& plaka) : plakaKodu(plaka), sol(nullptr), sag(nullptr) {}

};

void AgacaEkle(Node*& kok, const string& plaka) {
    if (kok == nullptr) {
        kok = new Node(plaka);
        return;
    }

    if (plaka < kok->plakaKodu) {
        AgacaEkle(kok->sol, plaka );
    }
    else {
        AgacaEkle(kok->sag, plaka);
    }
}

void AgaciYazdir(Node* kok, const string& prefix = "") {
    if (kok == nullptr)
        return;

    cout << prefix;
    cout << (kok->sag != nullptr && kok->sol != nullptr ? "L--" : "L--");

    cout << kok->plakaKodu << endl;

    if (kok->sol != nullptr) {
        AgaciYazdir(kok->sol, prefix + "    |");
    }

    if (kok->sag != nullptr) {
        AgaciYazdir(kok->sag, prefix + "    ");
    }
}

int AgacinDerinligi(Node* kok) {
    if (kok == nullptr)
        return 0;

    int solDerinlik = AgacinDerinligi(kok->sol);
    int sagDerinlik = AgacinDerinligi(kok->sag);

    return max(solDerinlik, sagDerinlik) + 1;
}

bool AgacDenge(Node* kok) {
    if (kok == nullptr)
        return true;

    int solDerinlik = AgacinDerinligi(kok->sol);
    int sagDerinlik = AgacinDerinligi(kok->sag);

    int derinlikFarki = abs(solDerinlik - sagDerinlik);

    if (derinlikFarki > 1)
        return false;

    return AgacDenge(kok->sol) && AgacDenge(kok->sag);
}

Node* AgacAra(Node* kok, const string& plaka) {
    if (kok == nullptr || kok->plakaKodu == plaka)
        return kok;

    if (plaka < kok->plakaKodu)
        return AgacAra(kok->sol, plaka);
    else
        return AgacAra(kok->sag, plaka);
}

int DuzeyFarki(Node* kok, const string& plaka1, const string& plaka2) {
    Node* node1 = AgacAra(kok, plaka1);
    Node* node2 = AgacAra(kok, plaka2);

    if (node1 == nullptr || node2 == nullptr)
        return -1;


    Node* ortakAta = kok;
    while (ortakAta != nullptr) {
        if (ortakAta->plakaKodu > plaka1 && ortakAta->plakaKodu > plaka2)
            ortakAta = ortakAta->sol;
        else if (ortakAta->plakaKodu < plaka1 && ortakAta->plakaKodu < plaka2)
            ortakAta = ortakAta->sag;
        else
            break;
    }

    if (ortakAta == nullptr)
        return -1;

    int duzey1 = 0;
    Node* temp = ortakAta;
    while (temp->plakaKodu != plaka1) {
        if (plaka1 < temp->plakaKodu) {
            temp = temp->sol;
        }
        else {
            temp = temp->sag;
        }
        duzey1++;
    }

    int duzey2 = 0;
    temp = ortakAta;
    while (temp->plakaKodu != plaka2) {
        if (plaka2 < temp->plakaKodu) {
            temp = temp->sol;
        }
        else {
            temp = temp->sag;
        }
        duzey2++;
    }

    return abs(duzey1 - duzey2);
}


//Preorder , Postorder , Inorder

void PreorderYazdir(Node* kok) {
    if (kok == nullptr)
        return;

    cout << kok->plakaKodu << " - ";;
    PreorderYazdir(kok->sol);
    PreorderYazdir(kok->sag);
}

void InorderYazdir(Node* kok) {
    if (kok == nullptr)
        return;

    InorderYazdir(kok->sol);
    cout << kok->plakaKodu << " - ";;
    InorderYazdir(kok->sag);
}

void PostorderYazdir(Node* kok) {
    if (kok == nullptr)
        return;

    PostorderYazdir(kok->sol);
    PostorderYazdir(kok->sag);
    cout << kok->plakaKodu << " - ";
}

//Agaci temizleme 
void AgaciTemizle(Node* kok) {
    if (kok != nullptr) {
        AgaciTemizle(kok->sol);
        AgaciTemizle(kok->sag);
        delete kok;
    }
}



int main() {
    const int MAX_SEHIR_SAYISI = 100; // Depolamak istediðiniz maksimum þehir sayýsý

    ifstream dosya("sehir_plaka_kodlari.txt");

    if (!dosya.is_open()) {
        cout << "Dosya acilamadi." << endl;
        return 1;
    }

    string sehirler[MAX_SEHIR_SAYISI][2]; // Ýki boyutlu dizi 
    int sehirSayisi = 0; // Toplam þehir sayýsý

    string satir;

    while (getline(dosya, satir)) {
        stringstream ss(satir);
        string plakaKodu, sehirAdi;

        getline(ss, plakaKodu, ',');
        getline(ss, sehirAdi);

        sehirler[sehirSayisi][0] = plakaKodu;
        sehirler[sehirSayisi][1] = sehirAdi;

        sehirSayisi++;
    }

    dosya.close();


    Node* kok = nullptr;
    int plakaSayisi = sehirSayisi;
    for (int i = 0; i < plakaSayisi; i++) {
        AgacaEkle(kok, sehirler[i][0]);
    }

    int derinlik = AgacinDerinligi(kok);
    cout << "Agacin Derinligi: " << derinlik << endl;

    bool dengeliMi = AgacDenge(kok);
    cout << "Agac " << (dengeliMi ? "dengeli" : "dengesiz") << endl;
    
    AgaciYazdir(kok);
    cout << endl;



    //Arama

    string plaka1, plaka2;
    cout << "Birinci plaka kodunu girin: ";
    cin >> plaka1;

    cout << "Ikinci plaka kodunu girin: ";
    cin >> plaka2;

    cout << endl;

    

    Node* node1 = AgacAra(kok, plaka1);
    Node* node2 = AgacAra(kok, plaka2);

    if (node1 != nullptr && node2 != nullptr) {
        
        for (int i = 0; i < sehirSayisi; i++) {
            if (plaka1 == sehirler[i][0])
            {
                cout << "Plaka kodu: " << plaka1 << ", Sehir: " << sehirler[i][1] << endl;
            }
            if (plaka2 == sehirler[i][0])
            {
                cout << "Plaka kodu: " << plaka2 << ", Sehir: " << sehirler[i][1] << endl;
            }
        }

        int duzeyFarki = DuzeyFarki(kok, plaka1, plaka2);
        if (duzeyFarki != -1) {
            cout << "Duzey farki: " << duzeyFarki << endl;
        }
        else {
            cout << "Belirtilen plaka kodlari agacta bulunamadi." << endl;
        }
    }
    else {
        cout << "Belirtilen plaka kodlari agacta bulunamadi." << endl;
    }

    cout << endl;

    cout << "Preorder Siralamasi:" << endl;
    PreorderYazdir(kok);

    cout << endl;

    cout << "\nInorder Siralamasi:" << endl;
    InorderYazdir(kok);

    cout << endl;

    cout << "\nPostorder Siralamasi:" << endl;
    PostorderYazdir(kok);

    cout << endl;

    // Bellek temizleme
    AgaciTemizle(kok);


    return 0;
}
