#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <CG/Gui.h>
#include <CG/Widget.h>

using namespace std;
using namespace sf;

namespace cg
{
class Button : public Widget
{
public:
    Button(Gui* parent, Vector2f size, Vector2f pos, String text, int id);
	Button() : Button(nullptr, Vector2f(0, 0), Vector2f(100, 30), "Button", -1) {}

	/// Returns the button label.
    String getText();

    /// Returns the button size.
    Vector2f getSize();

    void setColor(Color color);

    bool blinking;

	void setBlinking(bool b1) {blinking = b1;} //not implemented !!!

    /// Draw string.
    Text drawString(String, int, Vector2f, Text::Style);

    virtual void draw(RenderWindow& wnd);

	virtual bool onClick();

	virtual bool isClicked(Vector2f pos);

    virtual void setSize(Vector2f size);

    virtual void setText(String text);

    virtual FloatRect getBoundingBox();

protected:
	String bText;
	Color bColor;
    Vector2f bSize;
};
}
