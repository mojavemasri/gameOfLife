#include <iostream>
#include <string>
using namespace std;

class node{
  public:
//constructors
    node();
    node(bool alive, int surr);
    ~node();
//methods
    bool getAlive();
    void setAlive(bool newAlive);
    int getSurr();
    bool checkAlive();
    void setSurr(int newSurr);
    void incSurr();
    void decSurr();
    char toChar();
    void print();
  private:

//member variables
    bool m_alive;
    int m_surr;
};
