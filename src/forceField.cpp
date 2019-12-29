#include "forceField.h"
#include <Arduboy2.h>
#include "geometryUtils.cpp"

ForceField::ForceField() {};
  //MAKE SPECIAL FORCEBODY, 0th index?
ForceBody* ForceField::getForceBody(int index) {
  if(index != heroIndex){
    return bodies[index];
  } else {
    //throw error?
  }
}

ForceBody* ForceField::getHero() {
  return bodies[heroIndex];
}

void ForceField::setForceBody(int index, ForceBody* forceBody) {
  bodies[index] = forceBody;
}

//parent in resolveForces

void ForceField::addGravity(){
  // BIG REFACTOR
  // Only apply on stuff which is a dynamic body.
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      if(bodies[i]->getBodyType() == ForceBody::BodyType::DYNAMIC){
        // Currently is the default
        int forceVector [2] = {bodies[i]->getXForceVector(), bodies[i]->getMass()*gConstant};
        bodies[i]->setForceVector(forceVector);
      }
    }
  }
}

void ForceField::resolveColissions(){
  // Resolves forces on bodies from collisions

  // BIG REFACTOR
  // pass (i,j) -> {} resolver?
  // resolve collisions just cares about detection
  // Detect using path calculation, and watch for any overlapping
  // aspects.

  //
  for(int i = 0; i < sizeof(bodies); i++){
    if(bodies[i] != 0){
      for(int j = 0; j < sizeof(bodies); j++){
        // establish collision types, Top, Bottom etc
        // bodyVectorPath1.wrapBody(bodies[i]);
        //TODO: add checking for resolution types, dynamic, platform etc.
        if(j != i && bodies[j] != 0){
          // bodyVectorPath2.wrapBody(bodies[j]);
          if(isColliding(bodies[i],bodies[j])){
            int forceVector [2] = {bodies[i]->getXForceVector(), 0};
            if(bodies[i]->get_vy() > 0){
              // Haandles falling from above to platform
              // If the object still has velocity, apply an impulse to set its velocity to 0;
              // a*t = v => a = v/t
              // f = ma
              // QED => f = m*(v/t)
              // *-1 for inverse

              //Extract to getStoppingImpulse(forceBody)
              forceVector[1] = ((bodies[i]->get_vy()/timeConstant)*bodies[i]->getMass())*-1;
            }
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
      bodies[i]->set_vy(yVel <= 50 ? yVel : 50);//NEEDS MASS
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

ForceField::CollisionType ForceField::collisionCase(ForceBody* body, ForceBody* otherBody){

  if(
    GeometryUtils::isBetweenInclusive(body->getCollisionZone_x1(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
    || GeometryUtils::isBetweenInclusive(body->getCollisionZone_x2(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
    || GeometryUtils::surroundsPoints(body->getCollisionZone_x1(), body->getCollisionZone_x2(),otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
  ){
    // Same x position
    if(
      !GeometryUtils::isBetweenInclusive(body->getCollisionZone_y1(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
      && GeometryUtils::isBetweenInclusive(body->getCollisionZone_y2(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
    ){
      return ForceField::CollisionType::TOP;
    }
    if(
      GeometryUtils::isBetweenInclusive(body->getCollisionZone_y1(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
      && !GeometryUtils::isBetweenInclusive(body->getCollisionZone_y2(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
    ){
      return ForceField::CollisionType::BOTTOM;
    }

  }

  if(
    GeometryUtils::isBetweenExclusive(body->getCollisionZone_y1(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
    || GeometryUtils::isBetweenExclusive(body->getCollisionZone_y2(), otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
    || GeometryUtils::surroundsPoints(body->getCollisionZone_y1(), body->getCollisionZone_y2(),otherBody->getCollisionZone_y1(), otherBody->getCollisionZone_y2())
  ){
    // Same y position
    if(
      GeometryUtils::isBetweenInclusive(body->getCollisionZone_x1(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
      && !GeometryUtils::isBetweenInclusive(body->getCollisionZone_x2(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
    ){
      return ForceField::CollisionType::LEFT;
    }
    if(
      !GeometryUtils::isBetweenInclusive(body->getCollisionZone_x1(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
      && GeometryUtils::isBetweenInclusive(body->getCollisionZone_x2(), otherBody->getCollisionZone_x1(), otherBody->getCollisionZone_x2())
    ){
      return ForceField::CollisionType::RIGHT;
    }
  }
  return ForceField::CollisionType::NONE;
}

bool ForceField::isColliding(ForceBody* body, ForceBody* otherBody){
  //only works for squares
  // TODO: seperate into a enum returning collision TYPES
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
