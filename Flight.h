
/*****************************
* Name: Sabit Gökberk Karaca *
* Student ID: 21401862 *******
* Course: CS201 **************
* Section : 2 ****************
******************************/
class Reservation;

class Flight{

public:

    Flight();
    Flight(const int flightNo, const int rowNo, const int seatNo);
    ~Flight();

    int makeReservation(const int numPassengers, const int* seatRow, const char* seatCol);
    void cancelReservation(const int resCode);

    void showFlight();
    void showReservation(int resCode);

    void initialize(int flightNo, int rowNo, int seatNo);
    void deepCopy(Flight& f);

    int findEmptySeat();
    int getFlightNo();

private:

    int addReservation(const int numPassengers, const int* seatRow, const char* seatCol);
    void deleteReservation(int index);

    Reservation* getReservations();
    void findCell(int* row, int* col, const char seatChar);

    int flightNo;
    int rowNo;
    int seatNo;
    int lastResNo;
    int** allSeats;
    int reservationsSize;
    Reservation* reservations;

};
