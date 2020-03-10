#include "grid.h"

grid::grid(){
  m_width = 10;
  m_length = 10;
  m_mode = 0;
  field = new node*[m_width];
  for(int i = 0; i < m_width; ++i){
    field[i] = new node[m_length];
  }
  nodesAlive = 0;
  /*for(int i = 0; i < m_width; ++i){
    for(int k = 0; k < m_length; ++k){
      &field[i][k] = NULL;
    }
  }*/
}

grid::grid(string fname, int mode, int output){
  ifstream inFS;
  inFS.open(fname);
  char *line;
  inFS >> m_width;
  inFS >> m_length;
  line = new char[m_length];
  field = new node*[m_width];
  for(int i = 0; i < m_width; ++i){
    field[i] = new node[m_length];
    inFS >> line;
    initFile(line, i);
  }
  m_mode = mode;
  m_output = output;
}

grid::grid(int width, int length, float density, int mode, int output){
  m_width = width;
  m_length = length;
  m_mode = mode;
  m_output = output;
  field = new node*[m_width];
  for(int i = 0; i < m_width; ++i){
    field[i] = new node[m_length];
  }
  if(density > 1 || density <= 0){
    cout << "Invalid density input, density must be strictly greater than 0 and less than 1. Density has been set to 0.4." << endl;
    density = 0.4;
  }
  initGrid(density);
}

grid::~grid(){
  delete field;
}

void grid::initFile(char *line, int i){
  for(int j = 0; j < m_length; j++){
    if(line[j] == 'x'){
      cout << 'x';
      node n(true, 0);
      (field[i])[j] = n;
    }
    else if(line[j] == '-'){
      cout << '-';
      node n(false, 0);
      (field[i])[j] = n;
    }
  }
  cout << endl;
}

void grid::initGrid(float density){
  srand(time(NULL));
  for(int i = 0; i < m_width; ++i){
    for(int j = 0; j < m_width; ++j){
      float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  //    cout << a << " < " << density << "  ";
      if(a < density){
        node n(true, 0);
    //    cout << n.getAlive();
        (field[i])[j] = n;
        nodesAlive++;
        node *ptr = &(field[i])[j];
    //   cout << ptr->toChar();
      }
      else{
        node n(false, 0);
  //      cout << n.getAlive();
        (field[i])[j] = n;
        node *ptr = &(field[i])[j];
  //     cout << ptr->toChar();
      }
    }
//   cout << endl;
  }
}

void grid::assessNeighbors(){
  if(m_mode == 0){
    normalMode();
  }
  else if(m_mode == 1){
    mirrorMode();
  }
  else if(m_mode == 2){
    doughnutMode();
  }
}

void grid::normalMode(){

  for(int i = 0; i < m_width; ++i){
  //  node **loop = &field[i];
    for(int j = 0; j < m_length; ++j){

      //      cout << "testing i = " << i << ", j = " << j << endl;
          //node *iter = loop[j];
          field[i][j].setSurr(0);

          if(i == 0){
            if(j == m_length - 1){
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i+1][j-1]);
            }
            else if(j == 0){
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i+1][j+1]);
              checkNode(field[i][j], field[i][j+1]);
            }
            else{
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i+1][j+1]);
              checkNode(field[i][j], field[i+1][j-1]);
              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j-1]);
            }
          }

          else if(i == m_width - 1){
            if(j == m_length - 1){
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i-1][j-1]);
            }
            else if(j == 0){
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i-1][j+1]);
              checkNode(field[i][j], field[i][j+1]);
            }
            else{
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i-1][j+1]);
              checkNode(field[i][j], field[i-1][j-1]);
              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j-1]);
            }
      //      cout << field[i][j].getSurr() << endl;
          }

          else if(j == 0){
            checkNode(field[i][j], field[i-1][j]);
            checkNode(field[i][j], field[i+1][j]);
            checkNode(field[i][j], field[i][j+1]);
            checkNode(field[i][j], field[i+1][j+1]);
            checkNode(field[i][j], field[i-1][j+1]);
          }

          else if(j == m_length -1){
            field[i][j].setSurr(0);
        //    cout << "i = " << i << ", j = " << j << endl;
        //    cout << "Before: " << field[i][j].getSurr() << endl;
            checkNode(field[i][j], field[i-1][j]);
        //    cout << field[i-1][j].toChar() << endl;
            checkNode(field[i][j], field[i+1][j]);
        //    cout << field[i-1][j-1].toChar() << endl;
            checkNode(field[i][j], field[i][j-1]);
        //    cout << field[i][j-1].toChar() << endl;
            checkNode(field[i][j], field[i+1][j-1]);
        //    cout << field[i+1][j-1].toChar() << endl;
            checkNode(field[i][j], field[i-1][j-1]);
        //    cout << field[i+1][j].toChar() << endl;
        //    cout << "After: " << field[i][j].getSurr() << endl;
          }

          else{
            checkNode(field[i][j], field[i-1][j]);
            checkNode(field[i][j], field[i+1][j]);
            checkNode(field[i][j], field[i][j+1]);
            checkNode(field[i][j], field[i+1][j+1]);
            checkNode(field[i][j], field[i-1][j+1]);
            checkNode(field[i][j], field[i-1][j-1]);
            checkNode(field[i][j], field[i+1][j-1]);
            checkNode(field[i][j], field[i][j-1]);
          }
      node *ptr = &field[i][j];
  //    cout << field[i][j].getSurr() << endl;
    }
  }
  }

