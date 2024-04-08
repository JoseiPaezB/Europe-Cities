#ifndef Graph_h
#define Graph_h
#include "EdgeCity.h"
#include "HashCities.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
template <class T>
class Graph {
private:
    HashCities<T> vertices;
    vector<string> table;
    vector< vector< EdgeCity<T> > > adjacencyList;
    void dsfr(T vertex,vector<bool> &status); 
public:
    Graph();
    Graph(HashCities<T> vertices, vector< EdgeCity<T> > edges);
    int findVertex(T vertex);
    void addVertex(T vertex);
    void addEdge(EdgeCity<T> egde);
    void removeVertex(T vertex);
    void removeEdge(EdgeCity<T> edge);
    void bfs(T vertex);
    void print();
    void dfs (T vertex);
    int findShortest(vector<bool>&status,vector<int>&cost); 
    void dijkstra(T vertex,T vertex2);
    void dijkstraCar(T vertex,T vertex2);

};
ofstream file("output604-4.txt"); 
ofstream file2("output603-3.txt"); 
ofstream file3("output603-2.txt");


template <class T>
Graph<T>::Graph() {
}
template <class T>
int Graph<T>::findVertex(T vertex) {
    return vertices.findCuidad(vertex);
    /*typename vector<T>::iterator it;
    it = find(vertices.begin(), vertices.end(), vertex);
    if (it != vertices.end()) {
        return it - vertices.begin();
    } else {
        return -1;
    }*/
}
template <class T>
Graph<T>::Graph(HashCities<T> vertices, vector< EdgeCity<T> > edges) {
    // Actualizamos la lista de vértices
    this->vertices.table = vertices.table;
    // Inicilizamos la lista de adyacencias
    adjacencyList.resize(vertices.getSize());
    // Recorremos la lista adyacencias
    for (auto edge : edges) {
        // buscamos el índice en la lista de vértices del vértice origen
        int sourceIndex = findVertex(edge.originCity);
        // buscamos el índice en la lista de vértices del vértice destino
        int targetIndex = findVertex(edge.targetCity);
        // Validamos que existan en la lista de vértices
        if (sourceIndex != -1 && targetIndex != -1) {
            adjacencyList[sourceIndex].push_back(edge);
        }
    }
}

template <class T> 
void Graph<T>::dsfr(T vertex, vector<bool> &status){
    if(vertex!=""){
        cout<<vertex<<"--> ";
        file<<vertex<<"--> ";
    int vertexIndex=findVertex(vertex);
    status[vertexIndex]=true; 
    for(auto neighbor : adjacencyList[vertexIndex]){
        int neighborIndex=findVertex(neighbor.targetCity); 
        if(!status[neighborIndex]){
            dsfr(neighbor.targetCity, status); 
            if(neighbor.targetCity==""){
                break; 
            }
        }
    }
    
    }else{
         cout<<endl;
         file.close();
    
    }
    
}

template <class T> 
void Graph<T>::dfs(T vertex){
    int vertexIndex = findVertex(vertex);
    if (vertexIndex != -1) {
        vector<bool> status(vertices.getSize(), false);
        dsfr(vertex, status);
    } else {
        throw invalid_argument("Vertice invalido");
    }
}

template <class T>
void Graph<T>::addVertex(T vertex) {
    // Buscar si existe el vértice a agregar
    int vertexIndex = findVertex(vertex);
    // Si no existe agregarlo a la lista de vértices
    // Agregarlo a la lista de adyacencias
    if (vertexIndex == -1) {
        // Lo agregamos a la lista de vértices
        vertices.table.insert(vertex);
        // Agregarlo a la lista de adyacencias
        vector< EdgeCity<T> > emptyEdges;
        adjacencyList.push_back(emptyEdges);
    } else {
        throw invalid_argument("Vértice ya existe");
    }
}


