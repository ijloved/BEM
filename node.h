// KEEPER_BEM_NODE -- a class to handle the coordinate of node.
//
// Author: IkJung Yun

// Written from 2012.01.10.
// Last modified at 2012.01.13

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "common.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using namespace BEM_COMMON;

#ifndef BEM_NODE_H_
#define BEM_NODE_H_

namespace BEM_NODE{

  // String Constant
  static const string node_name_2D = "2D Node Class";

  /*
    ---------------------------------------------------------------------
    Node class -- Abstract structure
      To postpone the declaration of the array holding coordinates of nodes until proper class
      is established, such as Node_2D and Node_3D, this class is made to an abstract class.
    ---------------------------------------------------------------------
    Member
      static unsigned int m_ticket;
      unsigned int m_id;
    ---------------------------------------------------------------------
    Functions
      Node(void)
      Node(const Node & target)
      virtual Node & operator = (const Node & target)
      virtual bool operator == (const Node & target)
      virtual ~Node(void){--m_ticket;}
      static const int get_ticket(void) {return m_ticket;}
      const int get_id(void) const {return m_id;}
      virtual const DATA_TYPE get_pos(const int loc) const = 0;
      virtual void set_pos(const BEM_LOC loc, const DATA_TYPE val) = 0;
    ---------------------------------------------------------------------
  */
  class Node{
  private:
    // print node id and coordinate
    virtual ostream & info(ostream & os = cout){return os;}
  protected :
    // number of created instance
    static unsigned int m_ticket;
    // node id, not unique value but if two instances have same id number then the position of
    // instances is also same. However converse does not satisfied.
    unsigned int m_id;


  public :
    // Default Constructor -- increase m_ticket by one and  set m_id equal to m_ticket
    Node(void) : m_id(++m_ticket){;}
    // Copy Constructor
    Node(const Node & target) {
      ++m_ticket;
       m_id = target.m_id;
    }
    // Operator overloading for =
    virtual Node & operator = (const Node & target){
      m_id = target.m_id;
      return (*this);
    }
    // Operator overloading for ==
    virtual bool operator == (const Node & target) const {
      if(m_id == target.m_id)
        return (true);
      else return (false);
    }
    // Destructor - nothing but declared as virtual for later use.
    virtual ~Node(void){--m_ticket;}

    // get functions //
    static const int get_ticket(void) {return m_ticket;} // return ticket number of node
    const int get_id(void) const {return m_id;} // return node id
    virtual const DATA_TYPE get_pos(const int loc) const = 0;

    // set functions //
    virtual void set_pos(const BEM_LOC loc, const DATA_TYPE val) = 0;

  };                            // Class Node


  /*
    ---------------------------------------------------------------------
    Node_2D class -- is derived from Node class
      static const int n_dof = two_D;
      DATA_TYPE m_pos[n_dof];
      are declared.
    ---------------------------------------------------------------------
    Member
      (base) static unsigned int m_ticket;
      (base) unsigned int m_id;
      static const int n_dof = two_D;
      DATA_TYPE m_pos[n_dof];
    ---------------------------------------------------------------------
    Functions
    Node_2D(void)
    Node_2D(const DATA_TYPE * const pos)
    Node_2D(const Node_2D & target) : Node(target)
    virtual Node_2D & operator = (const Node_2D & target)
    virtual bool operator == (const Node_2D & target)
    virtual ~Node_2D(void)
    static const int get_dof(void)
    static const string & get_name(void)
    const DATA_TYPE get_pos(const int loc)
    void set_pos(const BEM_LOC loc, const DATA_TYPE val)
    ostream & info_class(ostream & os = cout)
    ostream & info(ostream & os = cout)
    ---------------------------------------------------------------------
  */
  class Node_2D : public Node{
  private :
    static const int n_dof = two_D; // number of degree of freedom
    DATA_TYPE m_pos[n_dof];         // 2D coordinates of point

  public :
    // Default Constructor - initialize m_pos as zero.
    Node_2D(void){
      for(int i=0; i<n_dof;++i)
        *(m_pos+i)= 0.0;
    }

    // Constructor 2 -- Input coordinates data as a parameter
    // Warning : This constructor doesn't check the dimension of an inputted array.
    Node_2D(const DATA_TYPE * const pos) {
      for(int i=0;i<n_dof;++i)
        *(m_pos+i) = *(pos+i);
    }

    // Copy Constructor
    Node_2D(const Node_2D & target) : Node(target){
      *this = target; // use operator =
    }

    // Operator overloading for =
    virtual Node_2D & operator = (const Node_2D & target){
      m_id = target.m_id;
      for(int i=0;i<n_dof;++i )
        *(m_pos+i) = *(target.m_pos+i);
      return (*this);
    }

    // Operator overloading for ==
    virtual bool operator == (const Node_2D & target) const{
      if(m_id != target.m_id)
        return false;
      for(int i=0;i<n_dof;++i )
        if(*(m_pos+i) != *(target.m_pos+i))
          return false;
      return (true);
    }

    // Destructor - nothing but declared as virtual for later use.
    virtual ~Node_2D(void){;}

    // get functions
    static const int get_dof(void) {return n_dof;} // return the number of DOF.
    static const string & get_name(void) {return node_name_2D;} //return the name of class
    const DATA_TYPE get_pos(const int loc) const { return m_pos[loc];} // return the coordinate
                                                                       // of the node.
    // set functions
    // change the coordinate of node
    void set_pos(const BEM_LOC loc, const DATA_TYPE val){
      if(loc>=n_dof){
        cout << "Error: " << string_location(loc) << " is not in the bound of analysis dimension" << endl;
        exit(8);
      }
      m_pos[loc] =val;
    }

    // print total number of created node which is existing and analysis dimension
    static ostream & info_class(ostream & os = cout);
    // print node id and coordinate
    virtual ostream & info(ostream & os = cout);
  };                            // Class Node_2D


} // namespace BEM_NODE

#endif
