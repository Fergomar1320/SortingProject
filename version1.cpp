#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int dictionary(string mes){
    vector<string> dictionary = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dic"};
    int index = 0;
    for (int i = 0; index == 0; i++){
        if(mes == dictionary[i]){
            index = i;
        }
    }
    return index;
}

void fileReading(vector <string> &data, vector <double> &dates){
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
            float monthValue = dictionary(month);
            float calculo = monthValue + (day/100) + ((hour*60*60)/100000000) + ((minute*60)/100000000) + ((second)/100000000);
            string completeLine = month + " " + to_string(static_cast<int>(day)) + " " + to_string(static_cast<int>(hour)) + ":" + to_string(static_cast<int>(minute)) + ":" + to_string(static_cast<int>(second)) + " " + errorType + errorDescription;
            data.push_back(completeLine);
            dates.push_back(calculo);
            //cout << month << " " << day << " " << hour << " " << minute << " " << second << " " << errorType << errorDescription << endl;
        }
        dataBase.close();
    }
    cout << "El archivo se leyó correctamente" << endl;
}

void writeFile(vector <string> &data){
    fstream dataBase;
    dataBase.open("sortData.txt",ios::out);
    if(dataBase.is_open()){
        for(int i = 1;i <= data.size(); i++){
            dataBase << data[i] << endl;
        }
        dataBase.close();
    }
}


void printData(vector <string> &data, vector <double> &dates){
    for(int i=0;i<data.size();i++){
        cout << data[i] << endl;
    }
}

void mergeOrder(vector<double> &dates, vector<string> &data, int start, int half, int end){
    vector<double> vI;
    vector<double> vD;
    vector<string> sI;
    vector<string> sD;

    int numIzq = half - start + 1;
    int numDer = end - half;

    for(int i = 0; i < numIzq; i++){
     vI.push_back(dates[start + i]);
     sI.push_back(data[start + i]);
    }
    for(int i = 0; i < numDer; i++){
        vD.push_back(dates[half + 1 + i]);
        sD.push_back(data[half + 1 + i]);
    }

    double i = 0;
    double j = 0; 
    double k = start;

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

void mergeSort(vector<double> &dates, vector<string> &data, int start, int end){
    if(start < end){
        int half = start + (end - start) / 2;
        mergeSort(dates, data, start, half);
        mergeSort(dates, data, half + 1, end);
        mergeOrder(dates, data, start, half, end);
    }
}


int main(){
    vector <string> myVector;
    vector <string> data;
    vector <double> dates;

    fileReading(data, dates);
    cout << "The file lecture has begun" << endl;
    cout << "Organizing......" << endl;
    mergeSort(dates, data, 0, dates.size()-1);
    cout << "The sorting has been completed" << endl;
    writeFile(data);
    cout << "The data has been saved in the sortData.txt file" << endl;
    cout << "Which data would you like to search?" << endl;
    //printData(data, dates); 
    return 0;
}