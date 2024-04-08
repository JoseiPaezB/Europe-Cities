#pragma once 
#include <string>
#include "HashCities.h"
using namespace std;
template<class T> 
struct EdgeCity{
    T originCity;
    T targetCity; 
    string trainTimeMins, trainTimeHour , carTimeMins, carTimeHour;
    EdgeCity(); 
    EdgeCity(T originCity, T targetCity); 
    EdgeCity(T originCity, T targetCity, string trainTimeMins, string trainTimeHour , string carTimeMins, string carTimeHour);

};


template<class T> 
EdgeCity<T>::EdgeCity(){
    trainTimeHour= "000"; 
    trainTimeMins= "00:00" ;
    carTimeHour= "000";
    carTimeMins= "00:00";}

template<class T>
EdgeCity<T>::EdgeCity(T originCity, T targetCity){
    this->originCity=originCity; 
    this->targetCity=targetCity; 
    
    
}

template<class T>
EdgeCity<T>::EdgeCity(T originCity, T targetCity,string trainTimeMins, string trainTimeHour , string carTimeMins, string carTimeHour){
    this->originCity=originCity; 
    this->targetCity=targetCity;; 
    this->trainTimeMins=trainTimeMins;
    this->trainTimeHour=trainTimeHour;
    this->carTimeMins=carTimeMins;
    this->carTimeHour=carTimeHour;
}