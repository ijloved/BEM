#include "node.h"
#include <iomanip>

using namespace BEM_NODE;
using std::setw;

unsigned int Node::m_ticket = 0; // Total number of node class' instance,  this is defined as static

string Node::m_name = "NODE"; // Name of class,  this is defined as static

// Print total number of created node which is existing and analysis dimension.
ostream & Node::info_class(ostream & os){
  os << m_name << " class has " // Print Node name
     << "total " << m_ticket    // Print total number of Node
     << " node that lies in " << n_dof <<" dimension." << endl; // Print analysis dimension
  return os;
}

// Print a id number and coordinates of a specific node instance
// Using formatted data such as %d node position [ %4f, %4f, %4f ].
ostream & Node::info(ostream & os){
  os << " " << m_id << " node position [ ";
  os << setw(4);
  for(int i = 0; i < n_dof-1; ++i){
    os << *(m_pos + i) << " , " ;
  }
  os << *(m_pos+n_dof-1) << " ]." << endl;
  return os;
}

