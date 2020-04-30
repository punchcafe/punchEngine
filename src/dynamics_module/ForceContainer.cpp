#ifndef force_container_h
#define force_container_h

#include "../entity/FieldElement.cpp"

class ForceContainer {
private:
  FieldElement * element;
  float forcesArray [3] = {0, 0, 0};
public:
  ForceContainer(FieldElement* elementPointer){
    this->element = elementPointer;
  }
  void setX(float x){
    this->forcesArray[0] = x;
  }
  void setY(float y){
    this->forcesArray[1] = y;
  }
  void setZ(float x){
    this->forcesArray[2];
  }
  float getX(){
    return this->forcesArray[0];
  }
  float getY(){
    return this->forcesArray[1];
  }
  float getZ(){
    return this->forcesArray[2];
  }
  FieldElement * getFieldElement(){
    return this->element;
  }
};

#endif
