#ifndef forceBody_h
#define forceBody_h

class ForceBody {
  public:
    enum BodyType{
      DYNAMIC,
      PLATFORM,
      INTANGIBLE
    };
  private:

  BodyType bodyType;
  long int forceVector [2];
  int halfWidth;
  int halfHeight;
  long int displacement [2];
  int velocity [2] = {0,0};
  int mass;
  public:
    ForceBody();
    BodyType getBodyType();
    void setHalfWidth(int halfWidth);
    int getHalfWidth();
    void setHalfHeight(int halfHeight);
    int getHalfHeight();
    void set_sx(int x);
    void set_sy(int y);
    void set_vx(int x);
    void set_vy(int y);
    int get_sx();
    int get_sy();
    int get_vx();
    int get_vy();
    int getMass();
    int getXForceVector ();
    int getYForceVector ();
    void setForceVector (int newForceVector [2]);
    int getCollisionZone_x1 ();
    int getCollisionZone_x2 ();
    int getCollisionZone_y1 ();
    int getCollisionZone_y2 ();
};
#endif
