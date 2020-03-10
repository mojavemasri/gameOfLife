#include "grid.cpp"

int main(){
  string fname = "empty";
  unsigned int config = 2;
  unsigned int mode = 3;
  unsigned int output = 3;
  grid *init;
  cout << "Welcome to Game of Life! " << endl;;
  while(config > 1){
  cout << "What type of configuration would you like? Enter 0 for a random configuration, or 1 for a preset file: ";
  cin >> config;
  }
  if(config == 1){
    cout << endl << "Enter the filename: ";
    cin >> fname;
  }
  while(mode > 2){
    cout << endl << "What type of mode would you like? Enter 0 for normal mode, 1 for mirror mode, and 2 for doughnut mode: ";
    cin >> mode;
  }

  while(output > 2){
    cout << endl << "What type of output would you like? Enter:\n0 if you want a brief pause between generations \n1 if you want to have to press the \"enter\"";
    cout << " key \n2 if you want to output to a file.";
    cin >> output;
  }

  if(config == 1){
    init = new grid(fname, mode, output);
  }
  else{
    init = new grid(20, 20, 0.4, mode, output);
  }
  init->run();
  delete init;
}
