#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
//Nolberto Castro Sánchez A01641501
//Fernando Gómez Martínez A01641228

using namespace std;

template <class T> class Node{
    private:
        T data;
        int ip;
        Node* next;
        Node* prev;
    public:
        Node(T newData, int newIp, Node* nextNode, Node* prevNode){
            this->data = newData;
            this->next = nextNode;
            this->prev = prevNode;
            this->ip = newIp;
        }//Complexity O(1)
        Node(T newData){
            this->data = newData;
            this->next = NULL;
            this->prev = NULL;
            this->ip = 0;
        }//Complexity O(1)
        void setData(T newData){
            this->data = newData;
        } //Complexity O(1)
        T getData(){
            return this->data;
        } //Complexity O(1)
        void setNext(Node *nextNode){
            this->next = nextNode;
            
        }//Complexity O(1)
        void setPrev(Node *prevNode){
            this->prev = prevNode;
        }//Complexity O(1)
        Node* getNext(){
            return this->next;
        }//Complexity O(1)
        Node* getPrev(){
            return this->prev;
        }//Complexity O(1)
};

template<class T> class doubleLinkedList{
    private:
        Node<T> *head;
        Node<T> *tale;
        int listLong;
    public:
        doubleLinkedList(){
            head = NULL;
            tale = NULL;
        }   //Complexity O(1)

        ~doubleLinkedList(){
        } //Complexity O(1)

        Node<T>* getTale(){
            return tale;
        } //Complexity O(1)

        void addToList(T data,int ip){
            if (head == NULL){
                Node<T>* temp = new Node<T>(data,ip,head,tale);
                this->head = temp;
                this->tale = temp;
            }else{
                Node<T>* newNode = new Node<T>(data,ip,NULL,tale);
                tale->setNext(newNode);
                tale = newNode;
            }
            listLong++;
        } //Complexity O(1)

        void printList(){
            Node<T>* currentNode = this->head;
            while(currentNode != NULL){
                cout << currentNode->getData() << endl;
                currentNode = currentNode->getNext();
            }
            cout << "NULL\n" << endl;
        } //Complexity O(n)

        Node<T>* searchNode(T valueTarget){
            Node<T>* currentNode = this->head;

            while(currentNode){
                if(currentNode->getData() == valueTarget){
                    return currentNode;
                }
                currentNode = currentNode->getNext();
            }

            return NULL;
        } //Complexity O(n)
};

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
            double hashValue = static_cast<double>(oneN) + (static_cast<double>(twoN)/100) + (static_cast<double>(threeN)/100000) + (static_cast<double>(fourN)/100000000); //+ fiveN;
            completeLine = month + " " + day + " " + time + " " + to_string(oneN) + "." + to_string(twoN) + "." + to_string(threeN) + "." 
            + to_string(fourN) + ":" + to_string(fiveN) + error + to_string(hashValue);
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

int main(){
    vector <string> data;
    vector <double> hashvalues;
    doubleLinkedList<string> firstList;

    cout << "The file lecture has begun" << endl;
    fileReading(data, hashvalues);
    cout << "Organizing......" << endl;
    mergeSort(hashvalues, data, 0, hashvalues.size()-1);
    cout << "The sorting has been completed" << endl;
    writeFile(data, hashvalues);
    firstList.printList();
    return 0;
}

