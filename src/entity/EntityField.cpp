#ifndef entity_field_h
#define entity_field_h

#include "EntityObserver.cpp"
#include "FieldElement.cpp"
#include "Entity.cpp"
#include "../utils/LinkedList.cpp"

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

    int getNumberOfEntities(){
      return this->numberOfEntities;
    }

    bool registerEntity(Entity entity, int x, int y){
      if(numberOfEntities == fieldSize){
        return false;
      }
      FieldElement* element = new FieldElement(entity, x, y);
      this->entities[numberOfEntities] = *element;
      // Check this doesn't break stuff!
      //delete element;
      this->numberOfEntities++;
      for(int i = 0; i < observers.size(); i++){
        observers.get(i).respondToNewFieldElement(element);
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

    FieldElement getEntity(int index){
      // TODO: Handle negative indexes
      if(index >= numberOfEntities){
        // TODO: sort this out
        return this->entities[numberOfEntities];
      }
      return this->entities[index];
    }
};
#endif
