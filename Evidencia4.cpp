#include <iostream>
#include <fstream>
#include <sstream>
#include "GraphCities.h"
using namespace std; 

template <class T>
void swap(vector<T> &list,int a, int b){
    //Validamos que sean diferentes
    if(list[a]!=list[b]){
        T aux=list[a]; 
        list[a]=list[b];
        list[b]=aux; 
        
    }
    //print(list); 
}

template <class T>
int getPivot(vector<T> &list,int left, int right){
    int pivot = right; 
    int auxIndex=left-1;
    for(int index=left;index<right;index++){
        if(list[index]<list[pivot]){
            auxIndex++;
            swap(list,index,auxIndex);
        }
    }
    auxIndex++;
    swap(list,auxIndex,pivot);
    return auxIndex;
}

template <class T>
void quickSort(vector<T> &list, int left, int right){
    
    if(left < right){
        int pivot=getPivot(list,left,right); 

        quickSort(list,left,pivot-1);
        quickSort(list,pivot+1,right);
    }
}

void exportFile(string archivo,vector<string>cityVertex){
    ofstream file(archivo);
    for(int i=0;i<cityVertex.size();i++){
        file<<cityVertex[i]<<endl;
    }
    file.close();
}

void exportFile2(string archivo,vector<EdgeCity<string>>& cities){
    ofstream file(archivo);
    for(int i=0;i<cities.size();i++){
        file<<cities[i].originCity<<","<<cities[i].targetCity<<","<<cities[i].trainTimeMins<<","<<cities[i].trainTimeHour<<","<<cities[i].carTimeMins<<","<<cities[i].carTimeHour<<endl;
    }
    file.close();
}





template<class T> 
void uniqueCities(vector<T>&cityVertex){
    //string res = cityVertex.begin(); 
    for(int j=0;j<=cityVertex.size();j++){
        for(int i=0;i<=cityVertex.size();i++){
            if(cityVertex[i]==cityVertex[j] && i!=j){
                cityVertex.erase(cityVertex.begin()+i);
                i--; 
            }
        }
        
    }

}



template <class T>
void readFile(vector<EdgeCity<T>>& cities, vector<T>& cityVertex){
    ifstream file("EuropeCities.csv");
    string line,originCity,targetCity, trainTimeMins, trainTimeHour , carTimeMins, carTimeHour;
    while(file.good()){
        getline(file,originCity,',');
        getline(file,targetCity,',');
        getline(file,trainTimeMins,',');
        getline(file,trainTimeHour,',');
        getline(file,carTimeMins,',');
        getline(file,carTimeHour,'\n');
        EdgeCity<string>edge(originCity,targetCity,trainTimeMins,trainTimeHour,carTimeMins,carTimeHour);
    
        //cout<<edge.originCity<<" "<<edge.targetCity<<" "<<edge.trainTimeMins<<" "<<edge.trainTimeHour<<" "<<edge.carTimeMins<<" "<<edge.carTimeMins<<" "<<endl;
        cities.push_back(edge);
        
        cityVertex.push_back(originCity);
        cityVertex.push_back(targetCity);
    } 
    file.close(); 
}
    

