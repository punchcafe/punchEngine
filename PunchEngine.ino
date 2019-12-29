
#include <Arduboy2.h>

#include "src/forceBody.h"
#include "src/physicsResolver.h"
#include "src/forceField.h"
#include "src/geometryUtils.cpp"


const unsigned char PROGMEM punchLogo[] =
{
// width, height,
25, 23,
0x00, 0x00, 0x00, 0x00, 0xf8, 0x28, 0x28, 0x28, 0x28, 0x28, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x28, 0x28, 0x28, 0x28, 0x28, 0xf8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x01, 0x01, 0x79, 0x89, 0x88, 0x88, 0x88, 0x79, 0x49, 0x39, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00,
};


// make an instance of arduboy used for many functions
Arduboy2 arduboy;

int s_x;
int s_y;
int v_x;
int v_y;
int t;
int floor_y;



ForceField thing;
ForceBody wrappedDude;
ForceBody wrappedRock;
ForceBody wrappedThird;
ForceBody floorBlock;
PhysicsResolver resolver;
ForceBody* reflectDude = &wrappedDude;
  ForceBody* reflectRock = &wrappedRock;
  ForceBody* reflectThird = &wrappedThird;
  ForceBody* reflectFloor = &floorBlock;
  ForceField loadMe;

int breakChecker;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  breakChecker = 0;
  loadMe.setForceBody(0, reflectDude);
  loadMe.setForceBody(1, reflectThird);
  loadMe.setForceBody(2, reflectFloor);
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(120);
  floorBlock.set_sx(50);
  //floorBlock.setHalfWidth(600);
  //floorBlock.setHalfHeight(10);
  floorBlock.set_sy(110);
  wrappedDude.set_sx(50);
  wrappedDude.setHalfHeight(100);
  wrappedDude.set_sy(floor_y*1);
  wrappedRock.set_sx(1000);
  wrappedRock.set_sy(150);
  wrappedThird.set_sx(150);
  wrappedThird.set_sy(200);
  floor_y = 500;
  s_x = 500;
  s_y = floor_y*1;
  t=1;
}




// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
breakChecker = breakChecker == 100 ? 0 : breakChecker+1;
  //if (!(arduboy.nextFrame()))
  //  return;


///final look:
///gameContext.increment()
///gamePrinter.print() -- is handed the arduboy.



  loadMe.addGravity();
  loadMe.resolveUserInput(arduboy);
  // should make this a force
  loadMe.resolveColissions();
  loadMe.resolveVelocities();
  //make an interface to hand to this during building. resolveUser calls a method on that
  //define user 0
  loadMe.resolveDisplacements();


  //resolving vel






  // first we clear our screen to black
  arduboy.clear();
    arduboy.setCursor(15, 20);
  arduboy.print(F("Punch Cafe"));
    arduboy.setCursor(15, 30);
  arduboy.print(F("Physics Eng."));
    arduboy.setCursor(2, 50);
  arduboy.print(F("......................."));

  arduboy.setCursor(wrappedRock.get_sx()/10,wrappedRock.get_sy()/10);
  arduboy.print("*");
  arduboy.setCursor(wrappedThird.get_sx()/10,wrappedThird.get_sy()/10);
  arduboy.print("-");
//work out something to make this work


int collisionZone [2][2];
  collisionZone[0][0] = wrappedDude.getCollisionZone_x1();
  collisionZone[0][1] = wrappedDude.getCollisionZone_x2();
  collisionZone[1][0] = wrappedDude.getCollisionZone_y1();
  collisionZone[1][1] = wrappedDude.getCollisionZone_y2();

    for(int i = 0; i < 2; i++){
      arduboy.setCursor(collisionZone[0][i]/10, wrappedDude.get_sy()/10);
      arduboy.print(F("|"));
    };

        for(int j = 0; j < 2; j++){
      arduboy.setCursor(wrappedDude.get_sx()/10, collisionZone[1][j]/10);
      arduboy.print(F("-"));
      };


arduboy.setCursor(110, 10);
arduboy.print(breakChecker);
  arduboy.setCursor(loadMe.getHero()->get_sx()/10, loadMe.getHero()->get_sy()/10);
  arduboy.print(F("Q"));
  arduboy.setCursor(10,40);
  arduboy.print(loadMe.collisionCase(loadMe.getHero(), loadMe.getForceBody(1)));
  arduboy.setCursor(10,50);

  arduboy.print(loadMe.getHero()->getYForceVector());
arduboy.print("/");
  arduboy.print(loadMe.getHero()->get_vy());
arduboy.print("/");
  arduboy.print(loadMe.getHero()->get_sy());

  Sprites::drawOverwrite(90, 17, punchLogo, 0);

  arduboy.display();
}