void grid::doughnutMode(){
      for(int i = 0; i < m_width; ++i){
        for(int j = 0; j < m_length; ++j){
              field[i][j].setSurr(0);
              if(i == 0){
                if(j == m_length - 1){
                  checkNode(field[i][j], field[i][j-1]);
                  checkNode(field[i][j], field[i][0]);
                  checkNode(field[i][j], field[i+1][j]);
                  checkNode(field[i][j], field[i+1][j-1]);
                  checkNode(field[i][j], field[i+1][0]);
                  checkNode(field[i][j], field[m_width-1][j-1]);
                  checkNode(field[i][j], field[m_width-1][j]);
                  checkNode(field[i][j], field[m_width-1][0]);
                }
                else if(j == 0){
                  checkNode(field[i][j], field[i][m_length-1]);
                  checkNode(field[i][j], field[i][j+1]);
                  checkNode(field[i][j], field[i+1][j]);
                  checkNode(field[i][j], field[i+1][m_length-1]);
                  checkNode(field[i][j], field[i+1][j+1]);
                  checkNode(field[i][j], field[m_width-1][m_length-1]);
                  checkNode(field[i][j], field[m_width-1][j]);
                  checkNode(field[i][j], field[m_width-1][j+1]);
                }
                else{
                  checkNode(field[i][j], field[i][j-1]);
                  checkNode(field[i][j], field[i][j+1]);
                  checkNode(field[i][j], field[i+1][j]);
                  checkNode(field[i][j], field[i+1][j-1]);
                  checkNode(field[i][j], field[i+1][j+1]);
                  checkNode(field[i][j], field[m_width-1][j-1]);
                  checkNode(field[i][j], field[m_width-1][j]);
                  checkNode(field[i][j], field[m_width-1][j+1]);
                }
              }

              else if(i == m_width - 1){
                if(j == m_length - 1){
                  checkNode(field[i][j], field[i][j-1]);
                  checkNode(field[i][j], field[i][0]);
                  checkNode(field[i][j], field[0][j]);
                  checkNode(field[i][j], field[0][j-1]);
                  checkNode(field[i][j], field[0][0]);
                  checkNode(field[i][j], field[i-1][j-1]);
                  checkNode(field[i][j], field[i-1][j]);
                  checkNode(field[i][j], field[i-1][0]);
                }
                else if(j == 0){
                  checkNode(field[i][j], field[i][m_length-1]);
                  checkNode(field[i][j], field[i][j+1]);
                  checkNode(field[i][j], field[0][j]);
                  checkNode(field[i][j], field[0][m_length-1]);
                  checkNode(field[i][j], field[0][j+1]);
                  checkNode(field[i][j], field[i-1][m_length-1]);
                  checkNode(field[i][j], field[i-1][j]);
                  checkNode(field[i][j], field[i-1][j+1]);
                }
                else{
                  checkNode(field[i][j], field[i][j-1]);
                  checkNode(field[i][j], field[i][j+1]);

                  checkNode(field[i][j], field[0][j]);

                  checkNode(field[i][j], field[0][j-1]);

                  checkNode(field[i][j], field[0][j+1]);

                  checkNode(field[i][j], field[i-1][j-1]);

                  checkNode(field[i][j], field[i-1][j]);
                  checkNode(field[i][j], field[i-1][j+1]);
                }
              }

              else if(j == 0){
                checkNode(field[i][j], field[i-1][j]);
                checkNode(field[i][j], field[i+1][j]);
                checkNode(field[i][j], field[i][j+1]);
                checkNode(field[i][j], field[i+1][j+1]);
                checkNode(field[i][j], field[i-1][j+1]);
                checkNode(field[i][j], field[i][m_length-1]);
                checkNode(field[i][j], field[i+1][m_length-1]);
                checkNode(field[i][j], field[i-1][m_length-1]);
              }

              else if(j == m_length -1){
                field[i][j].setSurr(0);
                checkNode(field[i][j], field[i-1][j]);
                checkNode(field[i][j], field[i+1][j]);
                checkNode(field[i][j], field[i][j-1]);
                checkNode(field[i][j], field[i+1][j-1]);
                checkNode(field[i][j], field[i-1][j-1]);
                checkNode(field[i][j], field[i][0]);
                checkNode(field[i][j], field[i+1][0]);
                checkNode(field[i][j], field[i-1][0]);
              }

              else{
                checkNode(field[i][j], field[i-1][j]);
                checkNode(field[i][j], field[i+1][j]);
                checkNode(field[i][j], field[i][j+1]);
                checkNode(field[i][j], field[i+1][j+1]);
                checkNode(field[i][j], field[i-1][j+1]);
                checkNode(field[i][j], field[i-1][j-1]);
                checkNode(field[i][j], field[i+1][j-1]);
                checkNode(field[i][j], field[i][j-1]);
              }
          node *ptr = &field[i][j];
      //    cout << field[i][j].getSurr() << endl;
        }
      }
}
void grid::mirrorMode(){

  for(int i = 0; i < m_width; ++i){
  //  node **loop = &field[i];
    for(int j = 0; j < m_length; ++j){

      //      cout << "testing i = " << i << ", j = " << j << endl;
          //node *iter = loop[j];
          field[i][j].setSurr(0);

          if(i == 0){
            if(j == m_length - 1){
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i+1][j]);

              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i][j-1]);

              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);

              checkNode(field[i][j], field[i+1][j-1]);
            }
            else if(j == 0){
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i+1][j]);

              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j+1]);

              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);


              checkNode(field[i][j], field[i+1][j+1]);
            }
            else{
              checkNode(field[i][j], field[i+1][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i+1][j+1]);
              checkNode(field[i][j], field[i+1][j-1]);

              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j+1]);

              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i][j-1]);
            }
          }

          else if(i == m_width - 1){
            if(j == m_length - 1){
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i-1][j]);

              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i][j-1]);

              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);

              checkNode(field[i][j], field[i-1][j-1]);
            }
            else if(j == 0){
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i-1][j]);

              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j+1]);

              checkNode(field[i][j], field[i-1][j+1]);

              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i][j]);
            }
            else{
              checkNode(field[i][j], field[i-1][j]);
              checkNode(field[i][j], field[i][j]);
              checkNode(field[i][j], field[i-1][j+1]);
              checkNode(field[i][j], field[i-1][j-1]);

              checkNode(field[i][j], field[i][j+1]);
              checkNode(field[i][j], field[i][j+1]);

              checkNode(field[i][j], field[i][j-1]);
              checkNode(field[i][j], field[i][j-1]);

            }
      //      cout << field[i][j].getSurr() << endl;
          }

          else if(j == 0){
            checkNode(field[i][j], field[i-1][j]);
            checkNode(field[i][j], field[i-1][j]);

            checkNode(field[i][j], field[i+1][j]);
            checkNode(field[i][j], field[i+1][j]);

            checkNode(field[i][j], field[i][j+1]);
            checkNode(field[i][j], field[i+1][j+1]);
            checkNode(field[i][j], field[i-1][j+1]);
            checkNode(field[i][j], field[i][j]);
          }

          else if(j == m_length -1){
            field[i][j].setSurr(0);
           //cout << endl;
            //cout << "i = " << i << ", j = " << j << endl;
            //cout << "Before: " << field[i][j].getSurr() << endl;
            checkNode(field[i][j], field[i-1][j]);
            checkNode(field[i][j], field[i-1][j]);

            checkNode(field[i][j], field[i+1][j]);
            checkNode(field[i][j], field[i+1][j]);

            checkNode(field[i][j], field[i][j-1]);
            checkNode(field[i][j], field[i+1][j-1]);
            checkNode(field[i][j], field[i-1][j-1]);
            checkNode(field[i][j], field[i][j]);
            //cout << "After: " << field[i][j].getSurr() << endl;
          }

          else{
            checkNode(field[i][j], field[i-1][j]);
            checkNode(field[i][j], field[i+1][j]);
            checkNode(field[i][j], field[i][j+1]);
            checkNode(field[i][j], field[i+1][j+1]);
            checkNode(field[i][j], field[i-1][j+1]);
            checkNode(field[i][j], field[i-1][j-1]);
            checkNode(field[i][j], field[i+1][j-1]);
            checkNode(field[i][j], field[i][j-1]);
          }
      node *ptr = &field[i][j];
  //    cout << field[i][j].getSurr() << endl;
    }
  }
}

