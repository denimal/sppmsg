#include <CG/Static.h>
#include <CG/Gui.h>
#include <CG/GuiHandler.h>

namespace cg
{
Static::Static() : Static(NULL, -1)
{

}

Static::Static(Gui* parent, int id) : Widget(parent, Vector2f(0.f, 0.f), id)
{
}

void Static::draw(RenderWindow& wnd)
{
    View view = wnd.getView(); //Save GUI view
    drawStatic(wnd);
    wnd.setView(view); //Restore GUI view
}
void Static::clear(RenderWindow& wnd, Color color)
{
    RectangleShape rs(parent->guiHandler->getSize());
    rs.setFillColor(color);
    wnd.draw(rs);
}

bool Static::isClicked(Vector2f)
{
    return true;
}
FloatRect Static::getBoundingBox()
{
    return FloatRect(Vector2f(0.f, 0.f), parent->guiHandler->getSize());
}
}