int main()
{
    HashCities<string> tablaCity;
    vector<EdgeCity<string>> cities;
    vector<string> cityVertex; 
    vector<string> res; 
    vector<vector<int>>asciiValues; 
    vector<char>orderdedCities;
    
    readFile(cities,cityVertex);
    uniqueCities(cityVertex);
    quickSort(cityVertex,0,cityVertex.size()-1);
    for(int i=0;i<cityVertex.size();i++){
        tablaCity.insert(cityVertex[i]);
        
    }

    /*tablaCity.print();  
    int res1=tablaCity.findCuidad("Santiago de Compostela");
    cout<<res1<<endl;
    cout<<endl;
    cout<<endl;*/
    Graph<string> graph(tablaCity,cities);
    /*graph.print();
    int res2=graph.findVertex("Santiago de Compostela");
    cout<<endl;
    cout<<res2<<endl;
    cout<<endl;
    cout<<endl;
    graph.bfs("Madrid");
    cout<<endl;
    cout<<endl;
    graph.dfs("Sevilla");*/
    
    bool tin=true; 
    int n,tipo,ress,deba,deba2; 
    string city1,city2; 

    cout<<"----------------------"<<endl;
    cout<<"Europe Cities"<<endl;
    cout<<"----------------------"<<endl;
    while(tin){
        cout<<"\n1.Despelgar cuidades en orden alfabetico"<<endl;
        cout<<"2.Lista de adyanecia de las cuidades"<<endl;
        cout<<"3.Busqueda de cuidad y recorrido"<<endl; 
        cout<<"4. Ruta entre cuidades (tren)"<<endl; 
        cout<<"5. Ruta entre cuidades (carro)"<<endl;
        cout<<"6. Salir"<<endl;
        cin>>n; 
        switch(n){
            case 1: 
                cout<<"\tCUIDADES"<<endl;
                for(int i=0;i<cityVertex.size();i++){
                    if(cityVertex[i]=="∩╗┐Ankara"){
                        continue;
                    }else{
                        cout<<cityVertex[i]<<endl;
                    }
                }
                exportFile("output603-1.txt",cityVertex);
                break;
            case 2:
                cout<<"\tLISTA DE ADYACENCIA"<<endl;
                graph.print();
                break;
            case 3:
                cout<<"\t ESCOGE EL TIPO DE RECORRIDO" <<endl; 
                cout<<"1. BFS"<<endl;
                cout<<"2. DFS"<<endl;
                cin>>tipo;
                if(tipo==1){
                    cout<<"\tBFS"<<endl;
                    cout<<"Ingrese la cuidad que desea buscar"<<endl;
                    string city; 
                    cin>>city; 
                    try{ress=graph.findVertex(city);}
                    catch(const out_of_range& oor){
                        cout<<"La cuidad "<<city<<" no se encuentra en la lista"<<endl;
                    }
                    if(ress!=-1){
                        cout<<"La cuidad "<<city<<" se encuentra en la posicion "<<ress<<endl;
                        cout<<"El recorrido de la cuidad "<<city<<" es: "<<endl;
                        graph.bfs(city);
                    }else{
                        cout<<"La cuidad "<<city<<" no se encuentra en la lista"<<endl;
                    }
                    cout<<endl;
                    break;
                }else if(tipo==2){
                    cout<<"\tDFS"<<endl;
                    cout<<"Ingrese la cuidad que desea buscar"<<endl;
                    string city; 
                    cin>>city; 
                    try{ress=graph.findVertex(city);}
                    catch(const out_of_range& oor){
                        cout<<"La cuidad "<<city<<" no se encuentra en la lista"<<endl;
                    }
                    if(ress!=-1){
                        cout<<"La cuidad "<<city<<" se encuentra en la posicion "<<ress<<endl;
                        cout<<"El recorrido de la cuidad "<<city<<" es: "<<endl;
                        graph.dfs(city);
                    }else{
                        cout<<"La cuidad "<<city<<" no se encuentra en la lista"<<endl;
                    }
                    cout<<endl;
                    break;
                }else{
                    cout<<"Opcion no valida"<<endl;
                    break;

                }
            case 4:
             
                cout<<"RUTA MAS CORTA POR TREN"<<endl;
                cout<<"Ingrese la cuidad de origen"<<endl;
                cin>>city1;
                if(graph.findVertex(city1)==-1){
                    cout<<"La cuidad "<<city1<<" no se encuentra en la lista"<<endl;
                    break;
                }
                cout<<"Ingrese la cuidad de destino"<<endl;
                cin>>city2;
                if(graph.findVertex(city2)==-1){
                    cout<<"La cuidad "<<city2<<" no se encuentra en la lista"<<endl;
                    break;
                }
                if(city1==city2){
                    cout<<"La cuidad de origen y destino son iguales"<<endl;
                    break;
                }else{
                    if(deba!=-1){
                        cout<<"La ruta mas corta entre "<<city1<<" y "<<city2<<" es: "<<endl;
                        try{graph.dijkstra(city1,city2);}
                        catch(const out_of_range& oor){
                            cout<<"La cuidad "<<city1<<" no se encuentra en la lista"<<endl;
                        }
                    }
                }
                cout<<endl;
                break;
            case 5: 
                cout<<"RUTA MAS CORTA POR CARRO"<<endl;
                cout<<"Ingrese la cuidad de origen"<<endl;
                cin>>city1;
                if(graph.findVertex(city1)==-1){
                    cout<<"La cuidad "<<city1<<" no se encuentra en la lista"<<endl;
                    break;
                }
                cout<<"Ingrese la cuidad de destino"<<endl;
                cin>>city2;
                if(graph.findVertex(city2)==-1){
                    cout<<"La cuidad "<<city2<<" no se encuentra en la lista"<<endl;
                    break;
                }
                if(city1==city2){
                    cout<<"La cuidad de origen y destino son iguales"<<endl;
                    break;
                }else{
                    cout<<"La ruta mas corta entre "<<city1<<" y "<<city2<<" es: "<<endl;
                    try{graph.dijkstraCar(city1,city2);}
                    catch(const out_of_range& oor){
                        cout<<"La cuidad "<<city1<<" no se encuentra en la lista"<<endl;
                    }
                }
                cout<<endl;
                break; 
                   
            case 6:
                cout<<"SALIENDO..."<<endl;
                tin=false; 
                break;

        }
    }
}
    
    

