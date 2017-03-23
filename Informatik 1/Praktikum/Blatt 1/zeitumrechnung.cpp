    #include <iostream>
    using namespace std;
    int main (){
        int eingabe = 123456; // Eingabe i n Sekunden
        int sekunden = 0;
        int minuten = 0;
        int stunden = 0;
        cout << eingabe << "Sekunden entsprechen" ;
        stunden = eingabe / 3600;
        eingabe = eingabe - 3600 * stunden;
        minuten = eingabe / 60;
        eingabe = eingabe - minuten * 60;
        sekunden = eingabe;

        cout << stunden << " Stunden , " << minuten << " Minuten und " << sekunden << " Sekunden . " << endl;
        return 0;
     }
