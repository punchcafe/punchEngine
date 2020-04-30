#ifndef astral_body_dynamics_h
#define astral_body_dynamics_h
#include "../entity/EntityField.cpp"
#include "../utils/LinkedList.cpp"
#include "DynamicsModule.cpp"
#include "ForceContainer.cpp"
#include <Arduboy2.h>
class AstralBodyDynamics : public DynamicsModule{
private:
  Arduboy2* arduboy;
  EntityField* entityField;
  LinkedList<ForceContainer> forceContainers;
  float gravityConstant = 1.0;

public:

  AstralBodyDynamics(Arduboy2* arduboy, EntityField* entityFieldArg){
    this->arduboy = arduboy;
    this->entityField = entityFieldArg;
  }

  void resolveInterval(float interval){

    //this->entityField->moveEntity(0, 1, 1);

    for(int i = 0; i < this->forceContainers.getSize(); i++){
      // Resolve forces
      float resultantForceVector [3];
      FieldElement * subjectElement = this->forceContainers.get(i)->getFieldElement();
      int subjectMass = subjectElement->getMass();

      for(int j = 0; j < this->forceContainers.getSize(); j++){
        if(j != i){
          FieldElement * objectElement = this->forceContainers.get(j)->getFieldElement();
          //int xsep = subjectElement->getX() - objectElement->getX();
          //int ysep = subjectElement->getY() - objectElement->getY();
          //int zsep = subjectElement->getZ() - objectElement->getZ();
          //long radiusSquared = ((xsep*xsep) + (ysep*ysep) + (zsep*zsep));
          //float radius = sqrt(radiusSquared);
          arduboy->setCursor(10, 10);

          arduboy->print(',');

          //int radius = 1;
          int objectMass = objectElement->getMass();
          float gmag = 1;/*(this->gravityConstant * objectMass * subjectMass) / radiusSquared;*/
          //TODO: make this use constants
          //resultantForceVector[0] += gmag*((xsep*1.0) / radius);
          //resultantForceVector[1] += gmag*((ysep*1.0) / radius);
          //resultantForceVector[2] += gmag*((zsep*1.0) / radius);
        }
        //this->entityField->moveEntity(0, 1, 1);
      }
      subjectElement->setX(resultantForceVector[0]);
      subjectElement->setY(resultantForceVector[1]);
      subjectElement->setZ(resultantForceVector[2]);

      // Apply velocity changes
      // Move objects
    }

  }

  void respondToNewFieldElement(int i){
    forceContainers.append(new ForceContainer(&entityField->getEntity(i)));

  }
  //Indicates an element has been removed, and all elements after have been shifted
  void respondToRemoveFieldElement(int i){

  }

  void subscribeToEntityField(EntityField* field){

  }

private:


};
#endif
