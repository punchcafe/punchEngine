#ifndef linked_list_element_h
#define linked_list_element_h

template <class T>
class LinkedListElement {
private:
  T* element;
  bool isTail;
  LinkedListElement* nextElement;

public:
  LinkedListElement(T element){
  }

  void setElement(T element){
    this->element = element;
  }

  void setIsTail(bool isTail){
    this->isTail = isTail;
  }

  void setNextElement(LinkedListElement* element){
    this->nextElement = element;
  }

  T* getElement(){
    return this->element;
  }
  bool getIsTail(){
    return this->isTail;
  }
  LinkedListElement* getNext(){
    return this->nextElement;
  }
};

#endif
