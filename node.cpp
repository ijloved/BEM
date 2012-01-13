#include "node.h"
#include <iomanip>

using namespace BEM_NODE;
using std::setw;

// Total number of node class' instance,  this is defined as static
unsigned int Node::m_ticket = 0;

// Print total number of created node which is existing and analysis dimension.
ostream & Node_2D::info_class(ostream & os){
  os << node_name_2D << " class has " // Print Node name
     << "total " << m_ticket    // Print total number of Node
     << " node that lies in " << n_dof <<" dimension." << endl; // Print analysis dimension
  return os;
}

// Print a id number and coordinates of a specific node instance
// Using formatted data such as %d node position [ %4f, %4f, %4f ].
ostream & Node_2D::info(ostream & os){
  os << " " << m_id << " node position [ ";
  os << setw(4);
  for(int i = 0; i < n_dof-1; ++i){
    os << *(m_pos + i) << " , " ;
  }
  os << *(m_pos+n_dof-1) << " ]." << endl;
  return os;
}

