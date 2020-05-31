#include <CG/ButtonToggle.h>
#include <CG/GuiHandler.h>

namespace cg
{
ButtonToggle::ButtonToggle(Gui* parent, Vector2f size, Vector2f pos, String text, int id, bool defaultState)
	: Button(parent,size,pos,text,id)
{
	this->setState(defaultState);
	this->animStat = 0;
	bColor = colors::buttonOutline;
}

void ButtonToggle::draw(RenderWindow& wnd)
{
	if (this->animStat > 0)
		this->animStat--;

	int ap = !state ? this->animStat : 30 - this->animStat;

	RectangleShape rect(this->getSize());
	rect.setPosition(this->getPosition());
	rect.setFillColor(colors::buttonColor);
	rect.setOutlineThickness(2.2f);
	rect.setOutlineColor(this->bColor);

	RectangleShape rect2(Vector2f(30.f, this->getSize().y));
	rect2.setPosition(this->getPosition().x + (this->getSize().x - 30.f) * (ap / 30.f), this->getPosition().y);

	int rcp = this->state ? this->animStat : 30 - this->animStat;
	int gcp = this->state ? 30 - this->animStat : this->animStat;

	Color color1 = Color(0, 255 * (gcp / 30.f), 0);
	Color color2 = Color(255 * (rcp / 30.f), 0, 0);

	rect2.setFillColor(color1 + color2);

	if (this->isMouseOver && this->enabled)
		rect.setFillColor(colors::buttonMouseOverColor);
	if (!this->enabled)
		rect.setFillColor(colors::buttonDisabledColor);

	wnd.draw(rect);
	wnd.draw(rect2);

	Text tx = Gui::drawCenteredString(this->getText() + (state ? ": On" : ": Off"), colors::textSize, this->getPosition() + this->getSize() / 2.f, Text::Bold);
	wnd.draw(tx);
}

bool ButtonToggle::onClick()
{
    if(enabled)
    {
        state = !state;
        this->animStat = 30-this->animStat; //0.5 seconds
        return true;
    }
    return false;
}

bool ButtonToggle::getState()
{
	return state;
}

void ButtonToggle::setState(bool b)
{
	state = b;
}
}
