
#include <Arduboy2.h>

#include "src/solidBody.h"
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
SolidBody dude;
SolidBody* refDude = &dude;
SolidBody inanimate;
SolidBody* inanimateRef = &inanimate;
SolidBody third;
SolidBody* thirdRef = &third;
ForceBody wrappedDude(refDude);
ForceBody wrappedRock(inanimateRef);
ForceBody wrappedThird(thirdRef);
PhysicsResolver resolver;
ForceBody* reflectDude = &wrappedDude;
  ForceBody* reflectRock = &wrappedRock;
  ForceBody* reflectThird = &wrappedThird;
  ForceField loadMe;

// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  loadMe.setForceBody(0, reflectDude);
  loadMe.setForceBody(1, reflectThird);
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(30);
  dude.set_sx(50);
  dude.set_sy(floor_y*1);
  inanimate.set_sx(115);
  inanimate.set_sy(15);
  third.set_sx(15);
  third.set_sy(45);
  floor_y = 50;
  s_x = 50;
  s_y = floor_y*1;
  t=1;
}




// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame




  loadMe.addGravity();
  loadMe.resolveColissions();

  if (!(arduboy.nextFrame()))
    return;

  if(arduboy.pressed(B_BUTTON)){
    if((dude.get_vy() == 0 && dude.get_sy()>=50)||
      (dude.get_vy() == 0)&&(thing.isColliding(reflectDude, reflectThird))){
      dude.set_vy(4);
      }
  }

  if((dude.get_sy() - dude.get_vy()) > floor_y){
    dude.set_sy(floor_y);
    dude.set_vy(0);
  } else if (thing.isColliding(reflectDude, reflectThird)){
    if(dude.get_vy() < 0)  dude.set_vy(0);
    dude.set_sy(dude.get_sy() - dude.get_vy()*t);
    }else {
    dude.set_sy(dude.get_sy() - dude.get_vy()*t);
    dude.set_vy(dude.get_vy() -1);
  }


  dude.set_vx(0);
  if(arduboy.pressed(LEFT_BUTTON)){
    dude.set_vx(2);
  } else if (arduboy.pressed(RIGHT_BUTTON)){
    dude.set_vx(-2);
  }
  dude.set_sx(dude.get_sx() - dude.get_vx()*t);



  // first we clear our screen to black
  arduboy.clear();
    arduboy.setCursor(15, 20);
  arduboy.print(F("Punch Cafe"));
    arduboy.setCursor(15, 30);
  arduboy.print(F("Physics Eng."));
    arduboy.setCursor(2, 52);
  arduboy.print(F("......................."));

  arduboy.setCursor(inanimate.get_sx(),inanimate.get_sy());
  arduboy.print("*");
    arduboy.setCursor(third.get_sx(),third.get_sy());
  arduboy.print("-");
//work out something to make this work
  int collisionZone [2][2];
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++){

      }
    }


  collisionZone[0][0] = wrappedDude.getCollisionZone_x1();
  collisionZone[0][1] = wrappedDude.getCollisionZone_x2();
  collisionZone[1][0] = wrappedDude.getCollisionZone_y1();
  collisionZone[1][1] = wrappedDude.getCollisionZone_y2();

    for(int i = 0; i < 2; i++){
      arduboy.setCursor(collisionZone[0][i], wrappedDude.getBody()->get_sy());
      arduboy.print(F("|"));
    };

        for(int j = 0; j < 2; j++){
      arduboy.setCursor(wrappedDude.getBody()->get_sx(), collisionZone[1][j]);
      arduboy.print(F("-"));
      };


  arduboy.setCursor(loadMe.getForceBody(0)->getBody()->get_sx(), loadMe.getForceBody(0)->getBody()->get_sy());
  arduboy.print(F("Q"));
  arduboy.setCursor(110,50);
  arduboy.print(loadMe.getForceBody(0)->getYForceVector());
  int displacement [2] = {wrappedDude.getBody()->get_sx(), wrappedDude.getBody()->get_sy()};
  //if(resolver.isContact(displacement, wrappedRock.getCollisionZone_x1(), wrappedRock.getCollisionZone_x2(), wrappedRock.getCollisionZone_y1(), wrappedRock.getCollisionZone_y2())){






  if(thing.isColliding(reflectDude,reflectRock)){
    arduboy.clear();
    arduboy.setCursor(15, 15);
  arduboy.print(F("Congrats!"));
  arduboy.setCursor(15, 30);
  arduboy.print(wrappedRock.getCollisionZone_x1());
  arduboy.print(wrappedRock.getCollisionZone_x2());
  arduboy.setCursor(15, 40);
  arduboy.print(wrappedRock.getCollisionZone_y1());
  arduboy.print(wrappedRock.getCollisionZone_y2());
  arduboy.setCursor(15, 50);
  arduboy.print(displacement[0]);
  arduboy.print(displacement[1]);
  }



  Sprites::drawOverwrite(90, 20, punchLogo, 0);

  arduboy.display();
}
