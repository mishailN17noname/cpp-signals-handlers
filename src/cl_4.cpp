#include "cl_4.h"

cl_4::cl_4(cl_base* p_head_object, string s_object_name):cl_base(p_head_object, s_object_name){}


int cl_4::get_class_num(){
   return 4;
}

void cl_4::signal(string & message){
   cout << '\n' << "Signal from "<< get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}
void cl_4::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() <<" Text: "<< message;
}
