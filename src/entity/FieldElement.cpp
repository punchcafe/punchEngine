#include "Entity.cpp"
#ifndef field_element
#define field_element

class FieldElement {
  private:
    int x;
    // For some reason calling this entity breaks everything
    Entity* entity;
    int y;
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
