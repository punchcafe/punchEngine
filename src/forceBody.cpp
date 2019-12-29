#include "forceBody.h"

ForceBody::ForceBody(){
  mass = 1;
  halfWidth = 50;
  halfHeight = 50;
}

ForceBody::BodyType ForceBody::getBodyType () {
  return bodyType;
}

void ForceBody::setBodyType (BodyType type) {
  this->bodyType = type;
}

int ForceBody::getXForceVector () {
  return this->forceVector[0];
}
int ForceBody::getYForceVector () {
  return this->forceVector[1];
}

void ForceBody::setForceVector (int newForceVector [2]) {
  this->forceVector[0] = newForceVector[0];
  this->forceVector[1] = newForceVector[1];
}

int ForceBody::getCollisionZone_x1 () {
  return get_sx()-getHalfWidth();
}
int ForceBody::getCollisionZone_x2 () {
  return get_sx()+getHalfWidth();
}

int ForceBody::getCollisionZone_y1 () {
  return get_sy()-getHalfHeight();
}

int ForceBody::getCollisionZone_y2 () {
  return get_sy()+getHalfHeight();
}

void ForceBody::setHalfWidth(int halfWidth){
  this->halfWidth = halfWidth;
}

int ForceBody::getHalfWidth(){
  return halfWidth;
}
void ForceBody::setHalfHeight(int halfHeight){
  this->halfHeight = halfHeight;
}
int ForceBody::getHalfHeight(){
  return halfHeight;
}
void ForceBody::set_sx(int x) {
  displacement[0] = x;
}
void ForceBody::set_sy(int y) {
  displacement[1] = y;
}
void ForceBody::set_vx(int x) {
  velocity[0] = x;
}
void ForceBody::set_vy(int y) {
  velocity[1] = y;
}
int ForceBody::get_sx() {
  return displacement[0];
}
int ForceBody::get_sy() {
  return displacement[1];
}
int ForceBody::get_vx() {
  return velocity[0];
}
int ForceBody::get_vy() {
  return velocity[1];
}
int ForceBody::getMass() {
  return mass;
}
