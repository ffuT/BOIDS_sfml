#pragma once
#include <math.h>

class vect{

public:
  vect(float, float);
  vect();
  ~vect();

  float mag();
  float length() {return mag();};

  vect operator+(const vect);
  vect& operator+=(const vect);
  vect operator-(const vect);
  float operator*(const vect);  //dot product
  vect operator*(const float);  //scale
  vect operator/(const float);  //scale
  bool operator==(vect);
  void normalize();
  void rotate(float);
  
  static vect normalized(const vect&);

  float x, y;
};

