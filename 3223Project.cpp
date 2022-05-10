#include <iostream>
using namespace std;

class Node
{
  private:
    int val;
    Node* next;
    Node* prev;

  public:
    Node();
    Node(int);
    ~Node();
    bool set_val(int);
    bool set_next(Node*);
    bool set_prev(Node*);
    int get_val();
    Node* get_next();
    Node* get_prev();
    void display();
};

Node::Node()
{
  val=0;
  next=NULL;
  prev=NULL;
}

Node::Node(int v)
{
  val=v;
  next=NULL;
  prev=NULL;
}

Node::~Node()
{
}

bool Node::set_val(int v)
{
  val=v;
  return true;
}

int Node::get_val()
{
  return val;
}

bool Node::set_next(Node* n)
{
  next=n;
  return true;
}

Node* Node::get_next()
{
  return next;
}

bool Node::set_prev(Node* p)
{
  prev=p;
  return true;
}

Node* Node::get_prev()
{
  return prev;
}

void Node::display()
{
  cout << val;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynList
{
  private:
    Node* start;
    
    // Node* get_index(int);

  public:
    // Node array[10][10];
    int lower = -1;
    int higher= -1;
    DynList();
    // ~DynList();
    bool add_element(int, DynList*, int);
    bool remove_range(DynList*, int);
    void display(int);
    bool add_range(int, int, DynList*, int, int*);
    bool merge_range(DynList*, int, int);
    bool remove_element(int);
    bool insert_before(int, int);
    bool remove_duplicates(DynList*, int*);
    void operator=(DynList);
    bool operator==(DynList);
};
DynList::DynList()
{
  start=NULL;

}


bool DynList::add_element(int v, DynList* d, int index)
{
  // cout << "Adding " << v << " to array index " << index << endl;
  if(v >= d[index].lower && v <= d[index].higher){
    Node* temp=new Node(v);
    if (start==NULL){
      start = temp; 
      return true;
    }
    else
    {
      temp->set_next(start);
      start->set_prev(temp);
      start=temp;
      return true;
    }
  }
  cout << "Value: " << v << " not in range for array index: " << index << endl << endl;
  return true;
}
void DynList::display(int index)
{
  Node* curr=start;
  cout << "index "<< index << ": [" << lower << ", " << higher << "]     ";
  while(curr!=NULL)
  {

    curr->display();
    cout << " ";
    curr=curr->get_next();
  }
  cout << endl;
}
bool DynList::add_range(int lower1, int higher1, DynList* d, int index, int* csz)
{
  cout << "Adding range [" << lower1 << ", " << higher1 << "] to arrayIndex " << index << endl; 
  for(int i = 0; i < *csz; i++){
    // cout << lower1 << " " << d[i].lower << endl;
    if(!((lower1 >= d[i].lower && lower1 <= d[i].higher) || (higher1 >= d[i].lower && higher1 <= d[i].higher))){ //if range not being use elsewhere
    // else if(v >= d[i].lower && d[i] << d[i].higher)
      // cout << "0" << endl;
      if(i != *csz - 1)//if not done checking all indexes in array continue
        continue;
      // cout << "1" << endl;
      lower = lower1;
      higher = higher1;
      return true;
    }
    else break;
  }
  cout << "Error: Range in use" << endl;   
  return false; 
}
bool DynList::remove_range(DynList* d, int index)
{ 
  cout << "Removing range from index: " << index << " and clearing elements"<< endl;
  d[index].lower = -1; //-1 is default lower value
  d[index].higher = -1;
  d[index].start = NULL;
  return true;
}
bool DynList::merge_range(DynList* d, int mergeTo, int merge){
  // int lowerTemp = d[merge].lower;
  // int higherTemp = d[merge].higher;
  cout << "Merging : " << merge << " to "<< mergeTo << endl;
  if(d[mergeTo].lower > d[merge].lower){
    d[mergeTo].lower = d[merge].lower;
  }
  if(d[mergeTo].higher < d[merge].higher){
    d[mergeTo].higher = d[merge].higher;
  }
  Node* curr1= d[merge].start;//point to start of merge, start is of type node, stores val and list
  while(curr1!=NULL)
  {

    // curr->display();
    // cout << " ";
    add_element(curr1->get_val(), d, mergeTo); //curr1 pointing to start of merge, grab value at start and then traverse rest of merge list
    curr1=curr1->get_next();
  }
  remove_range(d, merge);
  return true; 

}
bool DynList::remove_element(int v){
  if (start->get_val() == v)
  {
    Node *temp = start;
    start = start->get_next();
    delete temp;
    return true;
  }

  Node *curr = start;
  while((curr->get_next() != nullptr) && ((curr->get_next())->get_val() != v))
    curr = curr->get_next();

  Node *curr1 = curr->get_next();
  Node *curr2 = curr1->get_next();
  curr->set_next(curr2);
  delete curr1;
  return true;
}
bool DynList::insert_before(int v, int n)
{
  Node *temp = new Node(v);
  if (start->get_val() == n)
  {
    temp->set_next(start);
    start = temp;
    return true;
  }
  Node *curr = start;
  while((curr->get_next() != nullptr) && ((curr->get_next())->get_val() != n))
    curr = curr->get_next();

  Node *curr1 = curr->get_next();
  temp->set_next(curr1);
  curr->set_next(temp);
  return true;
}
bool DynList::remove_duplicates(DynList* d, int* csz){
  
  
  for(int i = 0; i < *csz; ++i){

    Node* curr = d[i].start;
    Node* currV = d[i].start;
    int v = currV->get_val(); //start of index array i has to have a non NULL value or will crash       
    // cout << "ssss" << endl;
    while(currV->get_next() != nullptr){//lets v = all elemets in list
      while(curr->get_next() != nullptr){ //checks v to all elements 
        // cout << curr->get_val() << endl;
        if((curr->get_next())->get_val() == v){
          cout << "removing :" << (curr->get_next())->get_val() << endl;
          Node *curr1 = curr->get_next();
          Node *curr2 = curr1->get_next();
          curr->set_next(curr2);
          delete curr1;
        }
        else{
          curr = curr->get_next();
          
          
          // continue;
          // cout << " iiiii" << endl;
        }
      }
      currV = currV->get_next();
      curr = currV->get_next();
      v = currV->get_val();
    }
  }
  return true;
}
void DynList::operator=(DynList d){
  Node* curr=d.start;

  Node* temp=new Node(curr->get_val());
  cout << "www" << endl;
  start = NULL;
  lower = d.lower;
  higher = d.higher;
  while( curr != NULL)
  {
    cout << curr->get_val() << endl;
    if (start==NULL){
      start = temp; 
      // return true;
    }
    else
    {
      temp->set_next(start);
      start->set_prev(temp);
      start=temp;
      // return true;
    }
    if(curr->get_next() != NULL){
      curr = curr->get_next();
      temp = new Node(curr->get_val());
    }
    else break;
  } 
}
bool DynList::operator==(DynList d){
  // higher = -1;
  if((d.lower != lower) || (d.higher != higher))
    return false;

  Node* curr = d.start;
  Node* currV = d.start;
  int v = currV->get_val(); //start of index array i has to have a non NULL value or will crash       
  // cout << "ssss" << endl;
  while(currV->get_next() != nullptr){//lets v = all elemets in list
    while(curr->get_next() != nullptr){ //checks v to all elements 
      // cout << curr->get_val() << endl;
      if(!(curr->get_next())->get_val() == v){
        return false;
      }
      else{
        curr = curr->get_next();
        
        
        // continue;
        // cout << " iiiii" << endl;
      }
    }
    currV = currV->get_next();
    curr = currV->get_next();
    v = currV->get_val();
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynList* addToIndex(DynList* d, int* csz,int* cap){
    
    const int inc = 1;
    
    if(*csz == *cap){
      cout << "moving to a bigger array..." << endl;
      // d = move(d, csz,inc);
      DynList *p = new DynList[*csz + inc];

      for(int i = 0; i < *csz; ++i)
        p[i] = d[i];  
      delete[] d;
      *cap = *cap + inc;
      *csz = *csz + 1;
      cout << "done!" << endl;
      return p;
    }
    
    // delete[] a;
    return d;  
}
void displayDynList(DynList* d, int* csz){
  for(int j = 0; j < *csz; j++){
        d[j].display(j);
    }
}

int main()
{
    
    int cap = 3; //array capacity
    int csz = 3; //current size
    DynList *d = nullptr;
    // DynList d[cap];
    d = new DynList [cap];
    int* cszPtr = &csz; //pointer to current size memory address to update it when sending through function
    int* capPtr = &cap;

  

    
    cout << *cszPtr << endl;
    
    // display function should display both array element (=range) and list (=elements).
    displayDynList(d, cszPtr);


    // Please use "add_range" function to add a new range
   
    ///////////////L  H  d  index   csz 
    d[1].add_range(6, 9, d, 1,     cszPtr);
    // cout << d[1].lower << endl;
    // cout << d[1].higher << endl;
    // cout<< "w" << endl;
    
    d[2].add_range(9, 20, d, 2, cszPtr);
    d[2].add_range(10, 20, d, 2, cszPtr);
    
    // cout << d[2].lower << endl;
    // cout << d[2].higher << endl;
    
    displayDynList(d, cszPtr); 
    // d[1].add(6, d, 1);

    // please use "add_element" function to add an element in the list
    // Element should be added in the list referenced by ArrayIndex
    d[1].add_element(5, d, 1);
    d[1].add_element(10, d, 1);
    d[1].add_element(6, d, 1);
    d[1].add_element(9, d, 1);
    d[1].add_element(8, d, 1);
    d[2].add_element(15, d, 2);
    d[2].add_element(13, d, 2);
    d[2].add_element(11, d, 2);
    d[2].add_element(17, d, 2);
    displayDynList(d, cszPtr);

    // Please use "remove_range" function to remove a range
    // fuction arguments are depending on your code
    // d.remove_range();
    d[1].remove_range(d, 1);
    displayDynList(d, cszPtr);
    d[1].add_range(6, 9, d, 1, cszPtr);
    d[1].add_element(5, d, 1);
    d[1].add_element(10, d, 1);
    d[1].add_element(6, d, 1);
    d[1].add_element(9, d, 1);
    d[1].add_element(8, d, 1);
    displayDynList(d, cszPtr);
    // Please use "merge_range" function to merge ranges
    // fuction arguments are depending on your code 
    // d.merge_range();
    d[1].merge_range(d, 1, 2);
    displayDynList(d, cszPtr);

    // Please use "remove_element" function to remove only one occurence of the element
    // d.remove_element(int x);
    d[1].remove_element(15);
    displayDynList(d, cszPtr);

    // Please use "insert(x,y)" function to insert x element before y
    // Please follow the order of function argument to make sure insert x before y
    // d.insert(int x, int y);
    d[1].insert_before(6, 13);
    displayDynList(d, cszPtr);
    // Please use "remove_duplicates" function to remove all duplicates throughout the all lists
    // d.remove_duplicates();
    d[0].add_range(90, 99, d, 0, cszPtr);
    d[0].add_element(90, d, 0);
    d[0].add_element(90, d, 0);
    d[0].add_element(99, d, 0);
    d[0].add_element(98, d, 0);
    d[0].add_element(90, d, 0);
    d[0].add_element(91, d, 0);
    d[2].add_range(21, 28, d, 2, cszPtr);
    d[2].add_element(21, d, 2);
    d[2].add_element(25, d, 2);
    d[2].add_element(21, d, 2);
    d[2].add_element(28, d, 2);
    displayDynList(d, cszPtr);
    d[1].remove_duplicates(d, cszPtr);
    displayDynList(d, cszPtr);


    d[2] = d[0];

    displayDynList(d, cszPtr);
    cout << "Comparing d[2] and d[0]" << endl;
    if(d[2] == d[0])
        cout << "equal" << endl;
    else 
      cout << "not equal" << endl;

    // displayDynList(d, cszPtr);

}
