
/*****************************
* Name: Sabit Gökberk Karaca *
* Student ID: 21401862 *******
* Course: CS201 **************
* Section : 2 ****************
******************************/

class Reservation {

public:

    Reservation();
    Reservation(const int numPassengers, const int* seatRow, const char* seatCol);
    ~Reservation();

    int getNumPassengers();
    void setNumPassengers(int num);

    int* getRow();
    void setRow(const int* sRow);

    char* getCol();
    void setCol(const char* sCol);

    int getResCode();
    void setResCode(int resCode);

    void display();
    void deepCopy(Reservation* r);

private:
    int numPassengers;
    int resCode;
    int* row;
    char* col;
};
