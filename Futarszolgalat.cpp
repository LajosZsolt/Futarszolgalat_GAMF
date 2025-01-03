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
        int naponkentiKm[8];


        void szamolNapokat()
        {
            // ki 0-azuk a napokat
            for (int i = 1; i<=7; i++){
                naponkentiDb[i] = 0;
                naponkentiKm[i] = 0;
            }
         
            for (int i = 0; i<db; i++){
                naponkentiDb[fuvarok[i].nap] ++;
                naponkentiKm[fuvarok[i].nap] += fuvarok[i].tavolsag;
            }
        }

        static int calcErtek(Fuvar fuvar)
        {
            return fuvar.nap * 100 + fuvar.sorsz;
        }

        void rendez()
        {
            for (int i = 0; i < db; i++)
            {
                for (int j = i+1; j < db; j++)
                {
                    if (calcErtek(fuvarok[j]) < calcErtek(fuvarok[i])) {
                        Fuvar seged = fuvarok[j];
                        fuvarok[j] = fuvarok[i];
                        fuvarok[i] = seged;
                    }
                }                
            }            
        }
    public:
        Feldolgoz(); 
        // 1. feladat
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

        // 2. feladat
        int hetMasodikFuvarKm() {
            // kiinduló értéket felvesszük olyan nagyra, melyet nem érhet el 
            int ertek1 = 10000;
            int ertek2 = 10000;
            int i1;
            int i2;
            for (int i = 0; i<db; i++){
                int ertek = calcErtek(fuvarok[i]);
                if (ertek < ertek1) {
                    i1 = i;
                    ertek1 = ertek;
                }
            }
            for (int i = 0; i<db; i++){
                if (i1 != i ) {
                    int ertek = calcErtek(fuvarok[i]);
                    if (ertek < ertek2) {
                        i2 = i;
                        ertek2 = ertek;
                    }
                }
            }
            return fuvarok[i2].tavolsag;
        }

        // 3. feladat
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

        // 4. feladat
        void hetSzabadNapjai() {
            // végig megyünk a napokon
            for (int n = 1; n<=7; n++){
                // Eldöntés tételével vizsgáljuk, hogy szabad nap volt a bizonyos nap
                int i=0;
                while(i<db && fuvarok[i].nap != n) i++;
                // itt ez esetben pont azt kell kírni, ha nincs elem a tömbben
                if (i==db) {
                    cout << n <<". - "<< napok[n]<< " ";
                }
            }

        }

        // 5. feladat
        int legtobbFuvarNap() {
            szamolNapokat();
            // minimumnak vesszük az első napot
            int maxIndex = 1;
            for (int i = 2; i<=7; i++){
                if (naponkentiDb[i]>naponkentiDb[maxIndex]) maxIndex = i;
            }
            return maxIndex;
        }

        // 6. feladat
        void osszegezNaponkent()
        {
            // végig megyünk a napokon
            for (int n = 1; n <= 7; n++)
            {
                cout <<"  "<< n << ". nap: " << naponkentiKm[n] << endl;
            }
        }

        string getNapStr(int i) {
            return napok[i];
        }

        // 8-9. feladat
        int szamolOsszesenKiirReszosszeg()
        {
            rendez();
            int fiz = 0;
            ofstream ki("befizetes.txt");
            if (ki.fail())
            {
                cout << "Fajl nem nyithato meg";
                exit(1);
            }

            for (int i = 0; i < db; i++)
            {
                int reszFiz = szamolTavAlapjan(fuvarok[i].tavolsag);
                ki << "  " << fuvarok[i].nap << ".nap " << fuvarok[i].sorsz << ".út: " << reszFiz << " Ft" << endl;
                fiz += reszFiz;
            }
            cout << "  Sikeresen elkeszult fajl: befizetes.txt" << endl;
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
    cout << "2. feladat: " << endl;
    cout << " Het masodik utja kilometerben: " << fd.hetMasodikFuvarKm() << endl;

    // 3. feladat
    cout << "3. feladat: " << endl;
    cout << " Het utolso fuvar kilometerben: " << fd.hetUtolsoFuvarKm() << endl;

    // 4. feladat
    cout << "4. feladat: " << endl;
    cout << " Het szabadnapjai: ";
    fd.hetSzabadNapjai();
    cout << endl;

    // 5. feladat
    cout << "5. feladat: " << endl;
    int max = fd.legtobbFuvarNap();
    cout << " Het melyik napjan volt a legtobb fuvar: " << max << ". nap, "  << fd.getNapStr(max) << endl;

    // 6. feladat
    cout << "6. feladat: " << endl;
    cout << " Egyes napkokon megtett kilometer: "<<endl;
    fd.osszegezNaponkent();
    cout << endl;

    // 7. feladat
    cout << "7. feladat: " << endl;
    cout << " Adjon meg egy tavolsagot: ";
    int tav;
    cin >> tav;
    cout << " Jarandosag: " <<  fd.szamolTavAlapjan(tav) << endl;

    // 8. feladat
    cout << "8. feladat: " << endl;
    int osszesen = fd.szamolOsszesenKiirReszosszeg();

    // 9. feladat
    cout << "9. feladat: " << endl;
    cout << " Heti jarandosag: " <<  osszesen << endl;
}