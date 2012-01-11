#include <iostream>
#include "node.h"
#include <fstream>

using namespace std;

using namespace BEM_NODE;

int main(void){

  cout << "This program is written to test the class BEM_NODE." << endl
       << "Main purpose of BEM is contain the coordinate of node." << endl << endl;

  fstream fout;
  fout.open("./data.dat");

  DATA_TYPE pos[3] ={10., 20., 30.};

  cout << "Start" << endl;
  Node::info_class(); // 0 ticket, 2 dof
  cout << "Create five node instances" << endl;
  Node my_class[5];
  Node::info_class(); // 5 ticket, 2 dof

  cout << endl << "Print information of first instance" << endl;
  my_class[0].info(); // 1 node [ 0, 0];
  my_class[1].info(); // 2 node [ 0, 0];

  cout << endl << "Make test" << endl;
  Node test(pos);     // second constructor
  Node::info_class(); // 6 ticket
  test.info();        // 6 node [10, 20];

  cout << endl << "Copy test 1" << endl;
  my_class[0] = test; // 1 node is replaced by test;
  Node::info_class(); // 6 ticket
  my_class[0].info(); // 6 node [10,20]

  cout << endl << "Copy test2" << endl;
  Node test1(test);   // Copy constructor
  Node::info_class(); // 7 ticket
  test1.info();       // 6 node [10, 20]

  cout << endl << "Print Information Table in \"./data.dat\"" << endl;
  for(int i=0; i < 5;++i)
    my_class[i].info(fout); // check ./data.dat

  cout << endl << "Print Information Table in screen" << endl;
  for(int i=0; i < 5;++i)
    my_class[i].info(cout); // compare the result with the one in ./data.dat

  cout << endl << "Ticket Test" << endl;
  {
    Node temp;
    Node::info_class(); // increase ticket to 8
  }
  Node::info_class(); // decrease ticket to 7 because local variable was gone.

  cout << endl << "set_pos Test" << endl;
  my_class[2].set_pos(x,100);
  //my_class[2].info(fout);
  my_class[2].info();
  my_class[2].set_pos(y,200);
  //my_class[2].info(fout);
  my_class[2].info();
  //my_class[2].set_pos(z,200); // if this line is un-commented, error will occur. Analysis
                              // dimension is set to two, currently.
  //my_class[2].info(fout);
  //my_class[2].info();

  cout << endl << "get function tests " << endl;
  for(int i=0;i<5;i++){
    cout << "Class " << my_class[i].get_name() << " ID " << my_class[i].get_id()
         << " node's ticket number is " << my_class[i].get_ticket() << " and its coordinates : " << endl;
    for(int j=0; j < my_class[i].get_dof(); j++)
      cout << my_class[i].get_pos(j) << " ";
    cout << endl;
  }


  return 0;
}
