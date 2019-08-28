#include "forceField.h"

ForceField::ForceField() {};
  //MAKE SPECIAL FORCEBODY, 0th index?
ForceBody* ForceField::getForceBody(int index) {
  return bodies[index];
}
void ForceField::setForceBody(int index, ForceBody* forceBody) {
  bodies[index] = forceBody;
}

//parent in resolveForces

void ForceField::addGravity(){
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      int forceVector [2] = {bodies[i]->getXForceVector(), bodies[i]->getMass()*gConstant};
      bodies[i]->setForceVector(forceVector);
    }
  }
}

void ForceField::resolveColissions(){
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      for(int j = 0; j < sizeof(bodies); j++){
        if(j != i && bodies[j] != 0){
          if(isColliding(bodies[i],bodies[j])){
            int forceVector [2] = {bodies[i]->getXForceVector(), 0};
            bodies[i]->setForceVector(forceVector);
          }
        }
      }
    }
  }
}

void ForceField::resolveVelocities(){
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      //int forceVector [2] = {bodies[i]->getXForceVector(), bodies[i]->getXForceVector()};
      //bodies[i]->setForceVector(forceVector);
    }
  }
}

void ForceField::resolveDisplacements(){
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      bodies[i]->set_sx(bodies[i]->get_vx()*1);
      bodies[i]->set_sy(bodies[i]->get_vx()*1);//time unit, pass through constructor.
    }
  }
}


bool ForceField::isColliding(ForceBody* body, ForceBody* otherBody){
  //only works for squares
  bool result = false;
  ForceBody* smallerBody = body->getHalfWidth() > otherBody->getHalfWidth() ?
                            body : otherBody;
  ForceBody* biggerBody = body->getHalfWidth() > otherBody->getHalfWidth() ?
                            otherBody : body;
  int smallerBodyCorners[4][2] = {
    {
      smallerBody->get_sx()+smallerBody->getHalfWidth(),
      smallerBody->get_sy()-smallerBody->getHalfWidth()
    },
    {
      smallerBody->get_sx()+smallerBody->getHalfWidth(),
      smallerBody->get_sy()+smallerBody->getHalfWidth()
    },
    {
      smallerBody->get_sx()-smallerBody->getHalfWidth(),
      smallerBody->get_sy()+smallerBody->getHalfWidth()
      },
    {
      smallerBody->get_sx()-smallerBody->getHalfWidth(),
      smallerBody->get_sy()-smallerBody->getHalfWidth()
    }
  };
//change it to halflength half height
  for(int i = 0; i<4; i++){
    result = result || physicsResolver.isContact(
      smallerBodyCorners[i],
      biggerBody->get_sx()-biggerBody->getHalfWidth(),
      biggerBody->get_sx()+biggerBody->getHalfWidth(),
      biggerBody->get_sy()-biggerBody->getHalfWidth(),
      biggerBody->get_sy()+biggerBody->getHalfWidth()
      );
  }

  return result;
}
