#ifndef forceField_h
#define forceField_h

#include "forceBody.h"
#include "physicsResolver.h"
#include "VectorPath.cpp"
#include <Arduboy2.h>

class ForceField {
 int heroIndex = 0;
 int gConstant = 7;
 int timeConstant = 1;
 ForceBody* bodies [10]{0};
 PhysicsResolver physicsResolver;
 BodyVectorPath bodyVectorPath1;
 BodyVectorPath bodyVectorPath2;


 //ForceResolver->
 //AccelerationResolver->based on force bodies
 //VelocityAppender

 //max number of bodies in a frame
 //temporary fieldMapSoln, checks for 2
 //initially until i work out how to get fuckin vectors
 public:
   ForceField();
   ForceBody* getForceBody(int index);
   ForceBody* getHero();
   void setForceBody(int index, ForceBody* forceBody);
   void addGravity();
   void resolveColissions();
   void resolveVelocities();
   void resolveDisplacements();
   void resolveUserInput(Arduboy2 arduboy);
   bool isColliding(ForceBody* body, ForceBody* otherBody);
   //int forceVector resolveCollision(ForceBody body){return 0;};
};
#endif
