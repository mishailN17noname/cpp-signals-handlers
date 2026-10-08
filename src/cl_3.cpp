#include "cl_3.h"

cl_3::cl_3(cl_base* p_head_object, string s_object_name):cl_base(p_head_object, s_object_name){}


int cl_3::get_class_num(){
   return 3;
}

void cl_3::signal(string & message){
   cout << '\n' << "Signal from "<< get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}
void cl_3::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() <<" Text: "<< message;
}
