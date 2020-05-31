#pragma once

#include <CG/Widget.h>

namespace cg
{
class ScrollBar : public Widget
{
    float bMaxPos;
    float bCurrentPos;
    float bDisplaySize;
    Color bColor;
    bool vertical;
public:
    ScrollBar();
    ScrollBar(Gui* gui, Vector2f pos, float dispSize, float max, bool vert, int bId);
    virtual void setColor(Color color);
    virtual void setScrollPosition(float pos);
    virtual void setMaxScrollPosition(float pos);
    virtual float getScrollPosition();
    virtual float getMaxScrollPosition();
    virtual void draw(sf::RenderWindow& wnd);
    virtual bool isClicked(Vector2f pos);
    virtual void onMouseClickW(Vector2f pos, bool release, Mouse::Button button);
    virtual FloatRect getBoundingBox();
    virtual void setSize(float size);
private:
    void updateScroll(Vector2f clickPos);
};
}
