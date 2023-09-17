#include "../headers/Boid.hpp"

Boid::Boid(float x, float y, float x_, float y_, sf::Color inCol) {
  pos = vect(x,y);
  dir = vect(x_,y_);
  dir.normalize();
  col = inCol;
}

Boid::~Boid() {

}

Boid::Boid() {
  pos = vect(0, 0);
  dir = vect(0, 0);
}

bool Boid::operator==(Boid other) {
  return (pos == other.pos && dir == other.dir);
}

void Boid::draw(sf::RenderWindow* winptr) {
  //body
  sf::RectangleShape rect(sf::Vector2f(8, 8));
  rect.setPosition(sf::Vector2f(pos.x-4, pos.y-4));
  rect.setFillColor(sf::Color(col));
  //movedir
  sf::VertexArray line(sf::Lines, 2);
  line[0].position = sf::Vector2f(pos.x, pos.y);
  line[1].position = sf::Vector2f(pos.x+dir.x*15, pos.y+dir.y*15);
  line[0].color = col;
  line[1].color = sf::Color(0,0,0); //fade to black
  //draw
  winptr->draw(line);
  winptr->draw(rect);
  this->pos += this->dir * moveSpeed; //update movement fps based yesbad
}

