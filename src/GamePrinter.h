#ifndef gamePrinter_h
#define gamePrinter_h

#include "forceField.h"
#include "forceBody.h"

#include <Arduboy2.h>


class GamePrinter {
  int pixelRatio = 10;
  ForceField forceField;
  Arduboy2 arduboy;

  //add special forceField method; forceField.getHero();
  public:
    void printBodies;
    //Loop through FB, checking sprite against. can re-use sprite refferences
  private:
    void printBody;
    void printHero;
};
#endif
