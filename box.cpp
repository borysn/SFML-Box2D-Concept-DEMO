//box.cpp file
#include "box.h"
const int PPM = 30;

int CBox::n = 0;

CBox::CBox(b2World & world) {
	m_shape = sf::RectangleShape(sf::Vector2f(20,20));//(0,0,50,50,sf::Color(255,255,255));
	m_shape.SetOrigin(10,10);
	m_shape.SetFillColor(sf::Color(255, 0, 255, 255));
    m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
    m_bodyDef.type = b2_dynamicBody;
    m_bodyShape.SetAsBox(10.0f/PPM,10.0f/PPM);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.3f;
    m_bodyFix.friction = 0.5f;
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

void CBox::SetWorld(b2World & world) {
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

CBox::CBox() {
	m_shape = sf::RectangleShape(sf::Vector2f(10.f,10.f));//(0,0,10,10,sf::Color(255,255,255));
    m_shape.SetOrigin(5,5);
	m_shape.SetFillColor(randColor());
	//cout << 300/PPM << " : " << -300/PPM-n*5/PPM << endl;
    m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
    n++;
    m_bodyDef.type = b2_dynamicBody;
    m_bodyShape.SetAsBox(5.0f/PPM,5.0f/PPM);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.1f;
    m_bodyFix.friction = 0.1f;
}

b2Body* CBox::GetBody() {
    return m_body;
}

sf::Shape & CBox::GetShape() {
    return m_shape;
}

void CBox::update() {
    m_shape.SetRotation( m_body->GetAngle() );
    m_shape.SetPosition( m_body->GetPosition().x*PPM, m_body->GetPosition().y*PPM);
}

void CBox::ResetPosition(b2World & world) {
	//destroy stuff (memory management, otherwise they build up)
	m_body->DestroyFixture(m_body->GetFixtureList());
	world.DestroyBody(m_body);
	n++;
	//m_shape.SetOrigin(5,5); 
	m_bodyDef.position.Set(300.0f/PPM,-300.0f/PPM-n*5/PPM);
	m_bodyDef.angularVelocity = 0;
	//m_bodyDef.angle = 270;
	m_bodyDef.linearVelocity.Set(0, 60);
	//reset fixture and body
	SetWorld(world);
	//reset shape
	update();
}

void CBox::jump(float angle) {
	m_body->SetAngularVelocity(angle);
}

CBox::~CBox()
{
}


sf::Color randColor() {
	int color = rand() % 10;
	switch (color) {
	case 1:
		return sf::Color::Blue;
		break;
	case 2:
		return sf::Color::Red;
		break;
	case 3:
		return sf::Color::Yellow;
		break;
	case 4:
		return sf::Color::Cyan;
		break;
	case 5:
		return sf::Color::Green;
		break;
	case 6:
		return sf::Color::Magenta;
		break;
	case 7:
		return sf::Color(120, 59, 25); //brownish
		break;
	case 8:
		return sf::Color(25, 59, 25);
		break;
	case 9:
		return sf::Color(25, 150, 125);
		break;
	default:
		return sf::Color(220, 159, 125);
		break;
	}
}
