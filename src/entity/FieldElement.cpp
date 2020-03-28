#ifndef field_element
#define field_element
#include "Entity.cpp"

class FieldElement {
  private:
    Entity* entity;
    int x;
    int y;
    // To be added later
    int z;

  public:
    FieldElement(){}

    FieldElement(Entity entity, int x, int y){
      this->entity = &entity;
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
    void setX(int x){
      this->x = x;
    }
    void setY(int y){
      this->y = y;
    }
};

#endif
