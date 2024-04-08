#ifndef HashStudentId_h 
#define HashStudentId_h
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include "EdgeCity.h"
using namespace std;


template<class T> 
class Graph;



template<class T>
class HashCities { 
private: 
    vector<bool> status;

public: 
    vector<string> table; 
    int hash(string city); 
    int colission(string city);
    HashCities(); 
    void insert(string city); 
    void remove(string city);
    void remove2(int index);
    int findCuidad(string city); 
    void print(); 
    void print2(); 
    string getCityAtIndex(int index)const;
    string findCity(int index);
    int getSize(); 
    string operator[](int index);
    vector<string> getKeys() const;
    int getPivot(int left,int right); 
    friend class Graph<T>;

};






template<class T> 
vector<string>HashCities<T>::getKeys()const {
        vector<string> keys;
        for (const auto& entry : table) {
            if (!entry.empty()) {
                keys.push_back(entry);
            }
        }
        return keys;
    }

    // Resto de tu clase HashCities

template<class T>
string HashCities<T>::operator[](int index){
    return table[index];
}


template<class T>
string HashCities<T>::getCityAtIndex(int index)const{
        if (index >= 0 && index < table.size()) {
            return table[index];
        } else {
            throw out_of_range("Índice fuera de rango");
        }
    }

template<class T>
void HashCities<T>::print() { 
    int cont=0; 
    if(table.size()==0){
        cout<<"No hay elementos en la tabla"<<endl;
    }else{
        
        for (int i = 0; i < table.size(); i++) { 
            if (table[i] != "") { 
                cont++;
                cout <<cont<<"."<< " " << i << " --> " << table[i] << endl; 
            }
        }
    }

}

template<class T>
void HashCities<T>::print2() { 
    int cont=0; 
    if(table.size()==0){
        cout<<"No hay elementos en la tabla"<<endl;
    }else{
        
        for (int i = 0; i < table.size(); i++) { 
            if (table[i] != "") { 
                cont++;
                cout <<cont<<"."<< " " << i << " --> " << table[i]; 
            }
        }
    }

}

template<class T>
int HashCities<T>::hash(string city) { 
    int asciivalue=static_cast<int>(city[0]);
    int asciivalue2=static_cast<int>(city[-1]);
    int res = city.length()%1000; 
    int res2=res+asciivalue+asciivalue2;
    return res2; 
}







template<class T>
string HashCities<T>::findCity(int index) {
    // Validar que el índice esté dentro de los límites de la tabla
    if (index < 0 || index >= table.size()) {
        // Devolver una cadena vacía o lanzar una excepción, dependiendo de tus necesidades
        return "";  // O puedes lanzar una excepción aquí
    }

    // Verificar si el elemento en el índice es no vacío y no está marcado como eliminado
    if (!table[index].empty() && !status[index]) {
        // Devolver la ciudad en el índice dado
        return table[index];
    } else {
        // Buscar la ciudad en la tabla a partir del índice
        int newIndex = (index + 1) % table.size();
        while (index != newIndex && (!table[index].empty() || status[index])) {
            if (!table[newIndex].empty() && !status[newIndex]) {
                return table[newIndex];
            }
            newIndex = (newIndex + 1) % table.size();
        }
        // No se encontró la ciudad
        return "";
    }
}



template<class T>
HashCities<T>::HashCities() { 
    table.resize(1000); 
    status.resize(1000);
}

template<class T>
int HashCities<T>::getSize(){
    return 1000-849;
}

template<class T>
void HashCities<T>::insert(string city) { 
    // Validar si existe el elemento
    if (findCuidad(city) == -1) {
        // Obtengo el índice de la función de hashing
        int index = hash(city);
        // Revisamos si el índice esta vacío
        if (table[index].empty()) {
            // insertamos el dato
            table[index] = city;
            // Actualizamos el estado de newIndex
            status[index] = false;
        } else {
            // Creamos un índice auxiliar para determinar si ya le dimos la vuelta
            int newIndex = (index + 1) % table.size();
            // Recorremos la tabla mientras no le demos la vuelta y el valor no sea vacío
            while (newIndex != index && !table[newIndex].empty()) {
                // Recorremos newIndex
                newIndex = (newIndex + 1) % table.size();
            }
            // Validamos que no le hayamos dado la vuelta a la tabla
            if (newIndex != index) {
                // insertamos el dato
                table[newIndex] = city;
                // Actualizamos el estado de newIndex
                status[newIndex] = false;
            } else {
                // Le dimos la vuelta a la tabla, es decir la tabla esta llena
                throw invalid_argument("La tabla esta llena");
            }
        }
    } else {
        throw invalid_argument("El valor ya se encuentra en la tabla");
    }     
}


template<class T>
void HashCities<T>::remove(string city){
   // Buscamos el índice donde se encuentra el valor a borrar
    int index = findCuidad(city);
    // Validamos si lo encontramos
    if (index != -1) {
        // Lo removemos
        table[index] = "";
        // Actualizamos la tabla de estados
        status[index] = true;
        cout<<"Se elimino el elemento"<<endl;
    } else {
        throw invalid_argument("El valor no se encuentra en la tabla");
    }
}
template<class T>
void HashCities<T>::remove2(int index2){
   // Buscamos el índice donde se encuentra el valor a borrar
    string index = findCity(index2);
    // Validamos si lo encontramos
    if (index != "") {
        // Lo removemos
        table[index2] = "";
        // Actualizamos la tabla de estados
        status[index2] = true;
        cout<<"Se elimino el elemento"<<endl;
    } else {
        throw invalid_argument("El valor no se encuentra en la tabla");
    }
}

template<class T>
int HashCities<T>::findCuidad(string city) { 
     // Obtengo el índice de la función de hashing
    int index = hash(city);
    if (table[index] == city) {
        return index;
    } else {
        // Creamos un índice auxiliar para determinar si ya le dimos la vuelta
        int newIndex = (index + 1) % table.size();
        // Recorremos la tabla para buscar el elemento
        while (index != newIndex && (!table[index].empty() || status[index])) {
            // Validamos si el valor de la tabla en newIndex es igual al valor buscado
            if (table[newIndex] == city) {
                // Regresamos newIndex
                return newIndex;
            }
            // Incrementamos el valor de newIndex
            newIndex = (newIndex + 1) % table.size();
        }
        // No lo encontré
        return -1;
    }
}



#endif 