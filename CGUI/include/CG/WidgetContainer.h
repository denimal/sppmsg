#pragma once
#include <SFML/Graphics.hpp>
#include <CG/Widget.h>
#include <vector>

using namespace std;
using namespace sf;

namespace cg
{
class WidgetContainer
{
public:
	/// Called if the user presses left mouse button. \return Clicked widget
	virtual Widget* onMouseClick(Vector2f pos);
	virtual Widget* onMouseClick(Vector2f pos, bool release, Mouse::Button button);

	/// Called if the user moves mouse (always in GUI ticking phase)
	virtual void onMouseMove(Vector2f pos);

	/// Called in render phase.
	virtual void onDraw(RenderWindow& wnd);

	/// Called if the user clicks button with specified ID.
	virtual void onClick(int buttonId);

	/// Adds specified Widget pointer to GUI. The widgets are not copied so you must keep it as long as container exists.
	virtual void addWidget(Widget* widget);

	/// Removes specified Widget from GUI.
	virtual void removeWidget(Widget& widget);

	/// \return Current focused widget
    Widget* getFocusedWidget();

	/// Sets focus for widget.
	virtual void setFocus(Widget* widget);

	/// Sets focus for widget
	virtual void setFocus(int wId);
protected:
    vector<Widget*> widgets;
};
}