template <class T>
void Graph<T>::addEdge(EdgeCity<T> edge) {
    // Validar que los vértices origen y destino existan
    int sourceIndex = findVertex(edge.originCity);
    int targetIndex = findVertex(edge.targetCity);
    // Validar que el edge no se encuentre ya en la lista de adyacencias
    // Agregar el edge a la lista de ayacencias
    if (sourceIndex != -1 && targetIndex != -1) {
        for (auto neighbor : adjacencyList[sourceIndex]) {
            // Validamos que no exisa ya en la lista de adyacencias
            if (neighbor.targetCity == edge.targetCity) {
                throw invalid_argument("El arco ya existe");
            }
        }
        // Agregar el edge a la lista de ayacencias
        adjacencyList[sourceIndex].push_back(edge);
    } else {
        throw invalid_argument("Alguno de los vértices no existen");
    }
}

template <class T>
void Graph<T>::removeVertex(T vertex){
    // buscamos el indice en la lista de vertices en el vertice origen
    int vertexIndex = findVertex(vertex);
    // validamos que exista en la lista de vertices
    if (vertexIndex != -1) {
        // eliminamos el vertice de la lista de vertices
        vertices.remove2(vertexIndex);
        // eliminamos el vertice de la lista de adyacencia
        adjacencyList.erase(adjacencyList.begin() + vertexIndex);
        // eliminamos el vertice de la lista de adyacencia de cada vertice
        for (auto &adjacency : adjacencyList) {
            typename vector< EdgeCity<T> >::iterator it;
            it = adjacency.begin();
            while (it != adjacency.end()) {
                if (it->target == vertex) {
                    adjacency.erase(it);
                } else {
                    it++;
                }
            }
        }
    }
}
template <class T>
void Graph<T>::removeEdge(EdgeCity<T> edge) {
    // buscar el índice del vértice origen
    int sourceIndex = findVertex(edge.originCity);
    int targetIndex = findVertex(edge.targetCity);

    if(sourceIndex!=-1&& targetIndex!=-1){
        for(int i=0;i<adjacencyList.size();i++){
            for(int j=0;j<adjacencyList[i].size();j++){
                if(adjacencyList[i][j+1].target==targetIndex){
                    adjacencyList[i].erase(adjacencyList[i].begin()+j);
                }
            }
        }
    }else{
        throw invalid_argument("Vertice invalido");
    }


    // Si existe, buscar en la lista de adyacencias el edge
        // si existe, eliminarlo
}

template <class T>
void Graph<T>::bfs(T vertex) {
    int vertexIndex = findVertex(vertex);
    if (vertexIndex != -1) {
        queue<int> fila;
        vector<bool> status(vertices.getSize(), false);
        fila.push(vertexIndex);
        status[vertexIndex] = true;

        while (!fila.empty()) {
            int currentVertexIndex = fila.front();
            fila.pop();
            
            file2<<vertices.getCityAtIndex(currentVertexIndex) << " --> ";
            cout << vertices.getCityAtIndex(currentVertexIndex) << " --> ";
            

            for (auto neighbor : adjacencyList[currentVertexIndex]) {
                int neighborIndex = findVertex(neighbor.targetCity);
                if (!status[neighborIndex]) {
                    fila.push(neighborIndex);
                    status[neighborIndex] = true;
                }
            }
        }
        file2.close(); 
    } else {
        throw invalid_argument("Vertice invalido");
    }
}

template <class T>
void Graph<T>::print() {
    for (int i=0; i<vertices.getSize(); i++) {
        //vertices.table.print();
        for (auto edge : adjacencyList[i]) {
            if(edge.targetCity==""){
                continue; 
            }else{
            file3<<edge.targetCity << " " << edge.trainTimeMins << " - "<< edge.trainTimeHour << " - "<< edge.carTimeMins << " - "<< edge.carTimeHour << " -> "<<endl;
            cout << edge.targetCity << " " << edge.trainTimeMins << " - "<< edge.trainTimeHour << " - "<< edge.carTimeMins << " - "<< edge.carTimeHour << " -> ";
            
        }
        }
        cout << endl;
    }file3.close();
}



template <class T>
int Graph<T>::findShortest(vector<bool> &status, vector<int> &cost) {
    // Incializamos una variable en -1 para guardar el índice del costo más pequeño
    int shortestIndex = -1;
    // Inicializamos una variable para determinar cual fue el costo más pequeño
    int shortestCost = INT_MAX;
    // Iteramos todos los vértices
    for (int i=0; i<vertices.getSize(); i++) {
        // Validamos que el estatus del vértice actual sea falso
        if (!status[i]) {
            // Comparamos si el costo de vértice actual es menor al costo más pequeño
            if (cost[i] < shortestCost) {
                // Actualizamos el shortest Cost
                shortestCost = cost[i];
                // Actualizamos el shortest Index
                shortestIndex = i;
            }
        }
    }
    return shortestIndex;
}





