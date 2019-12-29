#include "forceBody.h"
#include "Math.h"
#include "physicsResolver.h"
class Box{
  int x_1;
  int x_2;
  int y_1;
  int y_2;

public:

  setBox(int x1, int x2, int y1, int y2){
    x_1 = x1;
    x_2 = x2;
    y_1 = y1;
    y_2 = y2;
  }

  bool collidesWith(Box box, PhysicsResolver* resolver){
    int points [4][2] = {{x_1,y_1},{x_2,y_1},{x_1,y_2},{x_2,y_2}};
    bool outcome = false;
    for(int i = 0; i < 4; i++){
      outcome = resolver->isContact(points[i], box.getX1(), box.getX2(), box.getY1(), box.getY2());
    }
  }

  int getX1(){
    return x_1;
  }

  int getX2(){
    return x_2;
  }

  int getY1(){
    return y_1;
  }

  int getY2(){
    return y_2;
  }
};

class Path{
  public:
    int internalPath[4][2];

    int size(){
      return 4;
    }

    void setXAt(int x, int index){
      internalPath[index][0] = x;
    }

    void setYAt(int y, int index){
      internalPath[index][1] = y;
    }

    int getXAt(int index){
      return internalPath[index][0];
    }

    int getYAt(int index){
      return internalPath[index][1];
    }
};

class BodyVectorPath{

public:
  ForceBody* body;
  PhysicsResolver* physicsResolver;
  Path path;
  Box box;
  int time;

  BodyVectorPath(){
  }

  int size(){
    return this->path.size();
  }

  bool collidesWith(BodyVectorPath otherPath){
    for(int i = 0; i < size(); i++){
      for(int j = 0; j < otherPath.size(); j++){
        if(this->getBoxAt(i).collidesWith(otherPath.getBoxAt(j), physicsResolver)){
          return true;
        };
      }
    }
    return false;
  }

  Box getBoxAt(int index){
    box.setBox(
      path.getXAt(index)+body->getHalfWidth(),
      path.getXAt(index)-body->getHalfWidth(),
      path.getYAt(index)+body->getHalfWidth(),
      path.getYAt(index)-body->getHalfWidth()
    );
    return box;
  }

  void wrapBody(ForceBody* forceBody){
    //re-uses Object
    this->body = forceBody;
    double timeIncrement = this->time/this->path.size();
    this->path.setXAt(0, body->get_sx()*1);
    this->path.setYAt(0, body->get_sy()*1);
    // for(int i = 1; i < this->path.size(); i++){
    //   this->path.setXAt(i, (this->path.getXAt(i-1)+body->get_vx()*timeIncrement));
    //   this->path.setYAt(i, (this->path.getYAt(i-1)+body->get_vy()*timeIncrement));
    // }
  }
};
