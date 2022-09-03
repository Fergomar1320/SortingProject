#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int diccionario(string mes){
    vector<string> diccionario = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dic"};
    int index = 0;
    for (int i = 0; index == 0; i++){
        if(mes == diccionario[i]){
            index = i;
        }
    }
    return index;
}

void lecturaArchivo(){
    ifstream dataBase;
    dataBase.open("bitacora.txt");
    string month;
    int day;
    int hour;
    int minute;
    int second;
    char sillyChar;
    string errorType;
    string line;
    string errorDescription;

    if(dataBase.is_open()){
        while (!dataBase.eof( )){
            dataBase >> month >> day >> hour >> sillyChar >> minute >> sillyChar >> second >> errorType;
            getline(dataBase, errorDescription);
            cout << month << " " << day << " " << hour << " " << minute << " " << second << " " << errorType << errorDescription << endl;
        }
        dataBase.close();
    }
}

void separar(string linea, string arr[]){ 
    int inicio = 0, j = 0;

    for (int final=0; final < linea.length();){
        cout << inicio <<" "<<final<<" "<<j<<arr[j]<<endl;
        if(linea.at(final) != ' '){
            final ++;
        }else{
            arr[j] = linea.substr(inicio, final);
            
            final++;
            inicio = final;
            j++;
            
        }
    }
}

int main(){
    //ifstream archivoLog("bitacora.txt");
    string resgistro;
    string log[5];
    vector <string> myVector;
    cout << "Esta en la posición " << diccionario("Mar") << endl;
    lecturaArchivo();
    cout << "Los datos se leyeron Correctamente" << endl;
    cout << "Empezando organización" << endl;
    cout << "prueba" << endl;
    resgistro = "pepe pecas pica papas con ";
    separar(resgistro, log);
    cout << log[0] << "/";
    cout << log[1] << "/";
    cout << log[2] << "/";
    cout << log[3] << "/";
    cout << log[4] << "/";
    return 0;
}

// prueba