template <class T>
void Graph<T>::dijkstra(T vertex,T vertex2) {
    // Validamos que el vértice de parámetro exista
    vector<int> res;

    int vertexIndex = findVertex(vertex);
    int vertexIndex2 = findVertex(vertex2);
    if (vertexIndex != -1) {
        // Creamos la tabla de estados
        vector<bool> status(vertices.getSize(), false);
        // Creamos la tabla de costos
        vector<int> cost(vertices.getSize(), INT_MAX);
        // Creamos la tabla de path
        vector<int> path(vertices.getSize(), -1);
        vector<int> km(vertices.getSize(), -1);
        vector<int>min(vertices.getSize(),-1);
        // Actualizamos el costo en 0 del vértice inicio
        cost[vertexIndex] = 0;
        // Creamos una varibale para guardar cual el fue el vertice más pequeño de los que tienen estado en falso
        int shortestIndex = vertexIndex;
        int shortestIndex2 = vertexIndex2;
        // Iteramos mientras existe un vértice con estado en falso
        while (shortestIndex != vertexIndex2) {
            // Actualizamos el estado del shortestIndex
            status[shortestIndex] = true;
            // Recorremos los vecinos del shortestIndex
            for (auto neighbor : adjacencyList[shortestIndex]) {
                // Buscamos el índice del vecino
                int neighborIndex = findVertex(neighbor.targetCity);
                // Validamos el estado del vecino
                    // Validamos si el costo del vecino sea mayor que el costo del shortestIndex más el peso del vecino
                    int neighborCost = stoi(neighbor.trainTimeHour);
                    if (cost[neighborIndex] > cost[shortestIndex] + neighborCost) {
                        // Actualizo el costo del vecino
                        cost[neighborIndex] = cost[shortestIndex] + neighborCost;
                        path[neighborIndex] = shortestIndex;
                        km[neighborIndex]=km[shortestIndex]+neighborCost;
                        min[neighborIndex]=min[shortestIndex]+stoi(neighbor.trainTimeMins);
                        // Actualizamos el path del vecino
                        //path[neighborIndex] = shortestIndex;
                    }
                
            }
            // Actualizamos el valor de shortest Index
            shortestIndex = findShortest(status, cost);
        }
        // Seguimos con el proceso de actualizar la lista de pilas
        // Incializamos una lista de pilas vacías
        vector< stack<int> > shortestPaths(vertices.getSize());
        // Recorremos todos los vértices
        for (int i=0; i<vertices.getSize(); i++) {
            // Valdamos que el costo no sea infinito
                // Agregamos la pila del vértice actual su índice
                shortestPaths[i].push(i);
                // Creamos ubna variable para guardar el índice del path
                int pathIndex = path[i];
                // Iteramos mientras pathIndex sea diferente de -1
                while (pathIndex != -1) {
                    // Agregamos el path index a la pila
                    shortestPaths[i].push(pathIndex);   
                    // Actualizamos el path index con el valor del path de path index
                    pathIndex = path[pathIndex];
                }
            
        }
        // Imprimimos el resultado
        // Iteramos todos los vértices
        cout << vertices.table[vertexIndex2] << " -> ";

        while (!shortestPaths[vertexIndex2].empty()) {
                    // Imprimimos el primer elemento de la pila
                    //cout << shortestPaths[i].top() << " ";
                    // Sacamos el primer elemento de la pila
                    cout<<vertices.table[shortestPaths[vertexIndex2].top()]<<" ";
                    shortestPaths[vertexIndex2].pop();
        }cout << "- "; 
        if(cost[vertexIndex2]!=INT_MAX){
            int tin2=min[vertexIndex2];
            cout<<"DISTANCIA:" <<km[vertexIndex2]<<"km"<<" TIEMPO: " <<tin2 << "h :" << min[vertexIndex2]%60 << "min"<<endl;
        }else {
                cout<<"No existe esa ruta"<<endl; 
            }
        
    } else {
        throw invalid_argument("El vértice no existe");
    }
    

}

