
#ifndef entity_observer_h
#define entity_observer_h

#include "EntityField.cpp"

class EntityObserver {
public:
  //Indicates a new entity at index i
  virtual void respondToNewFieldElement(int i);
  //Indicates an element has been removed, and all elements after have been shifted
  virtual void respondToRemoveFieldElement(int i);

  //virtual void subscribeToEntityField(EntityField* field);
};
#endif
