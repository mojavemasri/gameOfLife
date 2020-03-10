#include <iostream>
#include "node.cpp"
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

class grid{
public:
  //constructors
  grid();
  grid(int width, int length, float density, int mode, int output);
  grid(string fname, int mode, int output);
  ~grid();

  void run();
  void round(int i);
  //auxFunctions
  void initGrid(float density);
  void initFile(char *line, int i);
  void assessNeighbors();
  void assessNeighbors(int i, int j);
  int assessLife();
  void checkNode(node &nmain, node &check);
  void print();
  void print(int i);
  int getNodesAlive();
  void normalMode();
  void mirrorMode();
  void doughnutMode();
  bool getChanges();
  void setChanges(bool newChange);

private:
  node** field;
  int m_width;
  int m_length;
  int nodesAlive;
  int m_mode;
  int changes;
  int m_output;
};
