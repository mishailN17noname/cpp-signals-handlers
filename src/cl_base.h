#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)
using namespace std;
class cl_base;
typedef void(cl_base::*TYPE_SIGNAL)(string &);
typedef void(cl_base::*TYPE_HANDLER)(string);


class cl_base{
   struct connect {
      TYPE_SIGNAL signal_ptr;
      cl_base* tar_ptr;
      TYPE_HANDLER handler_ptr;
   };
private:
   int state = 0;
   cl_base* parent;
   vector <cl_base*> children;
   string name;
   vector <connect*> connects;
public:
   cl_base(cl_base* parent, string name = "Object_root");
   ~cl_base();
   bool set_name(string name);
   string get_name();
   cl_base* get_parent();
   cl_base* get_child_by_name(string name);
   cl_base* find_object_on_branch(string name);
   cl_base* find_object_on_tree(string name);
   void print_branch(int level = 0);
   void print_branch_with_state(int level = 0);
   void set_state(int state);
   bool set_parent(cl_base* new_par);
   void remove_child_by_name(string child_name);
   cl_base* get_by_path(string path);
   void set_connection(TYPE_SIGNAL signal_ptr, cl_base* tar_ptr, TYPE_HANDLER handler_ptr);
   void remove_connection(TYPE_SIGNAL signal_ptr, cl_base* tar_ptr, TYPE_HANDLER handler_ptr);
   void emit_signal(TYPE_SIGNAL signal_ptr, string & command);
   string get_abs_path();
   virtual int get_class_num();
   void set_state_branch(int new_status);
};

#endif
