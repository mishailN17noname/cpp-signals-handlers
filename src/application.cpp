#include "application.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <stack>

TYPE_SIGNAL class_num_to_signal(int class_num){
   switch(class_num){
      case 1:
         return SIGNAL_D(application::signal);
      case 2:
         return SIGNAL_D(cl_2::signal);
      case 3:
         return SIGNAL_D(cl_3::signal);
      case 4:
         return SIGNAL_D(cl_4::signal);
      case 5:
         return SIGNAL_D(cl_5::signal);
      case 6:
         return SIGNAL_D(cl_6::signal);
   }
   return nullptr;
}

TYPE_HANDLER class_num_to_handler(int class_num){
   switch(class_num){
      case 1:
         return HANDLER_D(application::handler);
      case 2:
         return HANDLER_D(cl_2::handler);
      case 3:
         return HANDLER_D(cl_3::handler);
      case 4:
         return HANDLER_D(cl_4::handler);
      case 5:
         return HANDLER_D(cl_5::handler);
      case 6:
         return HANDLER_D(cl_6::handler);
   }
   return nullptr;
}

application::application(cl_base* parent): cl_base(parent){}


int application:: exec_app() {
   TYPE_SIGNAL signal_f;
   TYPE_HANDLER handler_f;
   this->set_state_branch(1);
   string command, input, message;
   int new_status;
   cl_base* tar_obj_ptr;
   cl_base* ex_obj_ptr;
   this->print_branch();
   cin >> command;
   while (command != "END"){
      cin >> input;
      ex_obj_ptr = this->get_by_path(input);
      if (ex_obj_ptr == nullptr){
         cout << '\n' << "Object " << input << " not found";
         cin >> input;
      }
      if (command == "EMIT"){
         getline(cin, message);
         int number = ex_obj_ptr->get_class_num();
         ex_obj_ptr->emit_signal(class_num_to_signal(number), message);
      }
      else if (command == "SET_CONNECT"){
         cin >> input;
         tar_obj_ptr = this ->get_by_path(input);
         if (tar_obj_ptr == nullptr){
            cout << '\n' << "Handeler object " << input << " not found";
            continue;
         }
         signal_f = class_num_to_signal(ex_obj_ptr->get_class_num());
         handler_f = class_num_to_handler(tar_obj_ptr->get_class_num());
         ex_obj_ptr->set_connection(signal_f, tar_obj_ptr, handler_f);
      }
      else if (command == "DELETE_CONNECT"){
         cin >> input;
         tar_obj_ptr = this->get_by_path(input);
         if (tar_obj_ptr == nullptr){
            cout << '\n' << "Handler object " << input << " not found";
            continue;
         }
         signal_f = class_num_to_signal(ex_obj_ptr->get_class_num());
         handler_f = class_num_to_handler(tar_obj_ptr->get_class_num());
         ex_obj_ptr->remove_connection(signal_f, tar_obj_ptr, handler_f);
      }
      else if (command == "SET_CONDITION"){
         cin >> new_status;
         ex_obj_ptr->set_state(new_status);
      }
      cin >> command;
   }
   return(0);
}

int application::get_class_num(){
   return 1;
}

void application::signal(string & message){
   cout << '\n' << "Signal from " << get_abs_path();
   message += " (class: " + to_string(get_class_num()) + ")";
}

void application::handler(string & message){
   cout << '\n' << "Signal to " << get_abs_path() << " Text: "<< message;
}
void application:: build_tree_objects(){
   cout << "Object tree";
   string path, child_name;
   int t;
   cin >> child_name;
   this->set_name(child_name);
   cl_base* parent_node;
   cl_base* last_created_node = this;
   cin >> path;
   while(path != "endtree"){
      cin >> child_name >> t;
      parent_node = last_created_node->get_by_path(path);
      if (parent_node == nullptr){
         this->print_branch();
         cout << '\n' << "The head object " << path << " is not found";
         exit(1);
      }
      if (parent_node->get_child_by_name(child_name)!=nullptr){
         cout << '\n' << path << " Dubbing the names of subordinate objects";
      }
      else {
         if (t==1){
            last_created_node = new application(parent_node);}
         else if (t==2){
            last_created_node = new cl_2(parent_node, child_name);
         }
         else if (t==3){
            last_created_node = new cl_3(parent_node, child_name);
         }
         else if (t==4){
            last_created_node = new cl_4(parent_node, child_name);
         }
         else if (t==5){
            last_created_node = new cl_5(parent_node, child_name);
         }
         else if (t==6){
            last_created_node = new cl_6(parent_node, child_name);
         }
         else {}

      }
      cin >> path;
   }
   cl_base* tar_ptr;
   string tar_path;
   cin >> path;
   while (path != "end_of_connections"){
      cin >> tar_path;
      parent_node = get_by_path(path);
      tar_ptr = get_by_path(tar_path);
      TYPE_SIGNAL signal_f = class_num_to_signal(parent_node->get_class_num());
      TYPE_HANDLER handler_f = class_num_to_handler(tar_ptr->get_class_num());
      parent_node->set_connection(signal_f, tar_ptr, handler_f);
      cin >> path;
   }
}
