#include <iostream>
#include <fstream>
using namespace std;
struct Fuvar {
    int nap;
    int sorsz;
    int tavolsag;
};

class Feldolgoz
{
    private :
        // Fuvarok tömbje
        Fuvar fuvarok[100];
        // hány elem van a tömben
        int db = 0;

        string napok [8];
        int naponkentiDb[8];


        void szamolNapokat()
        {
            // ki 0-azuk a napokat
            for (int i = 1; i<=7; i++){
                naponkentiDb[i] = 0;
            }
         
            for (int i = 0; i<db; i++){
                naponkentiDb[fuvarok[i].nap] ++;
            }
        }

    public:
        Feldolgoz(); 
        void beolvas() {
            ifstream be("utak.txt");
            if (be.fail()) { cout << "Fajl nem nyithato meg"; exit(1); }
            int i = 0;
            while(!be.eof()&&(be >> fuvarok[i].nap)) {
                be >> fuvarok[i].sorsz;
                be >> fuvarok[i].tavolsag;
                i++;
            }
            db = i;
        }

        int hetUtolsoFuvarKm() {
            int maxNap = 0;
            int maxSorszamIndex = 0;
            // megkeressük az utolsó napot
            for (int i = 0; i<db; i++){
                if (fuvarok[i].nap > maxNap) {
                    maxNap = fuvarok[i].nap;
                }
            }
            for (int i = 0; i<db; i++){
                if (fuvarok[i].nap == maxNap && fuvarok[i].sorsz > fuvarok[maxSorszamIndex].sorsz) {
                    maxSorszamIndex = i;
                }
            }

            return fuvarok[maxSorszamIndex].tavolsag;
        }

        int legtobbFuvarNap() {
            szamolNapokat();

            int maxIndex = 1;
            for (int i = 2; i<=7; i++){
                //cout << i << ". nap: " << naponkenti_osszeg[i]<<endl;
                if (naponkentiDb[i]>naponkentiDb[maxIndex]) maxIndex = i;
            }
            return maxIndex;
        }

        string getNapStr(int i) {
            return napok[i];
        }
        int szamolOsszesen() {
            int fiz = 0;
            for (int i = 0; i<db; i++){
                fiz += szamolTavAlapjan(fuvarok[i].tavolsag);
            }
            return fiz;
        }
        int szamolTavAlapjan(int tav)  {
            int fiz = 0;
            if (tav < 1) fiz = 0;
            else if (tav < 4) fiz = 500;
            else if (tav < 6) fiz = 700;
            else if (tav < 11) fiz = 900;
            else if (tav < 21) fiz = 1400;
            else if (tav < 31) fiz = 2000;
            return fiz;
        }
        static void print( Fuvar f)
        {
            cout << "Nap: "<< f.nap << " ssz.: " << f.sorsz << " tav: " << f.tavolsag << endl;
        }
};
Feldolgoz::Feldolgoz() {
    napok[1] = "Hetfo";
    napok[2] = "Kedd";
    napok[3] = "Szerda";
    napok[4] = "Csutortok";
    napok[5] = "Pentek";
    napok[6] = "Szombat";
    napok[7] = "Vasarnap";
}
int main() 
{
    Feldolgoz fd;

    cout << "1. feladat: " << endl;
    cout << " Beolvasas: " << endl;
    // 1. feladat
    fd.beolvas();

    // 2. feladat

    // 3. feladat
    cout << "3. feladat: " << endl;
    cout << " Het utolso fuvar kilometerben: " << fd.hetUtolsoFuvarKm() << endl;

    // 4. feladat

    // 5. feladat
    cout << "5. feladat: " << endl;
    int max = fd.legtobbFuvarNap();
    cout << " Het melyik napjan volt a legtobb fuvar: " << max << ". nap, "  << fd.getNapStr(max) << endl;

    // 6. feladat

    // 7. feladat
    cout << "7. feladat: " << endl;
    cout << " Adjon meg egy tavolsagot: ";
    int tav;
    cin >> tav;
    cout << " Jarandosag: " <<  fd.szamolTavAlapjan(tav) << endl;

    // 8. feladat

    // 9. feladat
    cout << "9. feladat: " << endl;
    cout << " Heti jarandosag: " <<  fd.szamolOsszesen() << endl;
}