#ifndef solidBody_h
#define solidBody_h

#include <Arduboy2.h>

class SolidBody {
    int halfWidth;
    int displacement [2];
    int velocity [2];
    int mass;
   public:
    SolidBody();
    void setHalfWidth(int halfWidth);
    int getHalfWidth();
    void set_sx(int x);
    void set_sy(int y);
    void set_vx(int x);
    void set_vy(int y);
    int get_sx();
    int get_sy();
    int get_vx();
    int get_vy();
    int getMass();
 };

#endif
