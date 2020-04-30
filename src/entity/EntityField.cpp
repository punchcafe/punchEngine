#ifndef entity_field_h
#define entity_field_h


#include "EntityObserver.cpp"
#include "FieldElement.cpp"
#include "Entity.cpp"
#include "../utils/LinkedList.cpp"

// TODO: find out what happens when you need to acces forward referrenced member
// methods
// This is why .h files are the best! we can forward ref without worrying about
// class, then let the .cpp files do the rest while everthing has been included

// TODO: rename CartesianEntityField
// TODO: separate space system from Field, have cartesian + angles

class EntityField {
  private:
    LinkedList<EntityObserver> observers;
    // Referrences an array
    FieldElement* entities;
    int numberOfEntities;
    int fieldSize;
  public:
    EntityField(int fieldSize){
      this->fieldSize = fieldSize;
      entities = new FieldElement [fieldSize];
      this->numberOfEntities = 0;
    }

    void registerObserver(EntityObserver* observer){
      this->observers.append(observer);
    }

    int getNumberOfEntities(){
      return this->numberOfEntities;
    }

    bool registerEntity(Entity * entity, int x, int y){
      if(numberOfEntities == fieldSize){
        return false;
      }
      // TODO: refactor! this is doubling up!
      FieldElement* element = new FieldElement(entity, x, y);
      this->entities[numberOfEntities] = *element;
      // Check this doesn't break stuff!
      //delete element;
      this->numberOfEntities++;

      for(int i = 0; i < observers.getSize(); i++){
        observers.get(i)->respondToNewFieldElement(this->numberOfEntities -1);
      }
      return true;
    }

    bool removeEntity(int index){
      return false;
    }

    bool moveEntity(int index, int xShift, int yShift){
      if(index < 0 || index >= this->numberOfEntities){
        return false;
      }
      int currentX = this->entities[index].getX();
      int currentY = this->entities[index].getY();
      this->entities[index].setX(currentX + xShift);
      this->entities[index].setY(currentY + yShift);
      return true;
    }

    FieldElement* getEntity(int index){
      // TODO: Handle negative indexes
      if(index >= numberOfEntities){
        // TODO: sort this out
        return &this->entities[numberOfEntities-1];
      }
      return &this->entities[index];
    }
};
#endif
