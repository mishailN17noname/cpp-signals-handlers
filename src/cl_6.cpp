#include "cl_6.h"

cl_6::cl_6(cl_base* p_head_object, string s_object_name):cl_base(p_head_object, s_object_name){}


int cl_6::get_class_num(){
   return 6;
}

void cl_6::signal(string & message){
   cout << '\n' << "Signal from "<< get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}
void cl_6::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() <<" Text: "<< message;
}
