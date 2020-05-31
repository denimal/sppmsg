#include <CG/TextBox.h>
#include <CG/Gui.h>
#include <CG/GuiHandler.h>

namespace cg
{
TextBox::TextBox(Gui* parent, Vector2f pos, Vector2f size, int id) : Widget(parent, pos, id)
{
    bSize = size;
    textPos = 0;
    bText = "";
    multiline = false;
    autoHScroll = false;
}

bool TextBox::isClicked(Vector2f pos)
{
    FloatRect buttonRect(getPosition(), getSize());
    return enabled && buttonRect.contains(pos);
}
void TextBox::onKeyboardEvent(Keyboard::Key key, bool release, bool, bool, bool, bool)
{
    if(focus && !release)
    {
        if(key == Keyboard::Left && textPos > 0)
            textPos--;
        else if(key == Keyboard::Right && textPos + 1U <= bText.getSize())
            textPos++;
        else if(key == Keyboard::Delete)
        {
            if(!bText.isEmpty())
            {
                if(textPos != bText.getSize())
                {
                    bText.erase(textPos, 1);
                }
            }
        }
    }
}

void TextBox::setSpacesEnabled(bool spaces)
{
    disableSpaces = !spaces;
}

bool TextBox::areSpacesDisabled()
{
    return disableSpaces;
}

Vector2f TextBox::getSize()
{
    return this->bSize;
}
void TextBox::setSize(Vector2f size)
{
    bSize = size;
}
void TextBox::draw(sf::RenderWindow& wnd)
{
    sf::RectangleShape rect(this->getSize());
    rect.setPosition(this->getPosition());
    rect.setFillColor(colors::textBoxColor);
    rect.setOutlineThickness(2.2f);
    rect.setOutlineColor(colors::textBoxOutline);

    if(!this->enabled)
        rect.setFillColor(colors::textBoxDisabledColor);
    if(this->focus)
        rect.setOutlineColor(colors::textBoxFocusOutline);

    wnd.draw(rect);

    if(!focus && getText().isEmpty())
    {
        sf::Text tx = Gui::drawString(this->bTooltip, colors::textSize, this->getPosition() + sf::Vector2f(5.f, 5.f));
        tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
        tx.setPosition(this->getPosition() + this->getSize() / 2.f - sf::Vector2f(0.f, 6.f));
        tx.setFillColor(colors::stringColor);
        wnd.draw(tx);
    }
    else
    {
        sf::Text tx = Gui::drawString(this->getText(), colors::textSize, this->getPosition() + sf::Vector2f(5.f, 5.f), sf::Text::Bold);
        tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
        tx.setPosition(this->getPosition() + this->getSize() / 2.f - sf::Vector2f(0.f, 6.f));
        tx.setFillColor(colors::textBoxTooltipColor);
        wnd.draw(tx);

        RectangleShape cr(Vector2f(4.f, getSize().y));
        cr.setPosition(tx.findCharacterPos(textPos).x, getPosition().y);
        wnd.draw(cr);
    }
}
void TextBox::setTooltip(String tooltip)
{
    bTooltip = tooltip;
}
void TextBox::setText(String text)
{
    bText = text;
}
void TextBox::onMouseClickW(Vector2f pos, bool release, Mouse::Button button)
{
    Widget::onMouseClickW(pos, release, button);
    // Currently I don't want to implement this.
}
void TextBox::onText(wchar_t c)
{
    sf::Text tx = Gui::drawString(this->getText(), colors::textSize, this->getPosition() + sf::Vector2f(5.f, 5.f), sf::Text::Bold);
    tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
    tx.setPosition(this->getPosition() + this->getSize() / 2.f - sf::Vector2f(0.f, 6.f));

    float lastCharPos = tx.findCharacterPos(bText.getSize()).x;
    bool canAdd = (lastCharPos + colors::textSize < (this->getPosition() + this->getSize()).x) || autoHScroll;

    if(c == L'\b') //backspace
    {
        if(!bText.isEmpty())
        {
            if(textPos != 0)
            {
                bText.erase(textPos - 1);
                textPos--;
            }
        }
    }
    else if((c == L'\n' || c == L'\r'))
    {
        if(multiline)
        {
            bText.insert(textPos, c);
            textPos++;
        }
    }
    else if((!disableSpaces || c != L' ') && canAdd)
    {
        bText.insert(textPos, c);
        textPos++;
    }
}
String TextBox::getText()
{
    return bText;
}
void TextBox::setMultiline(bool ml)
{
    multiline = ml;
}
void TextBox::setAutoScroll(bool h)
{
    autoHScroll = h;
}

FloatRect TextBox::getBoundingBox()
{
    return FloatRect(getPosition(), getSize());
}
}
