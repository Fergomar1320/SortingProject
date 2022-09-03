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

void lecturaArchivo(vector <string> &data, vector <double> &dates){
    ifstream dataBase;
    dataBase.open("bitacora.txt");
    string month;
    double day;
    double hour;
    double minute;
    double second;
    char sillyChar;
    string errorType;
    string line;
    string errorDescription;
    
    if(dataBase.is_open()){
        while (!dataBase.eof( )){
            dataBase >> month >> day >> hour >> sillyChar >> minute >> sillyChar >> second >> errorType;
            getline(dataBase, errorDescription);
            float monthValue = diccionario(month);
            float calculo = monthValue + (day/100) + (hour/1000) + (minute/10000) + (second/100000);
            string completeLine = month + " " + to_string(day) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " " + errorType + " " + errorDescription;
            data.push_back(completeLine);
            dates.push_back(calculo);
            //cout << month << " " << day << " " << hour << " " << minute << " " << second << " " << errorType << errorDescription << endl;
        }
        dataBase.close();
    }
    cout << "El archivo se leyó correctamente" << endl;
}

void printData(vector <string> &data, vector <double> &dates){
    for(int i=0;i<data.size();i++){
        cout << data[i] << " " << dates[i] <<endl;
    }
}

int main(){
    //ifstream archivoLog("bitacora.txt");
    string resgistro;

    string log[5];
    vector <string> myVector;
    vector <string> data;
    vector <double> dates;

    lecturaArchivo(data, dates);
    cout << "La lectura de archivos se ha realizado correctamente" << endl;
    cout << "Organizando......" << endl;

    // cout << "prueba" << endl;
    // separar(resgistro, log);
    // cout << &data << endl;
    // cout << log[0] << "/";
    // cout << log[1] << "/";
    // cout << log[2] << "/";
    // cout << log[3] << "/";
    // cout << log[4] << "/";
    return 0;
}

// prueba