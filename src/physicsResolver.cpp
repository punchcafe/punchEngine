#include "physicsResolver.h"

bool PhysicsResolver::isContact(int p [2] , int x_1, int x_2, int y_1, int y_2){
  //seperate
  //make this body.isContact(refferenceBody)? or keep static for memory
 bool result = (((x_1-1 <= p[0]) && (p[0] <= (x_2 +1)))&&(((y_1 - 1) <= p[1]) && (p[1] <= (y_2 + 1))));
 return result;
}
