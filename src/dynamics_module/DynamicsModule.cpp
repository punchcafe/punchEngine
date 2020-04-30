#ifndef dynamics_module_h
#define dynamics_module_h
#include "../entity/EntityObserver.cpp"

/*
An abstract class which defines physics behaviour of entities
in an EntityField, and updates them. Allows for separation of physics
from entities, so that differnt behvaiours, i.e. zelda-esque physics,
mario esque physics, or underwater style physics may be injected.
*/
class DynamicsModule : public EntityObserver {
public:
  /*
  Drive entities in the entity field according to the physics type
  */
  virtual void resolveInterval(float interval);
};

#endif
