/*
If injected, all entities will have simple top down cbehaviour.
Entities with greater than 0 mass will collide, preventing movement.
*/
#include "DynamicsModule.cpp"
class TopDownDynamics : public DynamicsModule{

};
