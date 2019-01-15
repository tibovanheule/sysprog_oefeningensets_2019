#include "Timestamp.h"
int Timestamp::getDay(){
    return this->day;
}
int Timestamp::getMonth(){
    return this->month;
}
int Timestamp::getYear(){
    return this->year;
}
void Timestamp::setDay(int d){
    this->day = d;
}
void Timestamp::setMonth(int d){
    this->month = d;
}
void Timestamp::setYear(int d){
    this->year = d;
}
Timestamp::Timestamp():day(0),month(0),year(0){

}
Timestamp::Timestamp(int day, int month, int year):day(day),month(month),year(year){

}
Timestamp::Timestamp(Timestamp &timestamp) {
	this->day = timestamp.day;
	this->month = timestamp.month;
	this->year = timestamp.year;
}
Timestamp::~Timestamp(){}