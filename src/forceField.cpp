#include "forceField.h"
#include <Arduboy2.h>

ForceField::ForceField() {};
  //MAKE SPECIAL FORCEBODY, 0th index?
ForceBody* ForceField::getForceBody(int index) {
  return bodies[index];
}

ForceBody* ForceField::getHero() {
  return bodies[heroIndex];
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
            if(bodies[i]->getYForceVector() > 0) bodies[i]->set_vy(0);
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
      int xVel = bodies[i]->get_vx() + ((bodies[i]->getXForceVector())/(bodies[i]->getMass()))*1;
      int yVel = bodies[i]->get_vy() + bodies[i]->getYForceVector();
      bodies[i]->set_vx(xVel <= 10 ? xVel : 10);//TIME
      bodies[i]->set_vy(yVel <= 10 ? yVel : 10);//NEEDS MASS
    }
  }
}

void ForceField::resolveDisplacements(){
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      int yDisplace = bodies[i]->get_sy()+bodies[i]->get_vy();
      bodies[i]->set_sx(bodies[i]->get_sx()+bodies[i]->get_vx());
      bodies[i]->set_sy(yDisplace < 500 ? yDisplace : 500);//time unit, pass through constructor.
    }
  }
}

void ForceField::resolveUserInput(Arduboy2 arduboy){
  getHero()->set_vx(0);
  if(arduboy.pressed(RIGHT_BUTTON)){
    getHero()->set_vx(10);
  } else if (arduboy.pressed(LEFT_BUTTON)){
    getHero()->set_vx(-10);
  }
  if(arduboy.pressed(B_BUTTON)){
     if(getHero()->get_vy() == 0 || getHero()->get_sy() ==500){
      getHero()->set_vy(-50);
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
      smallerBody->getCollisionZone_x2(),
      smallerBody->getCollisionZone_y1()
    },
    {
      smallerBody->getCollisionZone_x2(),
      smallerBody->getCollisionZone_y2()
    },
    {
      smallerBody->getCollisionZone_x1(),
      smallerBody->getCollisionZone_y2()
      },
    {
      smallerBody->getCollisionZone_x1(),
      smallerBody->getCollisionZone_y1()
    }
  };
//change it to halflength half height
  for(int i = 0; i<4; i++){
    result = result || physicsResolver.isContact(
      smallerBodyCorners[i],
      biggerBody->getCollisionZone_x1(),
      biggerBody->getCollisionZone_x2(),
      biggerBody->getCollisionZone_y1(),
      biggerBody->getCollisionZone_y2()
      );
  }

  return result;
}