void grid::assessNeighbors(int i, int j){
  if(i == 0){
    if(j == m_length - 1){
      checkNode(field[i][j], field[i+1][j]);
      checkNode(field[i][j], field[i][j-1]);
      checkNode(field[i][j], field[i+1][j-1]);
    }
    else if(j == 0){
      checkNode(field[i][j], field[i+1][j]);
      checkNode(field[i][j], field[i+1][j+1]);
      checkNode(field[i][j], field[i][j+1]);
    }
    else{
      checkNode(field[i][j], field[i+1][j]);
      checkNode(field[i][j], field[i+1][j+1]);
      checkNode(field[i][j], field[i+1][j-1]);
      checkNode(field[i][j], field[i][j+1]);
      checkNode(field[i][j], field[i][j-1]);
    }
  }

  else if(i == m_width - 1){
    if(j == m_length - 1){
      checkNode(field[i][j], field[i-1][j]);
      checkNode(field[i][j], field[i][j-1]);
      checkNode(field[i][j], field[i-1][j-1]);
    }
    else if(j == 0){
      checkNode(field[i][j], field[i-1][j]);
      checkNode(field[i][j], field[i-1][j+1]);
      checkNode(field[i][j], field[i][j+1]);
    }
    else{
      checkNode(field[i][j], field[i-1][j]);
      checkNode(field[i][j], field[i-1][j+1]);
      checkNode(field[i][j], field[i-1][j-1]);
      checkNode(field[i][j], field[i][j+1]);
      checkNode(field[i][j], field[i][j-1]);
    }
    cout << field[i][j].getSurr() << endl;
  }

  else if(j == 0){
    checkNode(field[i][j], field[i-1][j]);
    checkNode(field[i][j], field[i+1][j]);
    checkNode(field[i][j], field[i][j+1]);
    checkNode(field[i][j], field[i+1][j+1]);
    checkNode(field[i][j], field[i-1][j+1]);
  }

  else if(j == m_length){
//    cout << endl;
//    cout << "Before: " << field[i][j].getSurr() << endl;
    checkNode(field[i][j], field[i-1][j]);
    checkNode(field[i][j], field[i+1][j]);
    checkNode(field[i][j], field[i][j-1]);
    checkNode(field[i][j], field[i+1][j-1]);
    checkNode(field[i][j], field[i-1][j-1]);
//    cout << "After: " << field[i][j].getSurr() << endl;
  }

  else{
    checkNode(field[i][j], field[i-1][j]);
    checkNode(field[i][j], field[i+1][j]);
    checkNode(field[i][j], field[i][j+1]);
    checkNode(field[i][j], field[i+1][j+1]);
    checkNode(field[i][j], field[i-1][j+1]);
    checkNode(field[i][j], field[i-1][j-1]);
    checkNode(field[i][j], field[i+1][j-1]);
    checkNode(field[i][j], field[i][j-1]);
  }
}

