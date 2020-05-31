#pragma once

#include <SFML/Graphics.hpp>
;

using namespace sf;

namespace cg
{
class Gui;

class Widget
{
public:
    Widget(Gui* parent, Vector2f pos, int id);
    Widget();
    virtual ~Widget() {}

    /// Returns the widget position.
    virtual Vector2f getPosition();

    /// Compares this widget with other widget. Returns true if the IDs are equal.
    virtual bool operator==(Widget& r);

    /// Draws widget. Here the user can also implement the update procedure of the widget.
    virtual void draw(sf::RenderWindow& wnd) = 0;

    /// Returns true if the onButton function should be called.
	virtual bool onClick() {return false;}

	/// Called when the mouse is clicked. (Will be) used in lists to check which element is clicked.
	virtual void onMouseClickW(Vector2f pos, bool release, Mouse::Button button);

	/// Called when the keyboard key is clicked.
	virtual void onKeyboard(Keyboard::Key key);

	/// Called when the text is entered. Used by text boxes.
	virtual void onText(char c);

	/// Checks if the mouse is over on specified position. Called also when the mouse is moved so widget can handle this event here.
	virtual bool isClicked(Vector2f pos) = 0;

	/// Gets a bounding box for widget. Used by Scrollable Compound widget to automatically resize its area.
	virtual FloatRect getBoundingBox();

	/// Returns true when the widget is enabled (can use)
	virtual bool isEnabled();

	/// Returns the unique ID of the widget.
	virtual int getID();

	/// Returns true if the mouse is over.
	virtual bool mouseOver();

	/// Sets the mouse over.
	virtual void setMouseOver(bool mo = true);

	/// Returns true if the widget has focus. Used in text boxes.
	virtual bool hasFocus();

	/// Sets focus.
	virtual void setFocus(bool f = true);

	/// Returns the parent GUI.
	virtual Gui* getParent();

	/// Sets the widget's position
	virtual void setPosition(Vector2f pos);

	/// Enables / disables the widget.
	virtual void setEnabled(bool b);

protected:
	Vector2f bPos;
	bool isMouseOver;
    bool enabled;
    long id;
    bool focus;
    Gui* parent;
    bool mouseClicked;
};
}
