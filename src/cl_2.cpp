#include "cl_2.h"

cl_2::cl_2(cl_base* p_head_object, string s_object_name):cl_base(p_head_object, s_object_name){}


int cl_2::get_class_num(){
   return 2;
}

void cl_2::signal(string & message){
   cout << '\n' << "Signal from "<< get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}
void cl_2::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() <<" Text: "<< message;
}