int grid::assessLife(){
  int living = 0;
  bool live = false;
  bool init = false;
  for(int i = 0; i < m_width; ++i){
    for(int j = 0; j < m_length; ++j){
      init = field[i][j].getAlive();
      if(j == m_length-1){
    //    cout << "i = " << i << ", j = " << j << endl;
    //    cout << "Before: " << field[i][j].getAlive() << endl;
      //  cout << "Neighbors: " << field[i][j].getSurr() << endl;
      //fix below!

//       assessNeighbors(i,j);
     }
      //  cout << "assessNeighbors after check: " << field[i][j].getSurr() << endl;


        live = field[i][j].checkAlive();
    if(live){
    //  cout << "live!" << endl;
      living++;
    }
    if(init != field[i][j].getAlive()){
  //    cout << "WOMP WOMP WOMP" << endl;
      changes = true;}
      if(changes){
      //  cout << "i = " << i << ", j = " << j << endl;
  }

  }
    }
    return living;

  }

void grid::checkNode(node &nmain, node &check){
  node *ptr = &nmain;
  if(check.getAlive() == true){
    ptr->incSurr();
  //  cout << "survive" << endl;
  }
}

void grid::print(int i){
  ofstream outFS;
  outFS.open("GOL.txt", ios::app);
  outFS << i << endl;
  cout << endl;
  for(int i = 0; i < m_width; ++i){
    for(int j = 0; j < m_length; ++j){
      (field[i][j]).print();
      if(m_output == 2){
        outFS << field[i][j].toChar();
      }
    }
    cout << endl;
    if(m_output == 2){
      outFS << endl;
    }
  }
  outFS.close();
}

