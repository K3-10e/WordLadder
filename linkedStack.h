/*Description: file implements a stack throught the linkedStack class*/

/*Algorithm:
1. Make the constructor by initializing the points
2. Make the destructor by calling the delete stack function
3. call copyStack from the copy constructor
4. Create isStackEmpty by checking if the stackTop is nullptr
5. Create push by creating a new node as the head of the list
6. Make pop by returning/deleting the value on the top of the stack
7. Use peek to get the value at the top of the stack
8. return the count with stack count
9. call rSum with countSum and recursively find the sum of the list
10. Make the == and != operators by comparing all the values of the list
11. make a deep copy of the stack with copyStack
12. delete the whole stack with deleteStack*/

#include <iostream>

using namespace std;

template <class myType>
struct nodeType{
    myType info;
    nodeType<myType> *link;
};

template <class myType>
class linkedStack{
    private: 
        nodeType<myType> *stackTop;
        int count;
        myType rSum(nodeType<myType> *) const;
        void copyStack(const linkedStack<myType> &);
    
    public:
        bool operator == (const linkedStack <myType>&);
        bool operator != (const linkedStack<myType>&);
        linkedStack();
        linkedStack(const linkedStack<myType> &);
        ~linkedStack();
        void deleteStack();
        bool isStackEmpty() const;
        void push (const myType &);
        myType peek() const;
        myType pop();
        int stackCount() const;
        myType stackSum() const;
};

/*linkedStack: initializes class variables
parameters: none
return type: none*/
template <class myType>
linkedStack<myType>::linkedStack(){
    stackTop=nullptr;
    count=0;
}

/*linkedStack(linkedStack): calls copyStack to make deep copy of the stack
parameters: const linkedStack<myType> &
return type: none*/
template <class myType>
linkedStack<myType>::linkedStack(const linkedStack<myType> & duplicate){
    count=duplicate.count;
    copyStack(duplicate);
}

/*~linkedStack: deletes the stack by calling deleteStack
parameters: none
return type: none*/
template <class myType>
linkedStack<myType>::~linkedStack(){
    deleteStack();
}

/*isStackEmpty: checks if the stack is empty
parameters: none
return type: bool*/
template <class myType>
bool linkedStack<myType>::isStackEmpty() const{
    if(stackTop == nullptr) //checks if the head of list exists
        return true;
    return false;
}

/*push: adds a new node to the top of the stack
parameters: const myType &
return type: void*/
template <class myType>
void linkedStack<myType>::push(const myType & item){
    nodeType<myType> * newItem=nullptr;

    newItem= new nodeType<myType>;
    newItem->info=item; 
    newItem->link=stackTop; //links new item to old head
    stackTop=newItem; //makes new item the head
    count++;
}

/*pop: removes the top node from the stack
parameters: none
return type: myType*/
template <class myType>
myType linkedStack<myType>::pop(){
    myType stackInfo={};
    nodeType<myType> * tempNode=nullptr;

    if(isStackEmpty()){ //exits if stack is empty
        cout<<"pop: Error, stack empty"<<endl;
        return {};
    }
    stackInfo=stackTop->info; //stores info in variable
    tempNode=stackTop; //temp pointer points to head
    stackTop=stackTop->link; //head points to next node
    delete tempNode; //deletes old head
    count--;
    return stackInfo; //returns the old head's info
}

/*peek: returns the info from the top of the stack
parameters: none
return type: myType*/
template <class myType>
myType linkedStack<myType>::peek() const{
     if(isStackEmpty()){ //exits if stack is empty
        cout<<"peek: Error, stack empty"<<endl;
        return {};
    }
    return stackTop->info;
}

/*stackCount: returns the count from the class
parameter: none
return type: int*/
template <class myType>
int linkedStack<myType>::stackCount() const{
    return count; 
}

/*stackSum: finds the sum of the stack
parameter: none
return type: myType*/
template <class myType>
myType linkedStack<myType>::stackSum() const{
    rSum(stackTop); //calls rSum to find sum
}

/*rSum: recursively finds the sum of the stack
parameter: nodeType <myType> *
return type: myType*/
template <class myType>
myType linkedStack<myType>::rSum(nodeType <myType> * top) const{
    if(top == nullptr) //base case, list is terminated with a nullptr
        return top->info;
    return top->info+rSum(top->link); //adds info for all nodes
}

/*operator ==: compares every value of the lists and returns true if they
        are the same
parameter: const linkedStack<myType>
return type: bool*/
template <class myType>
bool linkedStack<myType>::operator ==(const linkedStack<myType> & compare){
    nodeType<myType> *current=nullptr;
    nodeType<myType> *compareCurrent=nullptr;

    if(count != compare.count)
        return false;
    current=stackTop; //starts at the top of the stacks to traverse lists
    compareCurrent=compare.stackTop;
    while(current != nullptr){
        if(current->info != compareCurrent->info)
            return false;
        current=current->link; //moves to next node
        compareCurrent=compareCurrent->link;
    }
    return true;
}

/*opertator !=: compares every value of the lists and returns false if
        they are the same
parameter: const linkedStack<myType> &
return type: bool*/
template <class myType>
bool linkedStack<myType>::operator !=(const linkedStack<myType> & compare){
    nodeType<myType> *current=nullptr;
    nodeType<myType> *compareCurrent=nullptr;

    if(count != compare.count) //has same layout as operator == funct,
        return true;          //but different return values
    current=stackTop;
    compareCurrent=compare.stackTop;
    while(current != nullptr){
        if(current->info != compareCurrent->info)
            return true;
        current=current->link;
        compareCurrent=compareCurrent->link;
    }
    return false;
}

/*copyStack: makes a deep copy of the passed in stack
parameter: const linkedStack <myType> &
return type: void*/
template <class myType>
void linkedStack<myType>::copyStack(const linkedStack<myType> & duplicate){
    nodeType<myType> *current=nullptr;
    nodeType<myType> *duplicateCurrent=nullptr;
    nodeType<myType> *last=nullptr;
    
    stackTop=nullptr;
    duplicateCurrent=duplicate.stackTop;
    for(int i=0; i < count; i++){
        current=new nodeType<myType>;
        current->info=duplicateCurrent->info; //copies info in
        current->link=nullptr;
        if(stackTop == nullptr){ //labels first/last values as first node
            stackTop=current;
            last=current;
        }
        else{
            last->link=current; //makes current node the link of the prev
            last=current; //current node becomes the last node
        }
        duplicateCurrent=duplicateCurrent->link; //moves to next node
    }
}

/*deleteStack: deletes the values in the stack
parameters: none
return type: void*/
template <class myType>
void linkedStack<myType>::deleteStack(){
    nodeType<myType> * toDelete=nullptr;

    while(stackTop != nullptr){
        toDelete=stackTop; //points to head of list
        stackTop=stackTop->link; //head points to next in list
        delete toDelete; //deletes the old head
    }
}