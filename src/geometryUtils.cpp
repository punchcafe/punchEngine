class GeometryUtils{
public:
static bool isBetweenInclusive(int value, int upperBound, int lowerBound){
  return value >= upperBound && value <= lowerBound;
}

static bool isBetweenExclusive(int value, int upperBound, int lowerBound){
  return value > upperBound && value < lowerBound;
}

static bool surroundsPoints(int surround_1, int surround_2, int passive_1, int passive_2){
  int lowerSurround;
  int upperSurround;
  int lowerPassive;
  int upperPassive;

  if(surround_1 > surround_2){
    upperSurround = surround_1;
    lowerSurround = surround_2;
  } else {
    upperSurround = surround_2;
    lowerSurround = surround_1;
  }

  if(passive_1 > passive_2){
    upperPassive = passive_1;
    lowerPassive = passive_2;
  } else {
    upperPassive = passive_2;
    lowerPassive = passive_1;
  }

  if(upperSurround > upperPassive && lowerSurround < lowerPassive){
    return true;
  }
  return false;
}
};
