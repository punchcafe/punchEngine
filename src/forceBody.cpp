#include "forceBody.h"
#include "solidBody.h"

ForceBody::ForceBody(SolidBody* solidBody){
  body = solidBody;
}

SolidBody* ForceBody::getBody() {
  return body;
}
int ForceBody::getXForceVector () {
  return forceVector[0];
}
int ForceBody::getYForceVector () {
  return forceVector [1];
}

void ForceBody::setForceVector (int newForceVector [2]) {
  forceVector[0] = newForceVector[0];
  forceVector[1] = newForceVector[1];
}

int ForceBody::getCollisionZone_x1 () {
  return body->get_sx()-body->getHalfWidth();
}
int ForceBody::getCollisionZone_x2 () {
  return body->get_sx()+body->getHalfWidth();
}

int ForceBody::getCollisionZone_y1 () {
  return body->get_sy()-body->getHalfWidth();
}

int ForceBody::getCollisionZone_y2 () {
  return body->get_sy()+body->getHalfWidth();
}
