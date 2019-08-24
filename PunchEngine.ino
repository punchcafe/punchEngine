/*
Hello, World! example
June 11, 2015
Copyright (C) 2015 David Martinez
All rights reserved.
This code is the most basic barebones code for writing a program for Arduboy.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
*/

#include <Arduboy2.h>

#include "src/solidBody.h"

const unsigned char PROGMEM punchLogo[] =
{
// width, height,
16, 16,
0x00, 0x00, 0xfc, 0x6c, 0x4c, 0x6c, 0x3c, 0x00, 0x00, 0x3c, 0x2c, 0x4c, 0x4c, 0xfc, 0xf8, 0x00,
0x00, 0x10, 0x3f, 0x00, 0x00, 0x07, 0x1f, 0x1d, 0x1d, 0x17, 0x17, 0x03, 0x60, 0x3f, 0x1f, 0x00,
};

class ForceBody {
  SolidBody* body;
  int forceVector [2];
  //lets make this refferences
  //space over which would count as collision. dont forget to edge out corners.

  public:
    ForceBody(SolidBody* solidBody){
    body = solidBody;
  }
    SolidBody* getBody() {
      return body;
    }
    int getXForceVector () {
      return forceVector[0];
    };
    int getYForceVector () {
      return forceVector [1];
    }
    void setForceVector (int newForceVector [2]) {
      forceVector[0] = newForceVector[0];
      forceVector[1] = newForceVector[1];
    };
    //use this to determine area, use same functionality
    int getCollisionZone_x1 () {
      return body->get_sx()-body->getHalfWidth();
    }
    int getCollisionZone_x2 () {
      return body->get_sx()+body->getHalfWidth();
    }

    int getCollisionZone_y1 () {
      return body->get_sy()-body->getHalfWidth();
    }

    int getCollisionZone_y2 () {
      return body->get_sy()+body->getHalfWidth();
    }
};

class PhysicsResolvers {
  public:
  bool isContact(int p [2] , int x_1, int x_2, int y_1, int y_2){
    //seperate
    //make this body.isContact(refferenceBody)? or keep static for memory
   bool result = (((x_1-1 <= p[0]) && (p[0] <= (x_2 +1)))&&(((y_1 - 1) <= p[1]) && (p[1] <= (y_2 + 1))));
  return result;
  }
};

 class ForceField {
  int gConstant = 10;
  ForceBody* bodies [10]{0};
  PhysicsResolvers physicsResolver;
  //ForceResolver->
  //AccelerationResolver->based on force bodies
  //VelocityAppender

  //max number of bodies in a frame
  //temporary fieldMapSoln, checks for 2
  //initially until i work out how to get fuckin vectors
  public:
    ForceField() {
      };
      //MAKE SPECIAL FORCEBODY, 0th index?
    ForceBody* getForceBody(int index) {
      return bodies[index];
    }
    void setForceBody(int index, ForceBody* forceBody) {
      bodies[index] = forceBody;
    }

//parent in resolveForces

    void addGravity(){
      for(int i = 0; i < sizeof(bodies); i++){
        if(bodies[i] != 0){
          int forceVector [2] = {bodies[i]->getXForceVector(), bodies[i]->getBody()->getMass()*gConstant};
          bodies[i]->setForceVector(forceVector);
        }
      }
    }

    void resolveColissions(){
      for(int i = 0; i < sizeof(bodies); i++){
        if(bodies[i] != 0){
          for(int j = 0; j < sizeof(bodies); j++){
            if(j != i && bodies[j] != 0){
              if(isColliding(bodies[i],bodies[j])){
                int forceVector [2] = {bodies[i]->getXForceVector(), 0};
                bodies[i]->setForceVector(forceVector);
              }
            }
          }
        }
      }
    }

    //void resolveVelocities
    //for(i in bodies){ bodies[i]->getBody()->setVelocity(velocity + (force/mass)*UNIT_TIME) }

    //void resolveDisplacements
    //s = s + v*t

    bool isColliding(ForceBody* body, ForceBody* otherBody){
      //only works for squares
      bool result = false;
      ForceBody* smallerBody = body->getBody()->getHalfWidth() > otherBody->getBody()->getHalfWidth() ?
                                body : otherBody;
      ForceBody* biggerBody = body->getBody()->getHalfWidth() > otherBody->getBody()->getHalfWidth() ?
                                otherBody : body;
      int smallerBodyCorners[4][2] = {
        {
          smallerBody->getBody()->get_sx()+smallerBody->getBody()->getHalfWidth(),
          smallerBody->getBody()->get_sy()-smallerBody->getBody()->getHalfWidth()
        },
        {
          smallerBody->getBody()->get_sx()+smallerBody->getBody()->getHalfWidth(),
          smallerBody->getBody()->get_sy()+smallerBody->getBody()->getHalfWidth()
        },
        {
          smallerBody->getBody()->get_sx()-smallerBody->getBody()->getHalfWidth(),
          smallerBody->getBody()->get_sy()+smallerBody->getBody()->getHalfWidth()
          },
        {
          smallerBody->getBody()->get_sx()-smallerBody->getBody()->getHalfWidth(),
          smallerBody->getBody()->get_sy()-smallerBody->getBody()->getHalfWidth()
        }
      };
//change it to halflength half height
      for(int i = 0; i<4; i++){
        result = result || physicsResolver.isContact(
          smallerBodyCorners[i],
          biggerBody->getBody()->get_sx()-biggerBody->getBody()->getHalfWidth(),
          biggerBody->getBody()->get_sx()+biggerBody->getBody()->getHalfWidth(),
          biggerBody->getBody()->get_sy()-biggerBody->getBody()->getHalfWidth(),
          biggerBody->getBody()->get_sy()+biggerBody->getBody()->getHalfWidth()
          );
      }

      return result;
    }
    //int forceVector resolveCollision(ForceBody body){return 0;};
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
PhysicsResolvers resolver;
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
