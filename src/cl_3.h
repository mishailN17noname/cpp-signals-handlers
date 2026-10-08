#ifndef __CL_3__H
#define __CL_3__H
#include "cl_base.h"

class cl_3: public cl_base
{
public:
   cl_3(cl_base* p_head_object, string s_object_name);
   int get_class_num();
   void signal(string & message);
   void handler(string & message);
};

#endif
