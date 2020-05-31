#include <CG/CompoundWidget.h>

namespace cg
{
CompoundWidget::CompoundWidget(Gui* gui, Vector2f size, int id): Widget(gui, size, id)
{

}
bool CompoundWidget::isClicked(Vector2f pos)
{
    bool b = false;
    for(Widget* widget: widgets)
        b |= widget->isClicked(pos);
    return b;
}
}
