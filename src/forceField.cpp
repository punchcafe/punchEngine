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
      int forceVector [2] = {bodies[i]->getXForceVector(), bodies[i]->getBody()->getMass()*gConstant};
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

//void resolveVelocities
//for(i in bodies){ bodies[i]->getBody()->setVelocity(velocity + (force/mass)*UNIT_TIME) }

//void resolveDisplacements
//s = s + v*t

bool ForceField::isColliding(ForceBody* body, ForceBody* otherBody){
  //only works for squares
  bool result = false;
  ForceBody* smallerBody = body->getBody()->getHalfWidth() > otherBody->getBody()->getHalfWidth() ?
                            body : otherBody;
  ForceBody* biggerBody = body->getBody()->getHalfWidth() > otherBody->getBody()->getHalfWidth() ?
                            otherBody : body;
  int smallerBodyCorners[4][2] = {
    {
      smallerBody->getBody()->get_sx()+smallerBody->getBody()->getHalfWidth(),
      smallerBody->getBody()->get_sy()-smallerBody->getBody()->getHalfWidth()
    },
    {
      smallerBody->getBody()->get_sx()+smallerBody->getBody()->getHalfWidth(),
      smallerBody->getBody()->get_sy()+smallerBody->getBody()->getHalfWidth()
    },
    {
      smallerBody->getBody()->get_sx()-smallerBody->getBody()->getHalfWidth(),
      smallerBody->getBody()->get_sy()+smallerBody->getBody()->getHalfWidth()
      },
    {
      smallerBody->getBody()->get_sx()-smallerBody->getBody()->getHalfWidth(),
      smallerBody->getBody()->get_sy()-smallerBody->getBody()->getHalfWidth()
    }
  };
//change it to halflength half height
  for(int i = 0; i<4; i++){
    result = result || physicsResolver.isContact(
      smallerBodyCorners[i],
      biggerBody->getBody()->get_sx()-biggerBody->getBody()->getHalfWidth(),
      biggerBody->getBody()->get_sx()+biggerBody->getBody()->getHalfWidth(),
      biggerBody->getBody()->get_sy()-biggerBody->getBody()->getHalfWidth(),
      biggerBody->getBody()->get_sy()+biggerBody->getBody()->getHalfWidth()
      );
  }

  return result;
}
