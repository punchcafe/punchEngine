#ifndef forceField_h
#define forceField_h

#include "forceBody.h"
#include "physicsResolver.h"

class ForceField {
 int gConstant = 10;
 ForceBody* bodies [10]{0};
 PhysicsResolver physicsResolver;
 //ForceResolver->
 //AccelerationResolver->based on force bodies
 //VelocityAppender

 //max number of bodies in a frame
 //temporary fieldMapSoln, checks for 2
 //initially until i work out how to get fuckin vectors
 public:
   ForceField();
   ForceBody* getForceBody(int index);
   void setForceBody(int index, ForceBody* forceBody);
   void addGravity();
   void resolveColissions();
   //void resolveVelocities
   //for(i in bodies){ bodies[i]->getBody()->setVelocity(velocity + (force/mass)*UNIT_TIME) }

   //void resolveDisplacements
   //s = s + v*t
   bool isColliding(ForceBody* body, ForceBody* otherBody);
   //int forceVector resolveCollision(ForceBody body){return 0;};
};
#endif
