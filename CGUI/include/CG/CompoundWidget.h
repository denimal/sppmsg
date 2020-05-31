#pragma once

#include <CG/Widget.h>
#include <CG/WidgetContainer.h>

namespace cg
{
class CompoundWidget : public Widget, public WidgetContainer
{
public:
    CompoundWidget(Gui* gui, Vector2f size, int id);

    /// Returns true when the widget is clicked. \param pos - The mouse position (relative to window)
    virtual bool isClicked(Vector2f pos);
};
}
