#ifndef forceBody_h
#define forceBody_h

#include "solidBody.h"

class ForceBody {
  SolidBody* body;
  int forceVector [2];
  public:
    ForceBody(SolidBody* solidBody);
    SolidBody* getBody();
    int getXForceVector ();
    int getYForceVector ();
    void setForceVector (int newForceVector [2]);
    int getCollisionZone_x1 ();
    int getCollisionZone_x2 ();
    int getCollisionZone_y1 ();
    int getCollisionZone_y2 ();
};
#endif
