#include "ReservationSystem.h"
#include "Flight.h"
#include <iostream>
using namespace std;

/*****************************
* Name: Sabit Gökberk Karaca *
* Student ID: 21401862 *******
* Course: CS201 **************
* Section : 2 ****************
******************************/

// Empty constructor
ReservationSystem::ReservationSystem(){
    allFlights = NULL;
    flightSize = 0;
}


// Destructor
ReservationSystem::~ReservationSystem(){
    if ( allFlights != NULL){
        delete[] allFlights;
        allFlights = NULL;
    }
}


// It creates a new flight and adds to the end of flight list
void ReservationSystem::addFlight(const int flightNo, const int rowNo, const int seatNo) {

    // Check if the flight exists or not
    for ( int i = 0; i < flightSize; i++) {
        if ( allFlights[i].getFlightNo() == flightNo){
            cout << "The flight " << flightNo << " already exists" << endl;
            return;
        }

    }

    // If it is the first time
    if ( flightSize == 0) {
        flightSize++;
        allFlights = new Flight[flightSize];
        allFlights[flightSize - 1].initialize(flightNo, rowNo, seatNo);
        cout << "New Flight " << flightNo << " has been added" << endl;
    }
    // If there are other flights
    else {
        Flight* tempFlights = allFlights;
        int tempSize = flightSize;

        flightSize++;
        allFlights = new Flight[flightSize];


        for ( int i = 0; i < tempSize; i++) {
            allFlights[i].deepCopy(tempFlights[i]);
        }

        allFlights[flightSize - 1].initialize(flightNo, rowNo, seatNo);
        cout << "New Flight " << flightNo << " has been added" << endl;

        delete[] tempFlights;

    }
}


// Prints the flight numbers and empty seats of current flights
void ReservationSystem::showAllFlights(){

    if ( flightSize == 0)
        cout << "No flights exist" << endl << endl;
    else {
        cout << endl << "Flights currently operated: " << endl;
        for ( int i = 0; i < flightSize; i++)
            cout << "Flight No: " << allFlights[i].getFlightNo() << "\t(" << allFlights[i].findEmptySeat() << " available seats)" << endl;
        cout << endl;
    }
}


// It prints the detailed information of a flight
void ReservationSystem::showFlight(const int flightNo){
    Flight* f = findFlight(flightNo);

    if (f != NULL)
        f->showFlight();
    else
        cout << "Flight " << flightNo << " does not exist" << endl;
}


// It returns a pointer of a flight with a specific flight no
Flight* ReservationSystem::findFlight(int flightNo){

    int index = -1;

    // Check if the flight exists or not
    for ( int i = 0; i < flightSize; i++){
        if ( allFlights[i].getFlightNo() == flightNo)
            index = i;
    }

    // Return the flight or return null if it does not exist
    if ( index == -1) {
        return NULL;
    }
    else
        return &(allFlights[index]);
}


// Creates a new reservation for the seats of a specific flight
int ReservationSystem::makeReservation(const int fligtNo, const int numPassengers, const int* seatRow, const char* seatCol){

    // Find the flight
    Flight* f = findFlight(fligtNo);

    // Call the make reservation function of that flight
    if ( f != NULL){
        return (*f).makeReservation(numPassengers, seatRow, seatCol);
    }
    else {
        cout << "Flight: " << fligtNo << " does not exist" << endl;
        return -1;
    }
}


// It cancels a flight with its reservations
void ReservationSystem::cancelFlight(const int flightNo){

    // Find the index of flight
    int index = -1;
    for ( int i = 0; i < flightSize; i++)
        if ( allFlights[i].getFlightNo() == flightNo)
            index = i;

    // Remove the flight from the array if it exists
    if ( index == -1)
        cout << "Flight " << flightNo << " does not exist" << endl;
    else {

        // If it is the only flight, delete allFlights array
        if ( flightSize == 1) {
            delete[] allFlights;
            allFlights = NULL;
            flightSize = 0;
            cout << "Flight " << flightNo << " and all of its reservations are canceled" << endl;
        }
        // If there are other flights, just delete the specific Flight
        else {
            Flight* temp = allFlights;
            int tempSize = flightSize;

            flightSize--;
            allFlights = new Flight[flightSize];

            for ( int i = 0; i < index; i++)
                allFlights[i].deepCopy(temp[i]);

            for ( int i = index + 1; i < tempSize; i++)
                allFlights[i-1].deepCopy(temp[i]);

            cout << "Flight " << flightNo << " and all of its reservations are canceled" << endl;
            delete[] temp;
        }
    }

}


// Print the details of a reservation
void ReservationSystem::showReservation(const int resCode){

    // Find flight no
    int flightNo = resCode / 100;

    // Find flight
    Flight* f = findFlight(flightNo);

    // Call its showReservation function
    if ( f != NULL)
        f->showReservation(resCode);
    else
        cout << "No reservations are found under code " << resCode << endl;
}


// Cancel a reservation
void ReservationSystem::cancelReservation(const int resCode) {

    // Find flight no
    int flightNo = resCode / 100;

    // Find the flight
    Flight* f = findFlight(flightNo);

    // Call its cancelReservation function if it exists
    if ( f != NULL)
        f->cancelReservation(resCode);
    else
        cout << "No reservations are found under code " << resCode << endl;
}
