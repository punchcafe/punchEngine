
#include <Arduboy2.h>
#include "src/entity/Entity.cpp"
#include "src/entity/EntityField.cpp"

EntityField* field = new EntityField(2);
Entity* hero = new Entity(1, 20, 20);
Entity* villain = new Entity(1, 30, 30);
bool result;
Arduboy2 arduboy;

// make an instance of arduboy used for many functions



// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  result = field->registerEntity(*hero, 50,20);
  result = field->registerEntity(*villain, 70,20);
  arduboy.begin();
}




// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  if (!(arduboy.nextFrame()))
    return;
  arduboy.clear();
  
  if(arduboy.pressed(LEFT_BUTTON)){
    field->moveEntity(0, -1, 0);
  } else if (arduboy.pressed(RIGHT_BUTTON)){
    field->moveEntity(0, 1, 0);
  } else if (arduboy.pressed(UP_BUTTON)){
    field->moveEntity(0, 0, -1);
  } else if (arduboy.pressed(DOWN_BUTTON)){
    field->moveEntity(0, 0, 1);
  }
  
  int herox = field->getEntity(0).getX();
  int heroy = field->getEntity(0).getY();

  int villainx = field->getEntity(1).getX();
  int villainy = field->getEntity(1).getY();
  
  arduboy.setCursor(herox,heroy);
  arduboy.print(F("H"));
  arduboy.setCursor(villainx,villainy);
  arduboy.print(F("V"));
  arduboy.display();
}
