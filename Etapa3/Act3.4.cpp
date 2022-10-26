#include <iostream>
#include <fstream>
#include "bst.cpp"

using namespace std;


void fileReading(BST &tree) {
    ifstream dataBase;
    dataBase.open("Prueba.txt");
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

            Node* temp = new Node(hashValue, completeLine);
            tree.insert(temp->ip, temp->text);
            //DoubleList.addToList(completeLine, hashValue);
        }
        dataBase.close();
    }
    cout << "The file was read correctly" << endl;
} //Time Complexity O(n)

int main(){
    BST arbol;
    fileReading(arbol);

    arbol.preOrder();
    return 0;
}

