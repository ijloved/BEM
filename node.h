// KEEPER_BEM_NODE -- a class to handle the coordinate of node.
//
// Author: IkJung Yun

// Written from 2012.01.10.

#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

#ifndef BEM_NODE_H_
#define BEM_NODE_H_

namespace BEM_NODE{

  // This variable is declared here temporarily.
  // As more classes is implemented, it will be moved to more proper class.
  // Tentatively, I think a header file having the definition of constants will be required.
  typedef double DATA_TYPE;

  // degree of freedom
  typedef enum _DOF_TAG{one = 1, two = 2, three = 3} BEM_DOF;
  // coordinates
  typedef enum _LOC_TAG{x = 0, y = 1, z = 2} BEM_LOC;

  inline const char *  string_location(BEM_LOC loc) {
    static const char * const m_x = "x";
    static const char * const m_y = "y";
    static const char * const m_z = "z";
    switch(loc){
    case x :
      return m_x;
    case y :
      return m_y;
    case z :
      return m_z;
    default:
      cout << "Error: Analysis dimension should be less than 3 dimension, "
           << "current dimension is " << loc << endl;
      exit(8);
    }
    cout << "Internal failure is occured in string_location(BEM_LOC loc)" << endl;
    exit(8);
    return NULL; // never reached this points
  }


  class Node{
  private :

    static int m_ticket;      // number of created instance
    static const int n_dof = two;      // number of degree of freedom

    static string m_name ;


    int m_id;     // node id, not unique value but if two instances have same id number then
                  // the position of instances is also same. However converse does not satisfied.

    // m_pos contains the position data of nodes.
    // its dimension depends on the degree of freedom of analysis.
    DATA_TYPE m_pos[n_dof];

    //  protected :

    // these pointers to point linked elements
    // however, currently not used.
    // AML_LList m_in_links;
    // AML_LList m_out_links;


  public :
    // Default Constructor
    // 1- increase m_ticket by one
    // 2- set m_id equal to m_ticket
    // 3- initialize m_pos as zero.
    Node(void) : m_id(++m_ticket){
      for(int i=0; i<n_dof;++i)
        *(m_pos+i)= 0.0;
    }

    // Constructor 2
    // 3 --> Input coordinates data as a parameter
    // Warning : This constructor doesn't check the dimension of an inputted array.
    Node(const DATA_TYPE * const pos) : m_id(++m_ticket){
      for(int i=0;i<n_dof;++i){
        *(m_pos+i) = *(pos+i); // cout << " " << i << " th compo value : " << *(m_pos+i) << endl;
      }
    }

    // Copy Constructor
    Node(const Node & target) {
      ++m_ticket;
      *this = target; // use operator =
    }

    // Operator overloading for =
    virtual Node & operator = (const Node & target){
      m_id = target.m_id;
      for(int i=0;i<n_dof;++i )
        *(m_pos+i) = *(target.m_pos+i);
      return (*this);
    }

    // Operator overloading for ==
    virtual bool operator == (const Node & target){
      if(m_id != target.m_id)
        return false;
      for(int i=0;i<n_dof;++i )
        if(*(m_pos+i) != *(target.m_pos+i))
          return false;

      return (true);
    }


    // Destructor - nothing but declared as virtual for later use.a
    virtual ~Node(void){--m_ticket;}

    // get functions
    static const int get_ticket(void) {return m_ticket;} // return ticket number of node
    static const int get_dof(void) {return n_dof;} // return the number of DOF.
    static const string & get_name(void) {return m_name;} //return the name of class

    const int get_id(void) const {return m_id;} // return node id

    const DATA_TYPE get_pos(const int loc) const { return m_pos[loc];} // return the coordinate
                                                                       // of the node.
    // set functions
    void set_pos(const BEM_LOC loc, const DATA_TYPE val){
      if(loc>=n_dof){
        cout << "Error: " << string_location(loc) << " is not in the bound of analysis dimension" << endl;
        exit(8);
      }
      m_pos[loc] =val;
    } // change the coordinate of node

    static ostream & info_class(ostream & os = cout); // print total number of created node
                                                      // which is existing and analysis dimension

    ostream & info(ostream & os = cout);              // print node id and coordinate

    // // Links
    // AML_LList* Get_In_Links(void){ return &m_in_links;}
    // AML_LList* Get_Out_Links(void){ return &m_out_links;}

    // // Conencting Node
    // void Connect_to(void* by) { m_out_links.Add_After_Tail(by);}
    // void Connect_from(void * by) { m_in_links.Add_After_Tail(by);}

  };
}

#endif
