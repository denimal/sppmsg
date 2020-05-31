#pragma once

#include <CG/Button.h>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace cg
{
class ButtonToggle : public Button
{
	bool state;
	int animStat;

public:
	ButtonToggle(Gui* parent, Vector2f size, sf::Vector2f pos, String text, int id, bool defaultState = false);
	ButtonToggle() : ButtonToggle(nullptr, Vector2f(0, 0), Vector2f(0, 0), "Button", -1) {}

	void draw(RenderWindow& wnd);
	bool onClick();

	/// Returns the current state. false=Off, true=On
	bool getState();

	/// Sets the current state, skipping animation.
	void setState(bool b);
};
}
