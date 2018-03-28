#include "Loop.h"

Loop::Loop() :
	m_window(VideoMode(800,600), "2D-Collision Test Ground"),
	m_quadPoints(sf::Points, 4)
{
	setUpKeys();

	m_quadBound.topLeft.x = 100;
	m_quadBound.topLeft.y = 100;
	m_quadBound.size.x = 100;
	m_quadBound.size.y = 100;

	m_quadPoints[0].position = sf::Vector2f(m_quadBound.topLeft.x, m_quadBound.topLeft.y);
	m_quadPoints[1].position = sf::Vector2f(m_quadBound.topLeft.x + m_quadBound.size.x, m_quadBound.topLeft.y);
	m_quadPoints[2].position = sf::Vector2f(m_quadBound.topLeft.x, m_quadBound.topLeft.y + m_quadBound.size.y);
	m_quadPoints[3].position = sf::Vector2f(m_quadBound.topLeft.x + m_quadBound.size.x, m_quadBound.topLeft.y + m_quadBound.size.y);
}

Loop::~Loop()
{
}

void Loop::run()
{
	//the clock object, keeps track of the time passing
	sf::Clock clock;
	//the amount of time since the last loop was completed
	sf::Time lag = sf::Time::Zero;

	//loop while the window is open
	while (m_window.isOpen())
	{
		//holds the time since the last loop, resets the clock
		sf::Time dTime = clock.restart();
		lag += dTime;
		//update input
		processEvents();

		//update as long as the lag is larger then the time per frame
		while (lag > M_MS_PER_UPDATE)
		{
			update(M_MS_PER_UPDATE);
			lag -= M_MS_PER_UPDATE;
		}
		//draw to the screen
		render();
	}
}

void Loop::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			m_keyHandler.updateKey(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			m_keyHandler.updateKey(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			m_keyHandler.updateKey(event.mouseButton.button, true);
			break;
		case sf::Event::MouseButtonReleased:
			m_keyHandler.updateKey(event.mouseButton.button, false);
			break;
		default:
			break;
		}

		//if the window is closed or the escape button is pressed, cloase the window
		if (sf::Event::Closed == event.type || m_keyHandler.isPressed(input["Esc"])) // window message
		{
			m_window.close();
		}
	}
}

void Loop::update(Time t_dTime)
{
	processKeyInput();

	m_quadPoints[0].position = sf::Vector2f(m_quadBound.topLeft.x, m_quadBound.topLeft.y);
	m_quadPoints[1].position = sf::Vector2f(m_quadBound.topLeft.x + m_quadBound.size.x, m_quadBound.topLeft.y);
	m_quadPoints[2].position = sf::Vector2f(m_quadBound.topLeft.x, m_quadBound.topLeft.y + m_quadBound.size.y);
	m_quadPoints[3].position = sf::Vector2f(m_quadBound.topLeft.x + m_quadBound.size.x, m_quadBound.topLeft.y + m_quadBound.size.y);
}

void Loop::render()
{
	m_window.clear(m_windowColor);
	m_window.draw(m_quadPoints);
	m_window.display();
}

void Loop::processKeyInput()
{
	if (m_keyHandler.isPressed(input["PosRot"]))
	{
		m_quadBound.rotation.cos += (1 * PI / 180.f);
	}
	else if (m_keyHandler.isPressed(input["NegRot"]))
	{
		m_quadBound.rotation.cos -= (1 * PI / 180.f);
	}
	if (m_keyHandler.isPressed(input["Up"]))
	{
		m_quadBound.topLeft.y--;
	}
	if (m_keyHandler.isPressed(input["Left"]))
	{
		m_quadBound.topLeft.x--;
	}
	if (m_keyHandler.isPressed(input["Down"]))
	{
		m_quadBound.topLeft.y++;
	}
	if (m_keyHandler.isPressed(input["Right"]))
	{
		m_quadBound.topLeft.x++;
	}
	if (m_keyHandler.isReleased(input["LeftClick"]))
	{
		if (m_windowColor == m_windowColorGreen)
		{
			m_windowColor = m_windowColorRed;
		}
		else
		{
			m_windowColor = m_windowColorGreen;
		}
	}
	m_keyHandler.reset();
}

void Loop::setUpKeys()
{
	kb::Key key;

	key.inputType = kb::KeyboardInput;
	key.keyCode = sf::Keyboard::Escape;
	key.isPressed = false;
	key.isReleased = false;
	input["Esc"] = key;
	key.keyCode = sf::Keyboard::Add;
	input["PosRot"] = key;
	key.keyCode = sf::Keyboard::Subtract;
	input["NegRot"] = key;
	key.keyCode = sf::Keyboard::W;
	input["Up"] = key;
	key.keyCode = sf::Keyboard::A;
	input["Left"] = key;
	key.keyCode = sf::Keyboard::S;
	input["Down"] = key;
	key.keyCode = sf::Keyboard::D;
	input["Right"] = key;

	key.inputType = kb::MouseInput;
	key.mouseButton = sf::Mouse::Button::Left;
	input["LeftClick"] = key;
}
