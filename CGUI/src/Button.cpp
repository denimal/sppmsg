#include <CG/Button.h>
#include <CG/GuiHandler.h>

namespace cg
{
Button::Button(Gui* p, Vector2f size, Vector2f pos, String text, int id)
: Widget(p, pos, id)
{
    this->isMouseOver = false;
    this->bColor = colors::buttonOutline;
    this->bSize = size;
    this->bText = text;
    this->enabled = true;
    this->blinking = false;
}

void Button::draw(RenderWindow& wnd)
{
    static int animTick = 0;
    animTick++;
    bool isBlink = animTick / 30 % 2;
    RectangleShape rect(this->getSize());
    rect.setPosition(this->getPosition());
    rect.setFillColor(colors::buttonColor);
    rect.setOutlineThickness((isBlink && blinking) ? 4.f : 2.2f);
    rect.setOutlineColor(this->bColor);

    if(this->isMouseOver && this->enabled)
        rect.setFillColor(colors::buttonMouseOverColor);
    if(!this->enabled)
        rect.setFillColor(colors::buttonDisabledColor);

    wnd.draw(rect);

    Text tx = Gui::drawCenteredString(this->getText(), colors::textSize, this->getPosition() + this->getSize() / 2.f - sf::Vector2f(0.f, 6.f), sf::Text::Bold);
	wnd.draw(tx);
}

String Button::getText()
{
    return this->bText;
}
void Button::setSize(Vector2f size)
{
    bSize = size;
}
Vector2f Button::getSize()
{
    return this->bSize;
}

bool Button::isClicked(Vector2f pos)
{
    FloatRect buttonRect(getPosition(), getSize());
    return buttonRect.contains(pos);
}

bool Button::onClick()
{
	//nothing to do
	return enabled;
}

void Button::setColor(Color color)
{
    this->bColor = color;
}

Text Button::drawString(String tx, int height, Vector2f pos, Text::Style style)
{
    return Gui::drawString(tx, height, pos, style);
}

void Button::setText(String text)
{
    bText = text;
}
FloatRect Button::getBoundingBox()
{
    return FloatRect(bPos, bSize);
}
}
