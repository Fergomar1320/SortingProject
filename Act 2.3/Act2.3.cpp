#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
//Nolberto Castro Sánchez A01641501
//Fernando Gómez Martínez A01641228

using namespace std;

void fileReading(vector <string> &data, vector <double> &hashvalues){
    ifstream dataBase;
    dataBase.open("database.txt");
    string month, day, time, error, otherChar, completeLine;
    int oneN, twoN, threeN, fourN, fiveN;
    char sillychar;
    if(dataBase.is_open()){
        while (!dataBase.eof( )){
            //Reading the complete file and saving data in variables;
            dataBase >> month >> day >> time >> oneN >> sillychar >> twoN >> sillychar >> threeN >> sillychar >> fourN >> sillychar >> fiveN;
            getline(dataBase, error); 
            double hashValue = static_cast<double>(oneN) + (static_cast<double>(twoN)/100) + (static_cast<double>(threeN)/100000) + (static_cast<double>(fourN)/10000000) + (static_cast<double>(fiveN)/1000000000);
            completeLine = month + " " + day + " " + time + " " + to_string(oneN) + "." + to_string(twoN) + "." + to_string(threeN) + "." 
            + to_string(fourN) + ":" + to_string(fiveN) + error;
            data.push_back(completeLine);
            hashvalues.push_back(hashValue);
            //DoubleList.addToList(completeLine, hashValue);
        }
        dataBase.close();
    }
    cout << "El archivo se leyó correctamente" << endl;
} //Time Complexity O(n)

void writeFile(vector <string> &data, vector <double> &hashvalues){
    fstream dataBase;
    dataBase.open("sortData.txt",ios::out);
    if(dataBase.is_open()){
        for(int i = 1;i <= data.size(); i++){
            dataBase << data[i] << endl;
        }
        dataBase.close();
    }
} //Time Complexity O(n^2)

void mergeOrder(vector<double> &hashvalues, vector<string> &data, int start, int half, int end){
    vector<double> vI;
    vector<double> vD;
    vector<string> sI;
    vector<string> sD;

    int numIzq = half - start + 1;
    int numDer = end - half;

    for(int i = 0; i < numIzq; i++){
     vI.push_back(hashvalues[start + i]);
     sI.push_back(data[start + i]);
    }
    for(int i = 0; i < numDer; i++){
        vD.push_back(hashvalues[half + 1 + i]);
        sD.push_back(data[half + 1 + i]);
    }

    double i = 0;
    double j = 0; 
    double k = start;

    while(i < numIzq && j < numDer){
        if (vI[i] <= vD[j]){
            hashvalues[k] = vI[i];
            data[k] = sI[i];
            i++;
        } else{
            hashvalues[k] = vD[j];
            data[k] = sD[j];
            j++;
        }
        k++;
    }

    while(j < numDer){
        hashvalues[k] = vD[j];
        data[k] = sD[j];
        j++;
        k++;
    }
    while(i < numIzq){
        hashvalues[k] = vI[i];
        data[k] = sI[i];
        i++;
        k++;
    }
} //Time Complexity O(n log n)

void mergeSort(vector<double> &hashvalues, vector<string> &data, int start, int end){
    if(start < end){
        int half = start + (end - start) / 2;
        mergeSort(hashvalues, data, start, half);
        mergeSort(hashvalues, data, half + 1, end);
        mergeOrder(hashvalues, data, start, half, end);
    }
} 

void sequentialSearch(vector<double> &hashvalues, vector<string> &data){

    int N1, N2, N3, N4, N5 , N6, N7, N8, N9, N10;
    char symbol;

    cout << "\nWrite the first ip" << endl;
    cin >> N1 >> symbol >> N2 >> symbol >> N3 >> symbol >> N4 >> symbol >> N5;
    double firstValue = static_cast<double>(N1) + (static_cast<double>(N2)/100) + 
    (static_cast<double>(N3)/100000) + (static_cast<double>(N4)/10000000) + (static_cast<double>(N5)/1000000000);
    cout << firstValue << endl;
    

    cout << "Write the second ip" << endl;
    cin >> N6 >> symbol >> N7 >> symbol >> N8 >> symbol >> N9 >> symbol >> N10;
    double secondValue = static_cast<double>(N6) + (static_cast<double>(N7)/100) + 
    (static_cast<double>(N8)/100000) + (static_cast<double>(N9)/10000000) + (static_cast<double>(N10)/1000000000);
    cout << secondValue << endl;

    cout << "\nHere are the search results: \n" << endl;
    for (int i = 0; i <= hashvalues.size(); i++){
        if (hashvalues[i] >= firstValue && hashvalues[i] <= secondValue){
                cout << data[i] << endl;
        }
    }

} // Time Complexity O(n^2)

int main(){
    vector <string> data;
    vector <double> hashvalues;
    cout << "The file lecture has begun" << endl;
    fileReading(data, hashvalues);
    cout << "Organizing......" << endl;
    mergeSort(hashvalues, data, 0, hashvalues.size()-1);
    cout << "The sorting has been completed" << endl;
    writeFile(data, hashvalues);
    cout << "Creating Double Linked List" << endl;
    sequentialSearch(hashvalues, data);
    cout << "\nThank you very much" << endl;
    return 0;
}

