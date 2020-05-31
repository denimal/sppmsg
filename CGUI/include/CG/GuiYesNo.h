#pragma once

#include <CG/Gui.h>
#include <CG/Button.h>

using namespace std;
using namespace sf;

namespace cg
{
class GuiYesNo : public Gui
{
public:
    GuiYesNo(String text);
	void onDraw(RenderWindow& wnd);
	void onClick(int button);
	void onLoad();
	void onResize();
private:
    String message;
	Button bYes;
	Button bNo;
};
}
