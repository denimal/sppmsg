#include <CG/Slider.h>
#include <CG/GuiHandler.h>

namespace cg
{
Slider::Slider(): Widget()
{

}
Slider::Slider(Gui* gui, Vector2f pos, float dispSize, float max, int bId): Widget(gui, pos, bId), bMaxPos(max), bCurrentPos(0), bDisplaySize(dispSize)
{
    bColor = colors::sliderOutline;
    mouseClicked = false;
}
void Slider::setColor(Color color)
{
    bColor = color;
}
void Slider::setSliderPosition(float pos)
{
    bCurrentPos = pos;
}
void Slider::setMaxSliderPosition(float pos)
{
    bMaxPos = pos;
}
float Slider::getSliderPosition()
{
    return bCurrentPos;
}
float Slider::getMaxSliderPosition()
{
    return bMaxPos;
}
void Slider::draw(sf::RenderWindow& wnd)
{
    RectangleShape rs(Vector2f(bDisplaySize, colors::sliderHeight));
    rs.setOutlineThickness(2.f);

    if(enabled)
        rs.setFillColor(colors::sliderColor);
    else
        rs.setFillColor(colors::sliderDisabledColor);

    rs.setOutlineColor(bColor);
    rs.setPosition(getPosition());
    wnd.draw(rs);

    rs.setSize(Vector2f(5.f, colors::sliderHeight));
    rs.setFillColor(colors::sliderSliderColor);
    rs.setOutlineColor(colors::sliderSliderOutline);
    rs.setOrigin(rs.getSize().x / 2.f, 0.f);
    rs.setPosition(getPosition() + Vector2f(bCurrentPos * bDisplaySize / bMaxPos, 0.f));
    wnd.draw(rs);

    if(!label.isEmpty())
        wnd.draw(Gui::drawCenteredString(label, 20, Vector2f(getPosition() + Vector2f(bDisplaySize / 2, colors::sliderHeight / 2))));
}
bool Slider::isClicked(Vector2f pos)
{
    bool b = FloatRect(0.f, getPosition().y, parent->guiHandler->getSize().x, colors::sliderHeight).contains(pos);
    //if(b)
        updateSlider(pos - getPosition());
    return b;
}
void Slider::onMouseClickW(Vector2f pos, bool rel, Mouse::Button button)
{
    if(button == Mouse::Left && FloatRect(getPosition().x, getPosition().y, bDisplaySize, colors::sliderHeight).contains(pos))
    {
        if(!rel)
            mouseClicked = true;
    }
    if(rel)
        mouseClicked = false;
}
void Slider::updateSlider(Vector2f clickPos)
{
    float relPos = clickPos.x / bDisplaySize;
    if(relPos < 0)
        relPos = 0;
    else if(relPos > 1)
        relPos = 1;
    if(mouseClicked)
        bCurrentPos = relPos * bMaxPos;
}
FloatRect Slider::getBoundingBox()
{
    return FloatRect(bPos, Vector2f(bDisplaySize, colors::sliderHeight));
}
void Slider::setLabel(String l)
{
    label = l;
}
}
