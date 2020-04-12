#include "dynamics_module/TopDownDynamics.cpp"
//TODO: use abstract factory pattern
class GameContainer {

private:
  EntityField* entityField;
  DynamicsModule* dynamicsModule;

  GameContainer(EntityField* entityField, DynamicsModule* dynamicsModule){
    // TODO: add registration here
    this->entityField = entityField;
    this->dynamicsModule = dynamicsModule;
  }

public:

  class Builder {
  private:
    Arduboy2* arduboy;
    EntityField* entityField;
    DynamicsModule* dynamicsModule;
  public:
    Builder(Arduboy2* arduboy){
      this->arduboy = arduboy;
    }

    Builder* useTopDownPhysics(){
      this->dynamicsModule = new TopDownDynamics(this->arduboy, this->entityField);
      return this;
    }

    Builder* setEntityField(EntityField* entityField){
      this->entityField = entityField;
      return this;
    }

    GameContainer* build(){
      return new GameContainer(this->entityField, this->dynamicsModule);
    }

  };

  static GameContainer::Builder* builder(Arduboy2* arduboy){
    return new GameContainer::Builder(arduboy);
  }

  void update(float frames){
    // TODO: make frames part of config?
    this->dynamicsModule->resolveInterval(frames);
  }

  // sprite manager
  // renderer

  // void render();
  // void updateFrame();


};
