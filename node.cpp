#include "node.h"

node::node(){
  m_alive = false;
  m_surr = 3;
}


node::node(bool alive, int surr){
  m_alive = alive;
  m_surr = surr;
}
node::~node(){

}

bool node::getAlive(){
  return m_alive;
}

void node::setAlive(bool newAlive){
  m_alive = newAlive;
}

bool node::checkAlive(){
//  cout << "Before alive: " << m_alive << endl;
//  cout << "Number of Neighbors: " << (m_surr) << endl;
  bool res = false;
  if(m_alive){
    if(m_surr <= 1){
      m_alive = false;
      res = false;
    }
    else if(m_surr <= 3 && m_surr > 1){
      res = true;
    }
    else{
      m_alive = false;
      res = false;
    }
  }
  else{
    if(m_surr == 3){
      m_alive = true;
      res = true;
    }
    else{
      res = false;
    }
  }
 //cout << "After alive: " << res << endl << endl;
  return res;
}

int node::getSurr(){
  return m_surr;
}
void node::setSurr(int newSurr){
  if(newSurr <= 9 && newSurr >= 0)
    m_surr = newSurr;
}
void node::incSurr(){
  if(m_surr < 9)
    m_surr++;
}
void node::decSurr(){
  if(m_surr > 0)
    m_surr--;
}

void node::print(){
  cout << toChar();
}

char node::toChar(){
  if(m_alive == true){
    return 'x';
  }
  else{
    return '-';
}
}

/*int main(){
  node *node1 = new node(false, 0);
  node1->checkAlive();

  node node2 = new node(true, 5);
  node node3 = new node(false, 2);
  node node4 = new node(false, 3);

  node2.checkAlive();
  node3.checkAlive();
  node4.checkAlive();
delete node1;
}*/
