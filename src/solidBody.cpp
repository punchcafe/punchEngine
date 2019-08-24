#include "solidBody.h"

SolidBody::SolidBody(){
  mass = 1;
  halfWidth = 5;
}

void SolidBody::setHalfWidth(int halfWidth){
  this->halfWidth = halfWidth;
}

int SolidBody::getHalfWidth(){
  return halfWidth;
}
void SolidBody::set_sx(int x) {
  displacement[0] = x;
}
void SolidBody::set_sy(int y) {
  displacement[1] = y;
}
void SolidBody::set_vx(int x) {
  velocity[0] = x;
}
void SolidBody::set_vy(int y) {
  velocity[1] = y;
}
int SolidBody::get_sx() {
  return displacement[0];
}
int SolidBody::get_sy() {
  return displacement[1];
}
int SolidBody::get_vx() {
  return velocity[0];
}
int SolidBody::get_vy() {
  return velocity[1];
}
int SolidBody::getMass() {
  return mass;
}
