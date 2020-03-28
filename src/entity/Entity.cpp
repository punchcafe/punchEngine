#ifndef entity_def
#define entity_def
// naming this entity breaks use of local variables called entity
class Entity {
  // In future make this an abstract class so people can implement as they please;
  // Is decoupled from position, so may re-use instances for recurring characters
  private:
    int mass;
    int height;
    int width;
  public:
    Entity(int mass, int height, int width){
      this->mass = mass;
      this->height = height;
      this->width = width;
    }

    int getMass(){
      return mass;
    }
    int getHeight(){
      return height;
    }
    int getWidth(){
      return width;
    }
};
#endif
