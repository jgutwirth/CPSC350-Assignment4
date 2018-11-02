#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList {
private:

public:
    unsigned int size;
    ListNode<T> *front;
    ListNode<T> *back;

    DoublyLinkedList() {
        size = 0;
        front = NULL;
        back = NULL;
    }


    ~DoublyLinkedList() {
        if(size!=0){
            delete front;
            delete back;
        }
    }


    void insertBack(T d) {
        ListNode<T> *node = new ListNode<T>(d);

        //Empty
        if (size == 0) {
            front = node;
        }
            //Not Empty
        else {
            back->next = node;
            node->prev = back;
        }

        back = node;
        ++size;
    }


    T removeFront() {
        if (!isEmpty()) {
            ListNode<T> *node = front;
            //Only Node in List
            if (front->next == NULL) {
                front = NULL;
                back = NULL;
            }
                //More than One
            else {
                front->next->prev = NULL;
                front = front->next;
            }

            //node->next = NULL;

            T temp = node->data;

            delete node;
            --size;
            return temp;
        } else {
            return T();
        }
    }


    T getFront() {
        return front->data;
    }


    void printList() {
        ListNode<T> *curr = front;

        while (true) {
            if (curr->next == NULL) {
                break;
            }

            cout << curr->data << endl;
            curr = curr->next;
        }
    }


    void deletePos(int pos) {
        int idx = 0;
        ListNode<T> *curr = front;
        ListNode<T> *prev = front;

        while (idx != pos) {
            prev = curr;
            curr = curr->next;
            ++idx;
        }

        prev->next = curr->next;
        curr->next->prev = prev;
        curr->next = NULL;
        curr->prev = NULL;
        curr->data = NULL;

        --size;
        delete curr;
    }


    bool isEmpty() {
        return (size == 0);
    }


    unsigned int getSize() {
        return size;
    }
};
