#pragma once

#include <CG/Gui.h>
#include <CG/Button.h>

using namespace std;
using namespace sf;

namespace cg
{
class GuiOk : public Gui
{
public:
    enum GuiOkType
    {
        Ok,
        OkCancel,
        YesNo, //currently as GuiYesNo
        YesNoCancel
    };

    GuiOk(string text, GuiOkType type = Ok);
	void onDraw(RenderWindow& wnd);
	void onClick(int button);
	void onLoad();
	void onResize();
private:
    string message;
	Button b1;
	Button b2;
	Button b3;
	GuiOkType guiOkType;
};
}
