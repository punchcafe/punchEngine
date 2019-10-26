#ifndef fieldPrinter_h
#define fieldPrinter_h

#include "forceField.h"
#include "forceBody.h"

#include <Arduboy2.h>


class FieldPrinter {
  int pixelRatio = 10;
  ForceField forceField;
  //add special forceField method; forceField.getHero();
  public:
    void printBodies;
  private:
    void printBody;
    void printHero;
};
#endif
