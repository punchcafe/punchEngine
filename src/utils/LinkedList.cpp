#ifndef linked_list_h
#define linked_list_h

#include "LinkedListElement.cpp"

template <class T>
class LinkedList{
private:
  int size;
  LinkedListElement<T>* head;
  LinkedListElement<T>* tail;

public:
  void append(T entry){
    LinkedListElement<T>* addition = new LinkedListElement<T>();
    addition.setIsTail(true);
    addition.setElement(entry);
    this->tail->setNextElement(addition);
    this->tail->setIsTail(false);
    this->tail = addition;
    size++;
  }

  int getSize(){
    return this->size;
  }

  T* get(int index){
    if(!(index >= this->size)){
      LinkedListElement<T>* element = this->head;
      for(int i = 0; i < index; i++){
        element = element->getNext();
      }
      return element->getElement();
    }

  }
};
#endif
