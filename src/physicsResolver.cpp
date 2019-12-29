#include "physicsResolver.h"

bool PhysicsResolver::isContact(int p [2] , int x_1, int x_2, int y_1, int y_2){
  //seperate
  //make this body.isContact(refferenceBody)? or keep static for memory
 bool result = (((x_1-1 <= p[0]) && (p[0] <= (x_2 +1)))&&(((y_1 - 1) <= p[1]) && (p[1] <= (y_2 + 1))));
 return result;
}

static int PhysicsResolver::stoppingImpulse(int velocity, int duration, int mass){
  return (velocity/duration)*mass*-1;
  // a*t = v => a = v/t
  // f = ma
  // QED => f = m*(v/t)
  // *-1 for inverse
}
