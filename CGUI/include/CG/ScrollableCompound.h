#pragma once

#include <CG/ScrollBar.h>
#include <CG/Widget.h>
#include <CG/CompoundWidget.h>

namespace cg
{
class ScrollableCompound : public CompoundWidget
{
    ScrollBar scrollX;
    ScrollBar scrollY;
    Vector2f currentSize;
    Vector2f size;
    vector<Vector2f> widgetInitialPositions;
public:
    ScrollableCompound(Gui* gui, Vector2f initialPos, Vector2f initialSize, int id);
    ScrollableCompound();
    virtual void draw(RenderWindow& wnd);
    virtual void addWidget(Widget* widget);
    virtual void setSize(Vector2f size);
    virtual Vector2f getSize();
};
}
