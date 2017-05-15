
/*****************************
* Name: Sabit Gökberk Karaca *
* Student ID: 21401862 *******
* Course: CS201 **************
* Section : 2 ****************
******************************/
class Flight;

class ReservationSystem {

public:
    ReservationSystem();
    ~ReservationSystem();

    void addFlight( const int flightNo, const int rowNo, const int seatNo);
    void cancelFlight( const int flightNo);

    void showAllFlights();
    void showFlight( const int flightNo);

    int makeReservation( const int flightNo, const int numPassengers,
                         const int* seatRow, const char* saetCol);

    void cancelReservation( const int resCode);
    void showReservation( const int resCode);

private:
    Flight* findFlight( int flightNo);

    Flight* allFlights;
    int flightSize;

};
