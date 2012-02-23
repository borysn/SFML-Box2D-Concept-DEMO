/*

     This is some source code i found which i will use as a guided tutorial to play with.
	 props up to irresistable force on the bo2d forums 
	 link to thread:
	 http://box2d.org/forum/viewtopic.php?f=3&t=8102&p=34828&hilit=sfml#p34828

	 Borys H.N. 2/17/12

*/
//main.cpp file
#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include "box.h"
#include <stdio.h>
#include <Windows.h>

const int PPM = 30;

using namespace std;

struct body
{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body * BOD;
	sf::RectangleShape RECT;
};

//modifies to float by BHN
string floatToStr(float number);
float framesPS(sf::Clock &);

int main() {
    sf::RenderWindow app(sf::VideoMode(800,600,32),"Application");

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    body ground;
    ground.DEF.position.Set(400.0f/PPM,600.0f/PPM);
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000,25));//100-50? is size?
	ground.RECT.SetOrigin(4000,25);
	ground.RECT.SetFillColor(sf::Color(200,75,20,255));
    ground.SHAPE.SetAsBox(4000.0f/PPM,25.0f/PPM);
    ground.BOD = world.CreateBody(&ground.DEF);
    ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = .7f;
	ground.FIX.friction = .9f;
    ground.BOD->CreateFixture(&ground.SHAPE,1.0f);

	//text stuff to appear on the page
	sf::Font myFont;
	if (!myFont.LoadFromFile("../res/athena_u.TTF"))
		return EXIT_FAILURE;
    sf::Text Text("FPS", myFont);
    Text.SetCharacterSize(20);
    Text.SetColor(sf::Color(0, 255, 255, 255));
    Text.SetPosition(25,25);
	//added these guys BHN
	sf::Text clearInstructions("Press [Space] to reset");
	sf::Text jumpInstructions("Press [A] to make blocks jump");
	clearInstructions.SetCharacterSize(18);
	jumpInstructions.SetCharacterSize(18);
	clearInstructions.SetColor(sf::Color(200, 55, 100, 255));
	jumpInstructions.SetColor(sf::Color(200, 55, 100, 255));
	clearInstructions.SetPosition(25, 50);
	jumpInstructions.SetPosition(25, 70);

    float timeStep = 1 / 180.0f;
	sf::Event Event = sf::Event();
    sf::Clock Clock;

    sf::Clock fpsClock;
    int frameNumber = 0;
    int lastFPSFrame = 0;
    string lastFPSDisplay;

    const int boxes = 400; //adding x boxes where?
    CBox good[boxes];
    for(i; i < boxes; i++) {
		good[i].SetWorld(world);
	}
	//these next two are all me. redefining ground properties for walls BHN
	body leftWall;
    leftWall.DEF.position.Set(0.0f/PPM,-300/PPM);
	leftWall.RECT = sf::RectangleShape(sf::Vector2f(25,8000));//100-50? is size?
	leftWall.RECT.SetOrigin(0,4000);
	leftWall.RECT.SetFillColor(sf::Color(200,75,200,255));
    leftWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    leftWall.BOD = world.CreateBody(&leftWall.DEF);
    leftWall.FIX.shape = &leftWall.SHAPE;
	leftWall.FIX.density = .7f;
	leftWall.FIX.friction = .9f;
    leftWall.BOD->CreateFixture(&leftWall.SHAPE,1.0f);

	body rightWall;
    rightWall.DEF.position.Set(800.0f/PPM,-300/PPM);
	rightWall.RECT = sf::RectangleShape(sf::Vector2f(25,8000));
	rightWall.RECT.SetOrigin(25,4000);
	rightWall.RECT.SetFillColor(sf::Color(100,205,20,255));
    rightWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    rightWall.BOD = world.CreateBody(&rightWall.DEF);
    rightWall.FIX.shape = &rightWall.SHAPE;
	rightWall.FIX.density = .7f;
	rightWall.FIX.friction = .9f;
    rightWall.BOD->CreateFixture(&rightWall.SHAPE,1.0f);

	while(app.IsOpen()) {
        world.Step(timeStep,8,3);
		char buff[32];
		sprintf_s(buff, "%f", framesPS(Clock));
		Text.SetString("FPS: " + sf::String(buff));

        frameNumber++;
		if (fpsClock.GetElapsedTime().AsMilliseconds() > 1000) {
            char buf[64];
            sprintf_s(buf, "FPS: %d\n", frameNumber - lastFPSFrame);
            lastFPSDisplay = string(buf);
            lastFPSFrame = frameNumber;
			fpsClock.Restart();
            fflush(stdout);
        }

        sf::Event events;
        while (app.PollEvent(events)) {
			switch (events.Type) {
				case sf::Event::Closed:
					app.Close();
				break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) {
						app.Clear();
						app.Display();
						good->setN(0);
						for(int i = 0; i < boxes; i++) {
							good[i].ResetPosition(world);
						}
					}/* draw other squares
					 else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::G)) {
						app.Clear();
						app.Display();
						good->setN(0);
						for(int i = 0; i < boxes; i++) {
							good[i] = CBox(world);
						}
					} */else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Escape))
						app.Close();
					else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::A)) {
						for(int i = 0; i < boxes; i++) {
							good[i].jump(90);
						}
					}

				break;
			}
		}

        for(int i = 0; i < boxes; i++) {
            good[i].update();
        }

       ground.RECT.SetPosition(ground.BOD->GetPosition().x*PPM,ground.BOD->GetPosition().y*PPM);
	   //offset by 25? why?
	   leftWall.RECT.SetPosition(leftWall.BOD->GetPosition().x*PPM, leftWall.BOD->GetPosition().y*PPM);
	   rightWall.RECT.SetPosition(rightWall.BOD->GetPosition().x*PPM, rightWall.BOD->GetPosition().y*PPM);

       app.Clear();
       app.Draw(ground.RECT);
	   app.Draw(leftWall.RECT);
	   app.Draw(rightWall.RECT);
	   app.Draw(Text);
	   app.Draw(clearInstructions);
	   app.Draw(jumpInstructions);
       for(int i = 0; i < boxes; i++)
            app.Draw(good[i].GetShape());

        app.Display();
    }

    return 0;
}

float framesPS(sf::Clock & clock)
{
    bool sec = false;
    int count = 0;
    count++;
	if(clock.GetElapsedTime().AsMilliseconds() >= 1000)
    {
        sec = true;
        clock.Restart();
        count = 0;
    }
	float t = (float)clock.GetElapsedTime().AsMilliseconds();
    float ret = 0;
    if ( t ==  0 ) return 0;
	else {ret = count / (float)clock.GetElapsedTime().AsMilliseconds(); }
    if ( sec){
		char buf[64];
        sprintf_s(buf, "%f\n", ret);
        fflush(stdout);}
    return ret;
}
