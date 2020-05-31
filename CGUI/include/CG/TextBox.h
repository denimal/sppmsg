#pragma once

#include <CG/Widget.h>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

namespace cg
{
class TextBox : public Widget
{
protected:
    String bText;
    String bTooltip;
    size_t textPos;
    Vector2f bSize;
    bool disableSpaces;
    bool multiline;
    bool autoHScroll;
public:
    /// Default constructor.
    TextBox() {}

    /// Constructor.
    TextBox(Gui* parent, Vector2f pos, Vector2f size, int id);

    virtual bool isClicked(Vector2f pos);

    virtual void draw(sf::RenderWindow& wnd);

    virtual void onMouseClickW(Vector2f pos, bool release, Mouse::Button button);

    virtual void onText(wchar_t c);

    //virtual void onKeyboard(Keyboard::Key key);
    virtual void onKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys);

    /// Returns the current entered text.
    String getText();

    /// Sets the entered text.
    void setText(String text);

    /// Sets the tooltip text.
    void setTooltip(String tooltip);

    /// Disable or enable spaces
    void setSpacesEnabled(bool spaces = true);

    /// Returns true when the spaces are \b disabled.
    bool areSpacesDisabled();

    /// Returns widget size.
    Vector2f getSize();

    /// Returns widget size.
    void setSize(Vector2f size);

    void setMultiline(bool ml);
    void setAutoScroll(bool h);

    virtual FloatRect getBoundingBox();
};
}
