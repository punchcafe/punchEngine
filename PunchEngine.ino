
#include <Arduboy2.h>
#include "src/entity/Entity.cpp"
#include "src/entity/EntityField.cpp"
#include "src/dynamics_module/AstralBodyDynamics.cpp"
#include "src/GameContainer.cpp"

EntityField* field = new EntityField(2);
Entity* hero = new Entity(1, 20, 20);
Entity* villain = new Entity(1, 30, 30);

LinkedList<Entity> trialList;

int nonBrokenCounter;

Arduboy2 arduboy;
GameContainer::Builder* gameBuilder = GameContainer::builder(&arduboy);
GameContainer* gameContainer;

void setup() {
  Serial.begin(9600);
  gameContainer = gameBuilder->setEntityField(field)->useAstralBodyPhysics()->build();
  field->registerEntity(hero, 50,20);
  field->registerEntity(villain, 70,20);
  trialList.append(hero);
  trialList.append(villain);
  arduboy.begin();
}

void loop() {

  arduboy.clear();

  nonBrokenCounter = nonBrokenCounter > 100 ? 0 : nonBrokenCounter + 1;

  gameContainer->update(0);
  
  int herox = field->getEntity(0).getX();
  int heroy = field->getEntity(0).getY();

  int villainx = field->getEntity(1).getX();
  int villainy = field->getEntity(1).getY();
  
  arduboy.setCursor(herox,heroy);
  arduboy.print(F("H"));
  arduboy.setCursor(villainx,villainy);
  arduboy.print(F("Vill"));
  
  
    arduboy.setCursor(40,30);
  arduboy.print(nonBrokenCounter);
  arduboy.display();
}
