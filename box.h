//box.h
#ifndef BOX_H_
#define BOX_H_
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

//i added this too, just for fun/show BHN
sf::Color randColor();

class CBox
{
private:
   b2Body * m_body;
   b2BodyDef m_bodyDef;
   b2PolygonShape m_bodyShape;
   b2FixtureDef m_bodyFix;
   sf::RectangleShape m_shape; //SFML shape
   static int n;
public:
   CBox(b2World & world);
   CBox();
   void SetWorld(b2World & world);
   b2Body* GetBody(); // Get Box2d body
   sf::Shape & GetShape();
   void update(); // Get SFML shape
   void ResetPosition(b2World & world); //this one is me too BHN resets shapes
   void jump(float angle);
   void setN(int newN) {n = newN;}  //reset n
   int getN() {return n;}
   ~CBox();
};



#endif
