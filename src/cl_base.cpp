#include "cl_base.h"
#include <stack>

cl_base::cl_base(cl_base* parent, string name): parent(parent), name(name) {
   if (parent != nullptr){
   parent-> children.push_back(this);
   }
}
cl_base::~cl_base(){
   for (int i = 0; i < children.size(); i++) delete children[i];
}
string cl_base:: get_name(){
   return name;
}
cl_base* cl_base::get_parent(){
   return parent;
}

bool cl_base:: set_name(string name1){
   if (get_parent() != nullptr && get_parent() -> get_child_by_name(name1) != nullptr)
   {
      return false;
   }
   name = name1;
   return true;
}
cl_base* cl_base::get_child_by_name(string name)
{
   for (auto child: children)
   {
      if (child->name == name) return child;
   }
   return nullptr;
}

cl_base* cl_base::find_object_on_branch(string s_object_name)
{
   cl_base* found = nullptr;
   queue <cl_base*> elements_q;
   elements_q.push(this);
   while(!elements_q.empty()){
      cl_base* element = elements_q.front();
      elements_q.pop();
      if (element->name== s_object_name){
         if (found != nullptr){
            return nullptr;
         }
         else {
            found = element;
         }
      }
      for (int i = 0; i< element->children.size(); i++){
         elements_q.push(element->children[i]);
      }
   }
   return found;
}

cl_base* cl_base::find_object_on_tree(string s_object_name){
   if (parent != nullptr){
      return parent->find_object_on_tree(s_object_name);
   }
   else {
      return find_object_on_branch(s_object_name);
   }
}
void cl_base:: print_branch(int level){
   cout << endl;
   for (int i = 0; i<level;i++){
      cout << "    ";
   }
   cout << this->get_name();
   for (int i = 0; i < children.size(); i++){
      children[i]-> print_branch(level + 1);
   }
}

void cl_base:: print_branch_with_state(int level){
   cout << endl;
   for (int i = 0; i < level; i++){
      cout << "    ";
   }
   if (this->state !=0){
      cout << this -> get_name() << " is ready";
   }
   else {
      cout << this -> get_name()<< " is not ready";
   }
   for (int i = 0; i<children.size(); i++){
      children[i]-> print_branch_with_state(level + 1);
   }
}

void cl_base::set_state(int state){
   if (parent == nullptr || parent->state !=0){
      this-> state=state;
   }
   if (state ==0){
      this->state = state;
      for (int i = 0; i<children.size(); i++){
         children[i]->set_state(state);
      }
   }
}

bool cl_base::set_parent(cl_base* new_par){
   if (this->get_parent() == new_par){
      return true;
   }
   if (this->get_parent() == nullptr || new_par == nullptr){
      return false;
   }
   if (new_par->get_child_by_name(this->get_name()) != nullptr){
      return false;
   }
   stack<cl_base*> s;
   s.push(this);
   while(!s.empty()){
      cl_base* cur_node = s.top();
      s.pop();
      if(cur_node == new_par){
         return false;
      }
      for (int i = 0; i < cur_node->children.size();i++){
         s.push(cur_node->children[i]);
      }
   }
   vector <cl_base*> &vec = this->get_parent()->children;
   for (int i = 0; i < vec.size();i++){
      if(vec[i] -> get_name() == this->get_name()){
         vec.erase(vec.begin()+i);
         new_par->children.push_back(this);
         return true;
      }
   }
   return false;
}

void cl_base::remove_child_by_name(string child_name){
   vector <cl_base*> &vec = this->children;
   for (int i = 0; i< vec.size(); i++){
      if (vec[i]->get_name() == child_name){
         delete vec[i];
         vec.erase(vec.begin() + i);
         return;
      }
   }
}
cl_base* cl_base::get_by_path(string path){
   if (path.empty()){
      return nullptr;
   }
   if (path == "."){
      return this;
   }
   if (path[0] == '.'){
      return find_object_on_branch(path.substr(1));
   }
   if (path.substr(0, 2) == "//"){
      return this->find_object_on_tree(path.substr(2));
   }
   if (path[0] != '/'){
      size_t slash = path.find('/');
      cl_base* child_ptr = this->get_child_by_name(path.substr(0, slash));
      if (child_ptr == nullptr || slash == string::npos){
         return child_ptr;
      }
      return child_ptr->get_by_path(path.substr(slash + 1));
   }
   cl_base* root = this;
   while(root->get_parent()!= nullptr){
      root = root->get_parent();
   }
   if (path =="/"){
      return root;
   }
   return root->get_by_path(path.substr(1));
}

void cl_base::set_connection(TYPE_SIGNAL signal_ptr, cl_base* tar_ptr, TYPE_HANDLER handler_ptr){
   for (int i = 0; i < connects.size(); i++){
      if (connects[i]->signal_ptr == signal_ptr && connects[i]->tar_ptr == tar_ptr && connects[i]->handler_ptr == handler_ptr){
         return;
      }
   }
   connect * new_connection = new connect();
   new_connection->signal_ptr = signal_ptr;
   new_connection->tar_ptr = tar_ptr;
   new_connection->handler_ptr = handler_ptr;
   connects.push_back(new_connection);
}
void cl_base::remove_connection(TYPE_SIGNAL signal_ptr, cl_base* tar_ptr, TYPE_HANDLER handler_ptr){
   for (int i = 0; i< connects.size(); i++){
      if (connects[i]->signal_ptr == signal_ptr && connects[i]->tar_ptr == tar_ptr && connects[i]->handler_ptr == handler_ptr){
         delete connects[i];
         connects.erase(connects.begin()+i);
         return;
      }
   }
}
void cl_base::emit_signal(TYPE_SIGNAL signal_ptr, string & command){
   if (this->state == 0){
      return;
   }
   (this->*signal_ptr)(command);
   for (int i = 0; i < connects.size();i++){
      if (connects[i]->signal_ptr == signal_ptr ){
         TYPE_HANDLER handler_ptr = connects[i]->handler_ptr;
         cl_base* tar_ptr = connects[i]->tar_ptr;
         if(tar_ptr->state != 0){
            (tar_ptr->*handler_ptr)(command);
         }
      }
   }
}

string cl_base::get_abs_path(){
   string res;
   stack<string> s;
   cl_base* root = this;
   while (root->get_parent() != nullptr){
      s.push(root->get_name());
      root = root->get_parent();
   }
   if (s.empty()){
      return "/";
   }
   while(!s.empty()){
      res += '/' + s.top();
      s.pop();
   }
   return res;
}


int cl_base::get_class_num(){
   return 0;
}

void cl_base::set_state_branch(int new_status){
   if (get_parent() != nullptr && get_parent()->state == 0){
      return;
   }
   set_state(new_status);
   for (int i = 0; i < children.size(); i++){
      children[i]->set_state_branch(new_status);
   }
}
