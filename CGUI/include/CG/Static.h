#pragma once

#include <CG/Widget.h>
#include <SFML/Graphics.hpp>

namespace cg
{
/// Widget used when drawing a game (or other objects) on the full screen.
class Static : public Widget
{
public:
    Static();

    /// Default constructor
    Static(Gui* parent, int id);

    /// Static widget should be drawn at first to be under GUI.
    virtual void draw(RenderWindow& wnd);

    /// Here should be the code of game screen drawing. The derived classes must implement it.
    virtual void drawStatic(RenderWindow& wnd) = 0;

    /// Clears the widget area, used in rendering.
    virtual void clear(RenderWindow& wnd, Color color = Color::Black);

    /// \see Widget::isClicked
    virtual bool isClicked(Vector2f pos);

    virtual FloatRect getBoundingBox();
};
}
