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
   Node_2D::info_class(); // 0 ticket, 2 dof
   cout << "Create five node instances" << endl;
   Node * my_class;
   Node_2D Nodes[5];

   my_class = Nodes;
   cout << "Base Class id " <<  my_class->get_id() << endl;
   my_class = (Nodes+1);
   cout << "Base Class id " <<  my_class->get_id() << endl;
   my_class = (Nodes+2);
   cout << "Base Class id " <<  my_class->get_id() << endl;
   my_class = (Nodes+3);
   cout << "Base Class id " <<  my_class->get_id() << endl;
   my_class = (Nodes+4);
   cout << "Base Class id " <<  my_class->get_id() << endl;

   {
     cout << endl << "nest" << endl;
     Node_2D test = *(Node_2D*)(my_class);
     Node_2D::info_class();
     test.info();
     if(test == *(Node_2D*)(my_class)){
       cout << "Test object is same with my_class" << endl;
       ((Node_2D*)my_class)->info();
     } else{
       cout << "Test object is not same with my_class" << endl;
     }

     my_class = (Nodes+3);
     if(test == *(Node_2D*)(my_class)){
       cout << "Test object is same with my_class" << endl;
       ((Node_2D*)my_class)->info();
     } else{
       cout << "Test object is not same with my_class" << endl;
       ((Node_2D*)my_class)->info();
     }
     cout << "nest-end" << endl;
   }

   cout << endl << "Print information of first instance" << endl;
   Nodes[0].info(); // 1 node [ 0, 0];
   Nodes[1].info(); // 2 node [ 0, 0];
   Nodes->info_class();

   cout << endl << "Make test" << endl;
   Node_2D test(pos);     // second constructor
   Node_2D::info_class(); // 6 ticket
   test.info();        // 6 node [10, 20];

   cout << endl << "Copy test 1" << endl;
   Nodes[0] = test; // 1 node is replaced by test;
   Node_2D::info_class(); // 6 ticket
   Nodes[0].info(); // 6 node [10,20]

  cout << endl << "Copy test2" << endl;
  Node_2D test1 = test;   // Copy constructor
  Node_2D::info_class(); // 7 ticket
  test1.info();       // 6 node [10, 20]

  cout << endl << "Print Information Table in \"./data.dat\"" << endl;
  for(int i=0; i < 5;++i){
    my_class = (Nodes+i);
    fout << " Pointer " << endl;
    ((Node_2D*)my_class)->info(fout); // check ./data.dat
    fout << " Array " << endl;
    Nodes[i].info(fout);
  }


  cout << endl << "Print Information Table in screen" << endl;
  for(int i=0; i < 5;++i)
    Nodes[i].info(cout); // compare the result with the one in ./data.dat

  cout << endl << "set_pos Test" << endl;
  Nodes[2].set_pos(x,100);
  Nodes[2].set_pos(y,200);
  Nodes[2].info();
  my_class = (Nodes+2);
  ((Node_2D*)(my_class))->info();
  ((Node_2D*)(my_class))->info(fout);


  //Nodes[2].set_pos(z,200); // if this line is un-commented, error will occur. Analysis
                              // dimension is set to two, currently.

  cout << endl << "get function tests " << endl;
  for(int i=0;i<5;i++){
    cout << "Class " << Nodes[i].get_name() << " ID " << Nodes[i].get_id()
         << " node's ticket number is " << Nodes[i].get_ticket() << " and its coordinates : " << endl;
    for(int j=0; j < Nodes[i].get_dof(); j++)
      cout << Nodes[i].get_pos(j) << " ";
    cout << endl;
  }

   fout.close();

  return 0;
}
