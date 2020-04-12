
#include <Arduboy2.h>
#include "src/entity/Entity.cpp"
#include "src/entity/EntityField.cpp"
#include "src/dynamics_module/TopDownDynamics.cpp"
#include "src/GameContainer.cpp"

EntityField* field = new EntityField(2);
Entity* hero = new Entity(1, 20, 20);
Entity* villain = new Entity(1, 30, 30);

Arduboy2 arduboy;
Arduboy2* arduboyPointer = &arduboy;

GameContainer::Builder* gameBuilder = GameContainer::builder(arduboyPointer);
GameContainer* gameContainer;

void setup() {
  field->registerEntity(*hero, 50,20);
  field->registerEntity(*villain, 70,20);
  gameContainer = gameBuilder->useTopDownPhysics()->setEntityField(field)->build();
  arduboy.begin();
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;
  arduboy.clear();

  gameContainer->update(0);
  
  int herox = field->getEntity(0).getX();
  int heroy = field->getEntity(0).getY();

  int villainx = field->getEntity(1).getX();
  int villainy = field->getEntity(1).getY();
  
  arduboy.setCursor(herox,heroy);
  arduboy.print(F("H"));
  arduboy.setCursor(villainx,villainy);
  arduboy.print(F("Vil"));
  arduboy.display();
}
