#include <CG/Widget.h>
#include <CG/Gui.h>

namespace cg
{
Widget::Widget() : Widget(nullptr, Vector2f(), -1) {}

void Widget::onMouseClickW(Vector2f pos, bool release, Mouse::Button button)
{
    if(isClicked(pos) && !release && button == Mouse::Left)
        parent->setFocus(this);
}
void Widget::onKeyboard(Keyboard::Key)
{
    //...
}

void Widget::setPosition(Vector2f pos)
{
    bPos = pos;
}

Widget::Widget(Gui* p, Vector2f pos, int i) : bPos(pos), id(i), parent(p)
{
    focus = false;
    enabled = true;
    isMouseOver = false;
}

void Widget::setMouseOver(bool mo)
{
    isMouseOver = mo;
}

void Widget::setFocus(bool f)
{
    focus = f;
}

void Widget::onText(char)
{
}

bool Widget::operator==(Widget& r)
{
    return r.id == this->id;
}

Vector2f Widget::getPosition()
{
    return this->bPos;
}

bool Widget::isEnabled()
{
    return enabled;
}
int Widget::getID()
{
    return id;
}
bool Widget::mouseOver()
{
    return isMouseOver;
}
bool Widget::hasFocus()
{
    return focus;
}
Gui* Widget::getParent()
{
    return parent;
}
void Widget::setEnabled(bool b)
{
    enabled = b;
}
FloatRect Widget::getBoundingBox()
{
    return FloatRect(bPos, Vector2f(0.f, 0.f));
}
}
