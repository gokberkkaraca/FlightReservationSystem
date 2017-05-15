#include "Flight.h"
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
Flight::Flight(){
    flightNo = 0;
    rowNo = 0;
    seatNo = 0;
    lastResNo = 1;
    reservationsSize = 0;
    reservations = NULL;
    allSeats = NULL;
}


// Constructor with parameters
Flight::Flight(const int flightNo, const int rowNo, const int seatNo) {

    // Set the given values
    this->flightNo = flightNo;
    this->rowNo = rowNo;
    this->seatNo = seatNo;

    reservations = NULL;
    reservationsSize = 0;
    lastResNo = 1;

    // Create the 2D array for all seats
    allSeats = new int*[rowNo];
    for ( int i = 0; i < rowNo; i++)
        allSeats[i] = new int[seatNo];

    // Set all the seats, 0: Empty, 1: Reserved
    for ( int i = 0; i < rowNo; i++) {
        for ( int j = 0; j < seatNo; j++)
            allSeats[i][j] = 0;
    }
}


// Destructor
Flight::~Flight(){

    if ( allSeats != NULL){

        // Delete the arrays that are stored in each row
        for ( int i = 0; i < rowNo; i++){
            delete[] allSeats[i];
            allSeats[i] = NULL;
        }

        // Delete the rows
        delete[] allSeats;
        allSeats = NULL;
    }

    // Delete the reservations array
    if ( reservations != NULL) {
        delete[] reservations;
        reservations = NULL;
    }
}


