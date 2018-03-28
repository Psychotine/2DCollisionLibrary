#ifndef SFML_KEY_BIND
#define SFML_KEY_BIND

#include "SFML\Graphics.hpp"
#include <map>

namespace kb
{
	/// <summary>
	/// type of input a key can have e.g. the keyboard inputs the event or the mouse does
	/// </summary>
	enum InputType
	{
		KeyboardInput,
		MouseInput
	};

	/// <summary>
	/// struct containing all info needed on a jey or mouse button press
	/// </summary>
	struct Key
	{
		//whether the input is from keyboard or mouse
		InputType inputType;
		//the sfml key code
		sf::Keyboard::Key keyCode;
		//the sfml mouse button code
		sf::Mouse::Button mouseButton;
		//bools to hold wether the button is pressed or released
		bool isPressed;
		bool isReleased;
	};

	/// <summary>
	/// Key handler class, used to queery sfml wether a particular button has been pressed or released
	/// </summary>
	class KeyHandler
	{
	public:
		KeyHandler() = default;

		/// <summary>
		/// update if a key passed to the function is pressed according to sfml
		/// </summary>
		/// <param name="t_key">key struct</param>
		/// <param name="isPressed">wether the button is pressed</param>
		void updateKey(sf::Keyboard::Key t_key, bool isPressed)
		{
			//assign the bools in the key map(of key structs)
			m_keyMap[t_key].isPressed = isPressed;
			m_keyMap[t_key].isReleased = (!isPressed);
		}

		/// <summary>
		/// update if a button passed to the function is pressed according to sfml
		/// </summary>
		/// <param name="t_button">key struct</param>
		/// <param name="isPressed">wether the key is pressed</param>
		void updateKey(sf::Mouse::Button t_button, bool isPressed)
		{
			m_mouseMap[t_button].isPressed = isPressed;
			m_mouseMap[t_button].isReleased = (!isPressed);
		}

		/// <summary>
		/// Needs to be done after all input has been used as mouse button released causes problems looking into it but for now problem is hacked fixed
		/// </summary>
		void reset()
		{
			for (auto & x : m_keyMap)
			{
				x.second.isReleased = false;
			}
			for (auto & x : m_mouseMap)
			{ 
				x.second.isReleased = false;
			}
		}

		/// <summary>
		/// returns wether the button or key in the key map is pressed
		/// </summary>
		/// <param name="t_key">the key/button being queeried</param>
		/// <returns>boolean</returns>
		bool isPressed(const Key t_key) 
		{
			if (t_key.inputType == KeyboardInput)
			{
				return m_keyMap[t_key.keyCode].isPressed;
			}
			else if (t_key.inputType == MouseInput)
			{
				return m_mouseMap[t_key.mouseButton].isPressed;
			}
		}
		/// <summary>
		/// returns wether the button or key in the key map is released
		/// </summary>
		/// <param name="t_key">the key/button being queeried</param>
		/// <returns>boolean</returns>
		bool isReleased(const Key t_key)
		{
			if (t_key.inputType == KeyboardInput)
			{
				return m_keyMap[t_key.keyCode].isReleased;
			}
			else if (t_key.inputType == MouseInput)
			{
				return m_mouseMap[t_key.mouseButton].isReleased;
			}
		}
	private:
		typedef std::map<sf::Keyboard::Key, Key> KeyMap;
		typedef std::map<sf::Mouse::Button, Key> MouseMap;

		KeyMap m_keyMap;
		MouseMap m_mouseMap;
	};
}

#endif