template <class T>
void Graph<T>::dijkstraCar(T vertex,T vertex2) {
    // Validamos que el vértice de parámetro exista
    vector<int> res;

    int vertexIndex = findVertex(vertex);
    int vertexIndex2 = findVertex(vertex2);
    if (vertexIndex != -1) {
        // Creamos la tabla de estados
        vector<bool> status(vertices.getSize(), false);
        // Creamos la tabla de costos
        vector<int> cost(vertices.getSize(), INT_MAX);
        // Creamos la tabla de path
        vector<int> path(vertices.getSize(), -1);
        vector<int> km(vertices.getSize(), -1);
        vector<int>min(vertices.getSize(),-1);
        // Actualizamos el costo en 0 del vértice inicio
        cost[vertexIndex] = 0;
        // Creamos una varibale para guardar cual el fue el vertice más pequeño de los que tienen estado en falso
        int shortestIndex = vertexIndex;
        int shortestIndex2 = vertexIndex2;
        // Iteramos mientras existe un vértice con estado en falso
        while (shortestIndex != vertexIndex2) {
            // Actualizamos el estado del shortestIndex
            status[shortestIndex] = true;
            // Recorremos los vecinos del shortestIndex
            for (auto neighbor : adjacencyList[shortestIndex]) {
                // Buscamos el índice del vecino
                int neighborIndex = findVertex(neighbor.targetCity);
                // Validamos el estado del vecino
                // Validamos si el costo del vecino sea mayor que el costo del shortestIndex más el peso del vecino
                int neighborCost = stoi(neighbor.carTimeHour);
                    if (cost[neighborIndex] > cost[shortestIndex] + neighborCost) {
                        // Actualizo el costo del vecino
                        cost[neighborIndex] = cost[shortestIndex] + neighborCost;
                        path[neighborIndex] = shortestIndex;
                        km[neighborIndex]=km[shortestIndex]+neighborCost;
                        min[neighborIndex]=min[shortestIndex]+stoi(neighbor.carTimeMins);
                        
                        
                        // Actualizamos el path del vecino
                    }
                
            }
            // Actualizamos el valor de shortest Index
            shortestIndex = findShortest(status, cost);
        }
        // Seguimos con el proceso de actualizar la lista de pilas
        // Incializamos una lista de pilas vacías
        vector< stack<int> > shortestPaths(vertices.getSize());
        // Recorremos todos los vértices
        for (int i=0; i<vertices.getSize(); i++) {
            // Valdamos que el costo no sea infinito
                // Agregamos la pila del vértice actual su índice
                shortestPaths[i].push(i);
                // Creamos ubna variable para guardar el índice del path
                int pathIndex = path[i];
                // Iteramos mientras pathIndex sea diferente de -1
                while (pathIndex != -1) {
                    // Agregamos el path index a la pila
                    shortestPaths[i].push(pathIndex);   
                    // Actualizamos el path index con el valor del path de path index
                    pathIndex = path[pathIndex];
                }
            
        }
        // Imprimimos el resultado
        // Iteramos todos los vértices
        
        cout << vertices.table[vertexIndex2] << " -> ";
            // Valid[amos que la pila no sea vacía o que el costo no sea infinito
                // Iteramos mientas la pila no sea vacía
                while (!shortestPaths[vertexIndex2].empty()) {
                    // Imprimimos el primer elemento de la pila
                    //cout << shortestPaths[i].top() << " ";
                    // Sacamos el primer elemento de la pila
                    cout<<vertices.table[shortestPaths[vertexIndex2].top()]<<" ";
                    shortestPaths[vertexIndex2].pop();
                }
                // Imprimimos el peso
                cout << "- "; 
                if(cost[vertexIndex2]!=INT_MAX){
                    int tin2=min[vertexIndex2];
                    cout<<"DISTANCIA:" <<km[vertexIndex2]<<"km"<<" TIEMPO: " <<tin2 << "h :" << min[vertexIndex2]%60 << "min"<<endl;

                }else {
                cout<<"No existe esa ruta"<<endl;   
                }
        
    } else {
        throw invalid_argument("El vértice no existe");
    }

}


#endif /* Graph_h */