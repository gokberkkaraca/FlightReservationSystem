#include "Reservation.h"
#include <iostream>
using namespace std;

/*****************************
* Name: Sabit Gökberk Karaca *
* Student ID: 21401862 *******
* Course: CS201 **************
* Section : 2 ****************
******************************/

// Empty Constructor
Reservation::Reservation(){
    numPassengers = 0;
    resCode = 0;
    row = NULL;
    col = NULL;
}


// Constructor with parameters
Reservation::Reservation(const int numPassengers, const int* seatRow, const char* seatCol) {

    row = new int[numPassengers];
    col = new char[numPassengers];

    for ( int i = 0; i < numPassengers; i++) {
        row[i] = seatRow[i];
        col[i] = seatCol[i];
    }

    this->numPassengers = numPassengers;
}


// Destructor
Reservation::~Reservation(){

    if ( row != NULL) {
        delete[] row;
        row = NULL;
    }

    if ( col != NULL) {
        delete[] col;
        col = NULL;
    }
}


// Getter Methods
char* Reservation::getCol(){
    return col;
}

int* Reservation::getRow(){
    return row;
}

int Reservation::getNumPassengers() {
    return numPassengers;
}

int Reservation::getResCode(){
    return resCode;
}


// Setter Methods
void Reservation::setResCode(int resCode) {
    this->resCode = resCode;
}

void Reservation::setNumPassengers( int num) {
    numPassengers = num;
}

void Reservation::setCol(const char* sCol) {
    col = new char[numPassengers];
    for ( int i = 0; i < numPassengers; i++) {
        col[i] = sCol[i];
    }
}

void Reservation::setRow(const int* sRow) {
    row = new int[numPassengers];
    for ( int i = 0; i < numPassengers; i++) {
        row[i] = sRow[i];
    }
}


// Make a deep copy of a reservation
void Reservation::deepCopy(Reservation* r) {

    setNumPassengers((*r).getNumPassengers());
    setRow((*r).getRow());
    setCol((*r).getCol());
    setResCode((*r).getResCode());

}


// Display a reservation with its reservation code and seats
void Reservation::display(){

    cout << "Reservations under code " << resCode << " in flight " << resCode / 100 << ": ";
    for ( int i = 0; i < numPassengers; i++) {
        cout << row[i] << col[i] << " ";
    }
    cout << endl;
}
