#include "cl_5.h"

cl_5::cl_5(cl_base* p_head_object, string s_object_name):cl_base(p_head_object, s_object_name){}


int cl_5::get_class_num(){
   return 5;
}

void cl_5::signal(string & message){
   cout << '\n' << "Signal from "<< get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}
void cl_5::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() <<" Text: "<< message;
}
