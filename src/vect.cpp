#include "../headers/vect.hpp"

vect::vect() {
  this->x = 0;
  this->y = 0;
}

vect::vect(float x, float y) {
  this->x = x;
  this->y = y;
}

vect::~vect() {};

vect vect::operator+(vect other) {
  return vect(x + other.x, y + other.y);
}
vect& vect::operator+=(vect other) {
  this->x += other.x;
  this->y += other.y;
  this->y += other.y;
  return *this;
}
vect vect::operator-(vect other) {
  return vect(x - other.x, y - other.y);
}
bool vect::operator==(vect other) {
  return (x == other.x && y == other.y);
}
float vect::operator*(vect other) {
  return x * other.x + y * other.y;
}
vect vect::operator*(float scale) {
  return vect(x * scale, y * scale);
}
vect vect::operator/(float scale) {
  return vect(x / scale, y / scale);
}

float vect::mag() {
  return sqrt(x * x + y * y);
}

void vect::rotate(float angle) {
  x =  x * cos(angle) + y * -sin(angle);
  y = x * sin(angle) + y * cos(angle);
}

void vect::normalize() {
  float mag = sqrt(x * x + y * y);
  x = x / mag;
  y = y / mag;
}

vect vect::normalized(const vect& in) {
  float mag = sqrt(in.x * in.x + in.y * in.y);
  return vect(in.x / mag,in.y / mag);
}