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
            float calculo = monthValue + (day/100) + ((hour*60*60)/100000000) + ((minute*60)/100000000) + ((second)/100000000);
            string completeLine = month + " " + to_string(day) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second); //+ " " + errorType + " " + errorDescription;
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
        cout << dates[i] << " " << data[i] << endl;
    }
}

void mergeOrder(vector<double> &dates, vector<string> &data, int inicio, int mitad, int final){
    vector<double> vI;
    vector<double> vD;
    vector<string> sI;
    vector<string> sD;

    int numIzq = mitad - inicio + 1;
    int numDer = final - mitad;

    for(int i = 0; i < numIzq; i++){
     vI.push_back(dates[inicio + i]);
     sI.push_back(data[inicio + i]);
    }
    for(int i = 0; i < numDer; i++){
        vD.push_back(dates[mitad + 1 + i]);
        sD.push_back(data[mitad + 1 + i]);
    }

    double i = 0;
    double j = 0; 
    double k = inicio;

    while(i < numIzq && j < numDer){
        if (vI[i] <= vD[j]){
            dates[k] = vI[i];
            data[k] = sI[i];
            i++;
        } else{
            dates[k] = vD[j];
            data[k] = sD[j];
            j++;
        }
        k++;
    }

    while(j < numDer){
        dates[k] = vD[j];
        data[k] = sD[j];
        j++;
        k++;
    }
    while(i < numIzq){
        dates[k] = vI[i];
        data[k] = sI[i];
        i++;
        k++;
    }
}

void mergeOrden(vector<double> &dates, vector<string> &data, int inicio, int final){
    if(inicio < final){
        int mitad = inicio + (final - inicio) / 2;
        mergeOrden(dates, data, inicio, mitad);
        mergeOrden(dates, data, mitad + 1, final);
        mergeOrder(dates, data, inicio, mitad, final);
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
    mergeOrden(dates, data, 0, dates.size()-1);
    printData(data, dates); 
    return 0;
}

// prueba