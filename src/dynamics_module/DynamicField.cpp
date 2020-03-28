#ifndef dynamic_field_h
#define dynamic_field_h
#include "DynamicsModule.cpp"
#include "../entity/EntityField.cpp"
#include "DynamicEntity.cpp"
// 2d Platform physics
class DynamicField : public DynamicsModule {
  EntityField* field;
  DynamicEntity* entities;
public:
  void respondToNewFieldElement(int i){
    FieldElement* newElement = &(field->getEntity(i)); // Assumes overwriting of current
    DynamicEntity* newDynamicEntity = new DynamicEntity(newElement);
    this->entities[i] = *newDynamicEntity;
  }
  void respondToRemoveFieldElement(int i){}

  void subscribeToEntityField(EntityField* field){
    this->field = field;
  }
};
#endif
