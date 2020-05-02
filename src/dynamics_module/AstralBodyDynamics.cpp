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
    int numberOfForceContainers = this->forceContainers.getSize();

    for(int i = 0; i < numberOfForceContainers; i++){
      // Resolve forces
      float resultantForceVector [3] = {0, 0, 0};
      FieldElement * subjectElement = this->forceContainers.get(i)->getFieldElement();
      int subjectMass = subjectElement->getMass();

      arduboy->print(subjectMass);

      for(int j = 0; j < numberOfForceContainers; j++){
        if(j != i){

          FieldElement * objectElement = this->forceContainers.get(j)->getFieldElement();
          int xsep = subjectElement->getX() - objectElement->getX();
          int ysep = subjectElement->getY() - objectElement->getY();
          int zsep = subjectElement->getZ() - objectElement->getZ();

          long radiusSquared = ((xsep*xsep) + (ysep*ysep) + (zsep*zsep));
          float radius = 10;
          //TODO: fix radius
          //float radius = sqrt(radiusSquared);

          int objectMass = objectElement->getMass();
          //TODO: fix gmag
          //float gmag = (this->gravityConstant * objectMass * subjectMass) / radiusSquared;
          float gmag = 1;
          //TODO: make this use constants
          resultantForceVector[0] += gmag*((xsep*1.0) / radius);
          resultantForceVector[1] += gmag*((ysep*1.0) / radius);
          resultantForceVector[2] += gmag*((zsep*1.0) / radius);

        }
      }
      this->forceContainers.get(i)->setX(resultantForceVector[0]);
      this->forceContainers.get(i)->setY(resultantForceVector[1]);
      this->forceContainers.get(i)->setZ(resultantForceVector[2]);
      resolveVelocity(this->forceContainers.get(i), 0.1f);
      // Apply velocity changes
      // Move objects

    }
    moveEntities(1);


  }

  void resolveVelocity(ForceContainer* container, float interval){
    container->setVX(container->getVX()+(container->getX()*interval)/(container->getMass()*1.0f));
    container->setVY(container->getVY()+(container->getY()*interval)/(container->getMass()*1.0f));
    container->setVZ(container->getVZ()+(container->getZ()*interval)/(container->getMass()*1.0f));
  }

  void moveEntities(float interval){
    for(int i = 0; i < forceContainers.getSize(); i++){
      this->entityField->moveEntity(i, this->forceContainers.get(i)->getVX()*interval*-1, this->forceContainers.get(i)->getVY()*interval*-1);
    }
  }

  void respondToNewFieldElement(int i){
    forceContainers.append(new ForceContainer(this->entityField->getEntity(i)));
  }
  //Indicates an element has been removed, and all elements after have been shifted
  void respondToRemoveFieldElement(int i){

  }

  void subscribeToEntityField(EntityField* field){

  }

private:


};
#endif
