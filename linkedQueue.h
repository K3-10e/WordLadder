/*Description: file implements a queue through the linkedQueue class
*/

/*Algorithm: 
1. Create the constructor by calling the initializeQueue function
2. Make the copy constructor by calling copyQueue making a deep copy
3. Deallocate the memeory with the destructor
4. Make isEmptyQueue by checking if the front pointer is null then returning
    true if it is
5. add the new data with enqueue adding it to the end of the list and moving
    the end pointer to the new data
6. delete the head of the node with dequeue moving the queue front pointer
    and returning the data in it
7. make back and front function by returning the info of the queueFront
    and queueRear pointer
8. make the operator= by calling the copyQueue function
9. make copyQueue by copying in the count, and deep copying in the data
10. print the queue by traversing the list and printing until the end
11. make queueCount by returning the count from the queue*/

#include <iostream>

using namespace std;

template <class Type>
struct queueNodeType{
    Type info;
    queueNodeType<Type> *link;
};

template <class Type>
class linkedQueue{
    private:
        queueNodeType<Type> *queueFront;
        queueNodeType<Type> *queueRear;
        int count;
        void copyQueue(const linkedQueue<Type>& otherQueue);
    
    public:
        linkedQueue<Type> & operator =(const linkedQueue<Type>&);
        linkedQueue();
        linkedQueue(const linkedQueue<Type>& otherQueue);
        ~linkedQueue();
        bool isEmptyQueue() const;
        void initializeQueue();
        void enqueue(const Type& newItem);
        Type front() const;
        Type back() const;
        Type dequeue();
        int queueCount();
        void printQueue();
};

/*linkedQueue: initializes the class memebers
parameters: none
return type: none*/
template <class Type>
linkedQueue<Type>::linkedQueue(){
    initializeQueue();
}

/*linkedQueue(linkedQueue): makes a deep copy of the passed in class
parameters: const linkedQueue<Type> & 
return type: none*/
template <class Type>
linkedQueue<Type>::linkedQueue(const linkedQueue<Type>& copy){
    initializeQueue();
    copyQueue(copy);
}

/*~linkedQueue: Deallocates the linked list
parameters: none
return type: none*/
template <class Type>
linkedQueue<Type>::~linkedQueue(){
    queueNodeType<Type> * toDelete=nullptr;

    while(queueFront != nullptr){
        toDelete=queueFront; //temporarily stores the head node
        queueFront=queueFront->link; //moves the head to the next node
        delete toDelete; //deletes the old head node
    }
}

/*initializeQueue: sets the memebers of the queue to 0 or null
parameters: none
return type: void*/
template <class Type>
void linkedQueue<Type>::initializeQueue(){
    queueFront=nullptr;
    queueRear=nullptr;
    count=0;
}

/*isEmptyQueue: checks whether the queue is empty or not, returns true if 
        empty and false otherwise
parameters: none
return type: bool*/
template <class Type>
bool linkedQueue<Type>::isEmptyQueue() const{
    if(queueFront == nullptr) //if the head doesn't exist, it is empty
        return true;
    return false;
}

/*enqueue: adds a new node to the end of the linked list
parameters: const Type &
return type: void*/
template <class Type>
void linkedQueue<Type>::enqueue(const Type & item){
    queueNodeType<Type> * current=nullptr;

    current=new queueNodeType<Type>;
    current->info=item;
    current->link=nullptr;
    count++;
    if(isEmptyQueue()){ //sets front and end nodes if it is the first node
        queueFront=current; 
        queueRear=current;
        return; //exists because there's no node in front to link this to
    }
    queueRear->link=current; //links the previous node to the new node
    queueRear=current; //sets the new node to the last node
}

/*front: returns the data from queueFront
paramters: none
return type: Type*/
template <class Type>
Type linkedQueue<Type>::front() const{
    return queueFront->info;
}

/*back: returns the data from queueRear
parameters: none
return type: Type*/
template <class Type>
Type linkedQueue<Type>::back() const{
    return queueRear->info;
}

/*dequeue: deletes the node from the head, moves the head to the next
        node, and returns the data from the deleted node
parameter: none
return type: Type*/
template <class Type>
Type linkedQueue<Type>::dequeue(){
    queueNodeType<Type> * temp=nullptr;
    Type queueInfo={};

    if(isEmptyQueue()) //exits if the queue is empty
        return {};

    queueInfo=queueFront->info; //stores the node's data into a variable
    temp=queueFront; //temp pointer points to the head of the list
    queueFront=queueFront->link; //queueFront points to the next node
    delete temp; //deletes old head
    count--;
    return queueInfo; //returns data from the variable   
}

/*operator =: deep copies in the data from the passed class
parameter: const linkedQueue<Type> &
return type: linkedQueue<Type> &*/
template <class Type>
linkedQueue<Type> & linkedQueue<Type>::operator =(const linkedQueue<Type>& compare){
    copyQueue(compare);
    return *this;
}

/*copyQueue: makes a deep copy of the linked list
parameter: const linkedQueue<Type> &
return type: void*/
template <class Type>
void linkedQueue<Type>::copyQueue(const linkedQueue<Type> & duplicate){
    queueNodeType<Type> * current=nullptr;
    queueNodeType<Type> * duplicateCurrent=nullptr;
    count=duplicate.count;
    queueFront=nullptr;

    duplicateCurrent=duplicate.queueFront; //creates a pointer to traverse
    for(int i=0; i < count; i++){ 
        current=new queueNodeType<Type>;
        current->info=duplicateCurrent->info; //copies info
        current->link=nullptr;
        if(queueFront == nullptr){ //sets pointers to first created node
            queueFront=current;
            queueRear=current;
        }
        else{
            queueRear->link=current; //sets link of previous to new node
            queueRear=current; //sets new node as the last node
        }
        duplicateCurrent=duplicateCurrent->link; //goes to the next node
    }
}

/*printQueue: prints the values in the queue
parameter: none
return type: void*/
template <class Type>
void linkedQueue<Type>::printQueue(){
    queueNodeType<Type> * current=nullptr;

    current=queueFront; //sets temp node to head to traverse list
    while(current != nullptr){ //traverses list until the end (nullptr)
        cout<<current->info<<" ";
        current=current->link; //moves to the next node
    }
}

/*queueCount: returns the count from the queue
parameter: none
return type: int*/
template <class Type>
int linkedQueue<Type>::queueCount(){
    return count;
}