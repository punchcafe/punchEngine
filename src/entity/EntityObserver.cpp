#include "FieldElement.cpp"
#ifndef entity_observer
#define entity_observer

class EntityObserver{
public:
  //Indicates a new entity at index i
  virtual void respondToNewFieldElement(int i);
  //Indicates an element has been removed, and all elements after have been shifted
  virtual void respondToRemoveFieldElement(int i);
};
#endif
