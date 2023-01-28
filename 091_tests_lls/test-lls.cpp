#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

using namespace std;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront1() {
    // WRITE ME
    IntList il;
    il.addFront(1);

    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.getSize() == 1);

    assert(il.head->data == 1);
    assert(il.tail->data == 1);

    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);

    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
  }

  void testAddFront2() {
    IntList il;
    il.addFront(1);
    il.addFront(2);

    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.getSize() == 2);

    assert(il.head->data == 2);
    assert(il.tail->data == 1);

    assert(il.head->prev == NULL);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 1);

    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 2);
  }
  // many more tester methods
  void testAddBack1() {
    IntList il;
    il.addBack(1);

    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.getSize() == 1);

    assert(il.head->data == 1);
    assert(il.head->data == 1);

    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);

    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
  }

  void testAddBack2() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    assert(il.head != NULL);
    assert(il.tail != NULL);
    assert(il.getSize() == 2);

    assert(il.head->data == 1);
    assert(il.tail->data == 2);

    assert(il.head->prev == NULL);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 2);

    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 1);
  }

  void testCopyConstr() {
    IntList il1;

    for (int i = 0; i < 3; i++) {
      il1.addFront(i);
    }

    IntList il2(il1);

    assert(il2.head != NULL);
    assert(il2.tail != NULL);
    assert(il2.getSize() == il1.getSize());
    assert(il1.getSize() == 3);

    IntList::Node * curr1 = il1.head;
    IntList::Node * curr2 = il2.head;
    assert(curr1->prev == NULL);
    assert(curr2->prev == NULL);
    while (curr1->next != NULL && curr2->next != NULL) {
      assert(curr1->data == curr2->data);
      curr1 = curr1->next;
      curr2 = curr2->next;
    }
    assert(curr1->next == NULL);
    assert(curr2->next == NULL);
    while (curr1->prev != NULL && curr2->prev != NULL) {
      assert(curr1->data == curr2->data);
      curr1 = curr1->prev;
      curr2 = curr2->prev;
    }
    //assert(il2.head->data == il1.head->data);
    //assert(il2.tail->data == il1.tail->data);
    //assert(il2.head->next->data == il1.head->next->data);
    //assert(il2.tail->prev->data == il1.tail->prev->data);
  }

  void testAssignOper() {
    IntList il1;
    IntList il2;

    for (int i = 0; i < 3; i++) {
      il1.addFront(i);
    }
    il2.addFront(3);
    il2 = il1;

    assert(il2.head != NULL);
    assert(il2.tail != NULL);
    assert(il2.getSize() == il1.getSize());
    assert(il2.getSize() == 3);

    IntList::Node * curr1 = il1.head;
    IntList::Node * curr2 = il2.head;
    assert(curr1->prev == NULL);
    assert(curr2->prev == NULL);
    while (curr1->next != NULL && curr2->next != NULL) {
      assert(curr1->data == curr2->data);
      curr1 = curr1->next;
      curr2 = curr2->next;
    }
    assert(curr1->next == NULL);
    assert(curr2->next == NULL);
    while (curr1->prev != NULL && curr2->prev != NULL) {
      assert(curr1->data == curr2->data);
      curr1 = curr1->prev;
      curr2 = curr2->prev;
    }
    //assert(il2.head->data == il1.head->data);
    //assert(il2.tail->data == il1.tail->data);
    //assert(il2.head->next->data == il1.head->next->data);
    //assert(il2.tail->prev->data == il1.tail->prev->data);
  }

  void testRemoveHead() {
    IntList il1;
    il1.addFront(1);
    il1.remove(1);
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
    assert(il1.getSize() == 0);

    IntList il;

    for (int i = 0; i < 4; i++) {
      il.addFront(i);
    }

    il.remove(3);
    assert(il.getSize() == 3);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
  }

  void testRemoveTail() {
    IntList il;
    for (int i = 0; i < 4; i++) {
      il.addFront(i);
    }

    il.remove(0);
    assert(il.getSize() == 3);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
  }

  void testRemoveMid() {
    IntList il;
    for (int i = 0; i < 4; i++) {
      il.addFront(i);
    }

    il.remove(2);
    assert(il.getSize() == 3);
    assert(il.head->next->data == 1);
    assert(il.tail->prev->prev->data == 3);
  }

  void testRemoveGen() {
    IntList il;

    il.addFront(1);
    bool removeOne = il.remove(1);
    assert(removeOne == true);

    il.addFront(1);
    bool removeTwo = il.remove(2);
    assert(removeTwo == false);
  }
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront1();
  t.testAddFront2();
  t.testAddBack1();
  t.testAddBack2();
  t.testCopyConstr();
  t.testAssignOper();
  t.testRemoveHead();
  t.testRemoveTail();
  t.testRemoveMid();
  t.testRemoveGen();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
