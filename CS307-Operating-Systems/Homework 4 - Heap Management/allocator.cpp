#ifndef _ALLOCATOR_CPP
#define _ALLOCATOR_CPP

#include <iostream>
#include <pthread.h>

using namespace std;

struct node_t
{
    int id;
    int size;
    int index;

    node_t* next;

    node_t(int a, int b, int c, node_t* d)
        : id(a), size(b), index(c), next(d) {}
};

class HeapManager
{
public:
    HeapManager();

    int initHeap(int size);
    int myMalloc(int ID, int size);
    int myFree(int ID, int index);

    void print();

private:
    void merge(node_t* node1, node_t* node2); //  a private member function for coalescing node1 with node2, which is called in myFree()

    node_t* head;               //  head pointer to free list
    pthread_mutex_t heapMutex;  //  a member mutex lock for concurrency
};

HeapManager::HeapManager()
    : head(NULL), heapMutex(PTHREAD_MUTEX_INITIALIZER) {}

int HeapManager::myMalloc(int ID, int size) {
    pthread_mutex_lock(&heapMutex);

    node_t* ptr = head;
    node_t tempNode(-1,-1,-1, head);
    node_t* prevNode = &tempNode;

    int returnValue;
    
    while (ptr != NULL) //  searching for a suitable chunk
    {
        if (ptr->id == -1 && ptr->size >= size) {
            break;
        }
        ptr = ptr->next;
        prevNode = prevNode->next;
    }

    if (ptr == NULL) {  //  suitable chunk could not found
        cout << "Can not allocate, requested size " << size << " for thread " << ID << " is bigger than remaining size" << endl;
        this->print();
        
        returnValue = -1;
    }
    else {  //  suitable chunk found
        node_t* newAlloc = new node_t(ID, size, ptr->index, ptr);   //  new chunk which is allocated by a thread
        
        if (prevNode->index == -1) {
            head = newAlloc;
        }
        else {
            prevNode->next = newAlloc;
        }

        ptr->size -= size;
        ptr->index += size;
        
        if (ptr->size == 0) {   //  if second chunk's size is 0 after splitting (which means the chunk found has a size exact that required)
            newAlloc->next = ptr->next;
            delete ptr;
        }

        cout << "Allocated for thread " << ID << endl;
        this->print();
        
        returnValue = newAlloc->index;
    }

    pthread_mutex_unlock(&heapMutex);
    return returnValue;
}

void HeapManager::merge(node_t* node1, node_t* node2) { //  adding node2 onto node1
    node1->size += node2->size;
    node1->next = node2->next;

    delete node2;
}

int HeapManager::myFree(int ID, int index) {
    pthread_mutex_lock(&heapMutex);

    node_t* ptr = head;
    node_t tempNode(-2,-1,-1, head);
    node_t* prevNode = &tempNode;

    int returnValue;

    while (ptr != NULL) //  searching for the target chunk
    {
        if (ptr->id == ID && ptr->index == index) {
            break;
        }
        ptr = ptr->next;
        prevNode = prevNode->next;
    }
    
    if (ptr == NULL) {  //  target chunk does not exist
        cout << "Can not free, there is no such chunk allocated by thread " << ID <<  " with index " << index << endl;
        this->print();

        returnValue = -1;
    }
    else {  //  target chunk exists
        ptr->id = -1;   //  freeing the chunk


        //  freeing cases on page 3, figure 2 in PA4 document

        if (prevNode->id != -1 && ptr->next->id != -1) { // case (a), do nothing in this case
            int x = 3; // dummy
        }
        else if (prevNode->id != -1 && ptr->next->id == -1) { // case (b): merge target chunk with the next chunk
            merge(ptr, ptr->next);
        }
        else if (prevNode->id == -1 && ptr->next->id != -1) { // case (c): merge previous chunk and the target chunk
            merge(prevNode, ptr);
        }
        else if (prevNode->id == -1 && ptr->next->id == -1) { // case (d): merge previous, target and next chunk
            merge(ptr, ptr->next);
            merge(prevNode, ptr);
        }

        cout << "Freed for thread " << ID << endl;
        this->print();
        
        returnValue = 1;
    }

    pthread_mutex_unlock(&heapMutex);
    return returnValue;
}

void HeapManager::print() {
    node_t* ptr = head;
    while (ptr != NULL)
    {
        cout << "[" << ptr->id << "][" << ptr->size << "][" << ptr->index << "]";
        if (ptr->next != NULL) {
            cout << "---";
        }
        ptr = ptr->next;
    }
    cout << endl;
}

int HeapManager::initHeap(int size) {
    head = new node_t(-1, size, 0, NULL);
    cout << "Memory initialized" << endl;
    this->print();
    return 1;
}

#endif