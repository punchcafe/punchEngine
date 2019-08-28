
#include <Arduboy2.h>

#include "src/forceBody.h"
#include "src/physicsResolver.h"
#include "src/forceField.h"

const unsigned char PROGMEM punchLogo[] =
{
// width, height,
16, 16,
0x00, 0x00, 0xfc, 0x6c, 0x4c, 0x6c, 0x3c, 0x00, 0x00, 0x3c, 0x2c, 0x4c, 0x4c, 0xfc, 0xf8, 0x00,
0x00, 0x10, 0x3f, 0x00, 0x00, 0x07, 0x1f, 0x1d, 0x1d, 0x17, 0x17, 0x03, 0x60, 0x3f, 0x1f, 0x00,
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
PhysicsResolver resolver;
ForceBody* reflectDude = &wrappedDude;
  ForceBody* reflectRock = &wrappedRock;
  ForceBody* reflectThird = &wrappedThird;
  ForceField loadMe;

int breakChecker;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  breakChecker = 0;
  loadMe.setForceBody(0, reflectDude);
  loadMe.setForceBody(1, reflectThird);
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(30);
  wrappedDude.set_sx(50);
  wrappedDude.set_sy(floor_y*1);
  wrappedRock.set_sx(115);
  wrappedRock.set_sy(15);
  wrappedThird.set_sx(15);
  wrappedThird.set_sy(45);
  floor_y = 50;
  s_x = 50;
  s_y = floor_y*1;
  t=1;
}




// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
breakChecker = breakChecker == 100 ? 0 : breakChecker+1;
  if (!(arduboy.nextFrame()))
    return;
reflectDude->set_vx(0);
wrappedDude.set_vy(0);
  wrappedThird.set_vx(0);
  wrappedThird.set_vy(0);
  loadMe.addGravity();
  loadMe.resolveVelocities();
  loadMe.resolveColissions();
  
  //resolving vel

  
  if(arduboy.pressed(LEFT_BUTTON)){
    wrappedDude.set_vx(2);
  } else if (arduboy.pressed(RIGHT_BUTTON)){
    wrappedDude.set_vx(-2);
  }

  if(arduboy.pressed(B_BUTTON)){
    if((wrappedDude.get_vy() == 0 && wrappedDude.get_sy()>=50)||
      (wrappedDude.get_vy() == 0)&&(thing.isColliding(reflectDude, reflectThird))){
      wrappedDude.set_vy(4);
      }
  }

  if((wrappedDude.get_sy() - wrappedDude.get_vy()) > floor_y){
    wrappedDude.set_sy(floor_y);
    wrappedDude.set_vy(0);
  }


  



  // first we clear our screen to black
  arduboy.clear();
    arduboy.setCursor(15, 20);
  arduboy.print(F("Punch Cafe"));
    arduboy.setCursor(15, 30);
  arduboy.print(F("Physics Eng."));
    arduboy.setCursor(2, 50);
  arduboy.print(F("......................."));

  arduboy.setCursor(wrappedRock.get_sx(),wrappedRock.get_sy());
  arduboy.print("*");
    arduboy.setCursor(wrappedThird.get_sx(),wrappedThird.get_sy());
  arduboy.print("-");
//work out something to make this work
  

int collisionZone [2][2];
  collisionZone[0][0] = wrappedDude.getCollisionZone_x1();
  collisionZone[0][1] = wrappedDude.getCollisionZone_x2();
  collisionZone[1][0] = wrappedDude.getCollisionZone_y1();
  collisionZone[1][1] = wrappedDude.getCollisionZone_y2();

    for(int i = 0; i < 2; i++){
      arduboy.setCursor(collisionZone[0][i], wrappedDude.get_sy());
      arduboy.print(F("|"));
    };

        for(int j = 0; j < 2; j++){
      arduboy.setCursor(wrappedDude.get_sx(), collisionZone[1][j]);
      arduboy.print(F("-"));
      };

 
arduboy.setCursor(110, 10);
arduboy.print(breakChecker);
  arduboy.setCursor(loadMe.getForceBody(0)->get_sx(), loadMe.getForceBody(0)->get_sy());
  arduboy.print(F("Q"));
  arduboy.setCursor(110,50);
  arduboy.print(loadMe.getForceBody(0)->getYForceVector());

  Sprites::drawOverwrite(90, 20, punchLogo, 0);

  arduboy.display();
}
