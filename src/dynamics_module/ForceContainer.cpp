#ifndef force_container_h
#define force_container_h

#include "../entity/FieldElement.cpp"

class ForceContainer {
private:
  FieldElement * element;
  float forcesArray [3] = {0, 0, 0};
  float velocitiesArray [3] = {0, 0, 0};
public:
  ForceContainer(FieldElement* elementPointer){
    this->element = elementPointer;
  }
  int getMass(){
    return this->element->getMass();
  }
  void setX(float x){
    this->forcesArray[0] = x;
  }
  void setY(float y){
    this->forcesArray[1] = y;
  }
  void setZ(float z){
    this->forcesArray[2] = z;
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
  void setVX(float x){
    this->velocitiesArray[0] = x;
  }
  void setVY(float y){
    this->velocitiesArray[1] = y;
  }
  void setVZ(float z){
    this->velocitiesArray[2] = z;
  }
  float getVX(){
    return this->velocitiesArray[0];
  }
  float getVY(){
    return this->velocitiesArray[1];
  }
  float getVZ(){
    return this->velocitiesArray[2];
  }
  FieldElement * getFieldElement(){
    return this->element;
  }
};

#endif