// Prints the 2D array of that flight
void Flight::showFlight(){

    cout << endl << "Flight " << flightNo << " has " << findEmptySeat() << " available seats" << endl;

    char charArray[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    cout << "\t";
    for ( int i = 0; i < seatNo; i++)
        cout << charArray[i] << "\t";
    cout << endl;

    // Iterate the seats
    for ( int i = 0; i < rowNo; i++) {
        cout << i + 1 << "\t";
        for ( int j = 0; j < seatNo; j++)
        {
            // Prints O if the seat is empty
            if ( allSeats[i][j] == 0)
                cout << charArray[14]  << "\t";
            // Prints X if the seat is reserved
            else
                cout << charArray[23] << "\t";
        }
        cout << endl;
    }

    cout << endl;
}


// Find the number of empty seats, will be used in other functions
int Flight::findEmptySeat(){

    int counter = 0;

    // Iterate all seats and check if it is empty or not
    for ( int i = 0; i < rowNo; i++) {
        for ( int j = 0; j < seatNo; j++)
            if ( allSeats[i][j] == 0)
                counter++;
    }

    return counter;
}


// Return the reservations array
Reservation* Flight::getReservations() {
    return reservations;
}


// Find the cell row and column from the input arrays, will be used in other functions
void Flight::findCell(int* row, int* col, const char seatChar) {

    // Convert rowNo to index
    (*row)--;

    // Convert seat char to index
    char charArray[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for ( int i = 0; i < 26; i++)
        if ( seatChar == charArray[i])
            *col = i;

}


// This method takes the number of passengers, rows of the seats as integers and columns of seats as characters
int Flight::makeReservation(const int numPassengers, const int* seatRow, const char* seatCol) {

        int row = 0;
        int col = 0;
        int unavailableSeatNum = 0;

        cout << "Seats ";

        //Check seat availability for each seat
        for ( int i = 0; i < numPassengers; i++) {
            row = seatRow[i];
            findCell(&row, &col, seatCol[i]);
            if ( allSeats[row][col] == 1) {
                unavailableSeatNum++;
                cout << row + 1 << seatCol[i] << " ";
            }
        }

        // If there are one or more unavailable seats, print them and return -1
        if ( unavailableSeatNum > 0){
            cout << "are not available" << endl;
            return -1;
        }


        // If all of them are empty, make the reservation
        for ( int i = 0; i < numPassengers; i++) {
                row = seatRow[i];
                findCell(&row, &col, seatCol[i]);
                allSeats[row][col] = 1;
        }

        cout << "are available" << endl;

        // Add the reservation and return the reservation code
        int reservationCode = addReservation(numPassengers, seatRow, seatCol);
        return reservationCode;
}


// Adds a new reservation by using the input arrays, will be used as a sub-function for makeReservation
int Flight::addReservation(const int numPassengers, const int* seatRow, const char* seatCol) {

    // If it is the first reservation
    if ( reservationsSize == 0) {
        reservationsSize++;
        reservations = new Reservation[reservationsSize];

        reservations[reservationsSize - 1].setNumPassengers(numPassengers);
        reservations[reservationsSize - 1].setRow(seatRow);
        reservations[reservationsSize - 1].setCol(seatCol);

        // Create a unique reservation code, for example if the flight is no 4 and it is 7. reservation of this flight,
        // Reservation code will be 4 * 100 + 7 = 407
        reservations[reservationsSize -1].setResCode(flightNo * 100 + lastResNo);
        lastResNo++;

        return reservations[reservationsSize - 1].getResCode();
    }

    // If it is not the first reservation
    else {
        // Copy the old array to a temporary array
        Reservation* temp = reservations;
        int tempSize = reservationsSize;

        // Allocate new memory with the size + 1
        reservationsSize++;
        reservations = new Reservation[reservationsSize];

        // Copy the old elements to new array
        for ( int i = 0; i < tempSize; i++)
            reservations[i].deepCopy(&(temp[i]));

        // Add the new element to the end of array
        reservations[reservationsSize - 1].setNumPassengers(numPassengers);
        reservations[reservationsSize - 1].setRow(seatRow);
        reservations[reservationsSize - 1].setCol(seatCol);

        // Create a unique reservation code, for example if the flight is no 4 and it is 7. reservation of this flight,
        // Reservation code will be 4 * 100 + 7 = 407
        reservations[reservationsSize -1].setResCode(flightNo * 100 + lastResNo);
        lastResNo++;

        delete [] temp;
        return reservations[reservationsSize - 1].getResCode();
    }
}


// Cancel a reservation when the reservation number is given
void Flight::cancelReservation(const int resCode){

    int index = -1;

    // Iterate the reservations for this flight to find the specific reservation
    for ( int i = 0; i < reservationsSize; i++){
        if ( reservations[i].getResCode() == resCode)
            index = i;
    }

    if ( index == -1){
        cout << "No reservations are found under code " << resCode << endl;
        return;
    }
    else {

        int row = 0;
        int col = 0;

        // Make the seats available again
        for ( int i = 0; i < reservations[index].getNumPassengers(); i++)
        {
            row = reservations[index].getRow()[i];
            findCell(&row, &col, reservations[index].getCol()[i]);
            allSeats[row][col] = 0;
        }

        // Delete the reservation
        deleteReservation(index);
    }
}


// The method that handles the array operations while canceling a reservation
void Flight::deleteReservation(int index){

    // If there is just 1 reservation on that flight, delete its reservation array
    if ( reservationsSize == 1) {
        reservationsSize = 0;
        delete[] reservations;
        reservations = NULL;
    }
    // If there are more than one reservations, delete only the specific reservation
    else {
        Reservation* temp = reservations;
        int tempSize = reservationsSize;

        reservationsSize--;
        reservations = new Reservation[reservationsSize];

        for ( int i = 0; i < index; i++)
            reservations[i].deepCopy(&(temp[i]));

        for ( int i = index + 1; i < tempSize; i++)
            reservations[i-1].deepCopy(&(temp[i]));

        delete[] temp;
    }
}


// It initializes a flight to given values
void Flight::initialize(int flightNo, int rowNo, int seatNo) {

    // Set the given values
    this->flightNo = flightNo;
    this->rowNo = rowNo;
    this->seatNo = seatNo;

    reservations = NULL;
    reservationsSize = 0;
    lastResNo = 1;

    // Create the 2D array for all seats
    allSeats = new int*[rowNo];
    for ( int i = 0; i < rowNo; i++)
        allSeats[i] = new int[seatNo];

    // Set all the seats, 0: Empty, 1: Reserved
    for ( int i = 0; i < rowNo; i++) {
        for ( int j = 0; j < seatNo; j++)
            allSeats[i][j] = 0;
    }
}


// It makes a deep copy of a flight
void Flight::deepCopy(Flight& f){
    this->flightNo = f.flightNo;
    this->rowNo = f.rowNo;
    this->seatNo = f.seatNo;
    this->reservationsSize = f.reservationsSize;
    this->lastResNo = f.lastResNo;

    // One by one copy
    if ( reservationsSize != 0) {
        this->reservations = new Reservation[reservationsSize];
        for ( int i = 0; i < reservationsSize; i++){
            reservations[i].setNumPassengers(f.reservations[i].getNumPassengers());
            reservations[i].setRow(f.reservations[i].getRow());
            reservations[i].setCol(f.reservations[i].getCol());
            reservations[i].setResCode(f.reservations[i].getResCode());
        }
    }

    // One by one copy
    this->allSeats = new int*[rowNo];
    for(int i = 0; i < rowNo; i++){
        allSeats[i] = new int[seatNo];
        for ( int j = 0; j < seatNo; j++) {
            allSeats[i][j] = f.allSeats[i][j];
        }
    }
}


// Prints the details of a reservation
void Flight::showReservation(int resCode){

    int index = -1;

    // Find the reservation
    for ( int i = 0; i < reservationsSize; i++)
        if ( reservations[i].getResCode() == resCode)
            index = i;

    // Print if it exists
    if ( index != -1)
        reservations[index].display();
    else
        cout << "No reservations are found under code " << resCode << endl;
}


// Returns the flight no
int Flight::getFlightNo() {
        return flightNo;
}
