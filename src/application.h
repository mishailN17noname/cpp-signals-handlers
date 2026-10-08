#ifndef __APPLICATION__H
#define __APPLICATION__H
#include "cl_base.h"

class application: public cl_base{
public:
   application(cl_base* parent);
   void build_tree_objects();
   int exec_app();
   int get_class_num();
   void signal(string & message);
   void handler(string & message);
};
#endif
