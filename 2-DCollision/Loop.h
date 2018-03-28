#ifndef LOOP
#define LOOP

#include "SFML\Graphics.hpp"
#include <iostream>

#include "SFMLKeyBind.h"
#include "CollisionDetector.h"

using namespace sf;

const Time M_MS_PER_UPDATE{milliseconds(10)};

class Loop
{
public:
	Loop();
	~Loop();

	void run();
private:
	void processEvents();
	void update(Time t_dTime);
	void render();

	void processKeyInput();

	void setUpKeys();

	RenderWindow m_window;

	Color m_windowColorGreen{ 19, 236, 176, 255 };
	Color m_windowColorRed{ 215, 40, 67, 255 };
	Color m_windowColor{ 19, 236, 176, 255 };

	cd::Quad m_quadBound;
	VertexArray m_quadPoints;

	kb::KeyHandler m_keyHandler;
	std::map<std::string, kb::Key> input;
};


#endif