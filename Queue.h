
#include <iostream>
#include "ListNode.h"

using namespace std;

    template <class T>
    class GenQueue {
    private:

    public:
        unsigned int numElements;
        ListNode<T> *front;
        ListNode<T> *back;

        GenQueue() {
            numElements = 0;
            front = NULL;
            back = NULL;
        }

        ~GenQueue() {

        }

        void enqueue(T d) {
            ListNode<T> *node = new ListNode<T>(d);

            if (numElements == 0) {
                front = node;
            } else {
                back->next = node;
                node->prev = back;
            }

            back = node;
            ++numElements;
        }

        T dequeue() {
            if (!isEmpty()) {
                ListNode<T> *node = front;

                T temp = node->data;

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

                delete node;
                --numElements;
                return temp;
            } else {
                return T();
            }
        }

        T Front() {
            return front->data;
        }


        T Back() {
            return back->data;
        }


        void printQ() {
            ListNode<T> *curr = front;

            while (true) {
                if (curr != NULL) {
                    cout << curr->data << endl;
                    curr = curr->next;
                } else {
                    break;
                }
            }
        }


        bool isEmpty() {
            return (numElements == 0);
        }


        unsigned int getSize() {
            return numElements;
        }
    };
