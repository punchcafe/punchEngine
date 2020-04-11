/*
If injected, all entities will have simple top down cbehaviour.
Entities with greater than 0 mass will collide, preventing movement.
*/
#ifndef top_down_dynamics_h
#define top_down_dynamics_h
#include "../entity/EntityField.cpp"
#include "DynamicsModule.cpp"
#include <Arduboy2.h>
class TopDownDynamics : public DynamicsModule{
private:
  Arduboy2* arduboy;
  EntityField* entityField;
public:

  TopDownDynamics(Arduboy2 arduboy, EntityField* entityField){
    this->arduboy = &arduboy;
    this->entityField = entityField;
  }

  resolveInterval(float interval){
    if(arduboy->pressed(LEFT_BUTTON)){
      entityField->moveEntity(0, -1, 0);
    } else if (arduboy->pressed(RIGHT_BUTTON)){
      entityField->moveEntity(0, 1, 0);
    } else if (arduboy->pressed(UP_BUTTON)){
      entityField->moveEntity(0, 0, -1);
    } else if (arduboy->pressed(DOWN_BUTTON)){
      entityField->moveEntity(0, 0, 1);
    }
  }

  void respondToNewFieldElement(int i){

  }
  //Indicates an element has been removed, and all elements after have been shifted
  void respondToRemoveFieldElement(int i){

  }

  virtual void subscribeToEntityField(EntityField* field){

  }

};
#endif
