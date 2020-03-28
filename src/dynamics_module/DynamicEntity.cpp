#ifndef dynamic_entity_h
#define dynamic_entity_h
#include "../entity/FieldElement.cpp"
class DynamicEntity{
private:
  FieldElement* rawElement;
public:
  DynamicEntity(FieldElement* fieldElement){
    this->rawElement = fieldElement;
  }
};
#endif
