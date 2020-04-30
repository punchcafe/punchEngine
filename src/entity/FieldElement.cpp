#ifndef field_element
#define field_element
#include "Entity.cpp"

class FieldElement {
  private:
    Entity* entity;
    int x;
    int y;
    int z;

  public:
    FieldElement(){}

    FieldElement(Entity * entity, int x, int y){
      this->entity = entity;
      this->x = x;
      this->y = y;
    }

    int getHeight(){
      return this->entity->getHeight();
    }
    int getWidth(){
      return this->entity->getWidth();
    }
    int getMass(){
      return this->entity->getMass();
    }
    int getX(){
      return this->x;
    }
    int getY(){
      return this->y;
    }
    int getZ(){
      return this->z;
    }
    void setX(int x){
      this->x = x;
    }
    void setY(int y){
      this->y = y;
    }
    void setZ(int z){
      this->z = z;
    }
};

#endif
