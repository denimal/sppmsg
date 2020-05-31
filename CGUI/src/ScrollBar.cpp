#include <CG/ScrollBar.h>
#include <CG/GuiHandler.h>

namespace cg
{
ScrollBar::ScrollBar()
{

}
ScrollBar::ScrollBar(Gui* gui, Vector2f pos, float dispSize, float max, bool vert, int bId): Widget(gui, pos, bId), bMaxPos(max), bCurrentPos(0), bDisplaySize(dispSize)
{
    bColor = colors::sliderOutline;
    mouseClicked = false;
    vertical = vert;
}
void ScrollBar::setColor(Color color)
{
    bColor = color;
}
void ScrollBar::setScrollPosition(float pos)
{
    bCurrentPos = pos;
}
void ScrollBar::setMaxScrollPosition(float pos)
{
    bMaxPos = pos;
}
float ScrollBar::getScrollPosition()
{
    return bCurrentPos;
}
float ScrollBar::getMaxScrollPosition()
{
    return bMaxPos;
}
void ScrollBar::draw(sf::RenderWindow& wnd)
{
    RectangleShape rs;
    if(vertical)
        rs.setSize(Vector2f(colors::sliderHeight, bDisplaySize));
    else
        rs.setSize(Vector2f(bDisplaySize, colors::sliderHeight));

    rs.setOutlineThickness(2.f);

    if(enabled)
        rs.setFillColor(colors::sliderColor);
    else
        rs.setFillColor(colors::sliderDisabledColor);

    rs.setOutlineColor(bColor);
    rs.setPosition(getPosition());
    wnd.draw(rs);

    if(vertical)
    {
        rs.setSize(Vector2f(colors::sliderHeight, 5.f));
        rs.setOrigin(0.f, rs.getSize().y / 2.f);
        rs.setPosition(getPosition() + Vector2f(0.f, bCurrentPos * bDisplaySize / bMaxPos));
    }
    else
    {
        rs.setSize(Vector2f(5.f, colors::sliderHeight));
        rs.setOrigin(rs.getSize().x / 2.f, 0.f);
        rs.setPosition(getPosition() + Vector2f(bCurrentPos * bDisplaySize / bMaxPos, 0.f));
    }

    rs.setFillColor(colors::sliderSliderColor);
    rs.setOutlineColor(colors::sliderSliderOutline);

    wnd.draw(rs);
}
bool ScrollBar::isClicked(Vector2f pos)
{
    FloatRect rect;
    if(vertical)
        rect = FloatRect(getPosition().x, 0.f, colors::sliderHeight, parent->guiHandler->getSize().y);
    else
        rect = FloatRect(0.f, getPosition().y, parent->guiHandler->getSize().x, colors::sliderHeight);

    bool b = rect.contains(pos);
    updateScroll(pos - getPosition());
    return b;
}
void ScrollBar::onMouseClickW(Vector2f pos, bool release, Mouse::Button button)
{
    FloatRect rect;

    if(vertical)
        rect = FloatRect(getPosition().x, getPosition().y, colors::sliderHeight, bDisplaySize);
    else
        rect = FloatRect(getPosition().x, getPosition().y, bDisplaySize, colors::sliderHeight);

    if(button == Mouse::Left && rect.contains(pos))
    {
        if(!release)
            mouseClicked = true;
    }
    if(release)
        mouseClicked = false;
}
void ScrollBar::updateScroll(Vector2f clickPos)
{
    float cp;
    if(vertical)
        cp = clickPos.y;
    else
        cp = clickPos.x;

    float relPos = cp / bDisplaySize;

    if(relPos < 0)
        relPos = 0;
    else if(relPos > 1)
        relPos = 1;

    if(mouseClicked)
        bCurrentPos = relPos * bMaxPos;
}
FloatRect ScrollBar::getBoundingBox()
{
    if(vertical)
        return FloatRect(getPosition().x, getPosition().y, colors::sliderHeight, bDisplaySize);
    else
        return FloatRect(getPosition().x, getPosition().y, bDisplaySize, colors::sliderHeight);
}
void ScrollBar::setSize(float size)
{
    bDisplaySize = size;
}
}