void grid::print(){
  ofstream outFS;
  outFS.open("GOL.txt", ios::app);
  cout << endl;
  for(int i = 0; i < m_width; ++i){
    for(int j = 0; j < m_length; ++j){
      (field[i][j]).print();
      if(m_output == 2){
        outFS << field[i][j].toChar();
      }
    }
    cout << endl;
    if(m_output == 2){
      outFS << endl;
    }
  }
  outFS.close();
}


void grid::round(int i){
  int nothing;
  cout << endl;
  if(m_output == 1){
    cin.get();
  }
  else if(m_output == 0){
    chrono::seconds dura( 1);
    this_thread::sleep_for( dura );
    }
  cout << i << endl;
  setChanges(0);
//  cout << "Changed: " << getChanges() << endl;
//  cout << "testing assessNeighbors" << endl;
  assessNeighbors();
//  cout << "Changed: " << getChanges() << endl;
// cout << "works" << endl;
//  cout << "testing assessLife" << endl;
  nodesAlive = assessLife();
//  cout << "Changed: " << getChanges() << endl;
//  cout << "works" << endl;
//  cout << "testing print" << endl;
  print(i);
//  cout << "works" << endl;
//  cout << "Nodes Left: " << nodesAlive << endl;
}

int grid::getNodesAlive(){
  return nodesAlive;
}

bool grid::getChanges(){
  return changes;
}

void grid::setChanges(bool newChange){
  changes = newChange;
}

void grid::run(){
  int loop;
  if(m_length * m_width > 60){
    loop = m_length * m_width;
    loop /= 2;
  }
  else{
    loop = 60;
  }
  cout << "loop = " << loop << endl;
  for(int i = 0; i < loop; ++i){
    round(i);
    if(getNodesAlive() == 0){
      break;
    }
    else if(getChanges() == false){
      break;
    }
  }
}
/*int main(){
  grid *tester = new grid(20, 20, 0.1, 1);
  tester->print();
  int i = 0;
  while(i < 80){
    cout << i << endl;
    tester->round();
    i++;
    cout << "Changed: " << tester->getChanges() << endl;
    if(tester->getNodesAlive() == 0){
      break;
    }
    else if(tester->getChanges() == false){
      break;
    }
  }
  delete tester;
}*/
