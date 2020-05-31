#include <CG/Gui.h>
#include <cmath>
#include <CG/GuiHandler.h>

namespace cg
{
Gui::Gui()
{
    currentDialog = nullptr;
    parent = nullptr;
}

Gui::~Gui()
{
    closeDialog(0);
}

void Gui::drawAll(RenderWindow& wnd)
{
    onDraw(wnd);
    if(isDialogRunning())
        currentDialog->drawAll(wnd);
}
void Gui::onUpdate()
{
}

Widget* Gui::onMouseClick(Vector2f pos)
{
    return nullptr;
}
Widget* Gui::onMouseClick(Vector2f pos, bool release, Mouse::Button button)
{
    if(!isDialogRunning())
    {
        return WidgetContainer::onMouseClick(pos, release, button);
    }
    else
    {
        return currentDialog->onMouseClick(pos, release, button);
    }
    return nullptr;
}

void Gui::onMouseMove(Vector2f pos)
{
    if(!isDialogRunning())
    {
        WidgetContainer::onMouseMove(pos);
    }
    else
    {
        currentDialog->onMouseMove(pos);
    }
}

void Gui::onText(wchar_t ch)
{
    Widget* widget = getFocusedWidget();
    if(widget)
    {
        widget->onText(ch);
    }
}

void Gui::onResize() {}

void Gui::runDialog(Gui* dialog, int callId)
{
    if(isDialogRunning())
    {
        closeDialog(0);
    }

    currentDialog = dialog;
    currentDialog->parent = this;
    dialogCallId = callId;
    currentDialog->onLoad();
    currentDialog->onResize();
}

void Gui::close(int returnValue)
{
    if(parent)
    {
        parent->closeDialog(returnValue);
    }
    else
    {
        guiHandler->close(returnValue);
    }
}

void Gui::onButton(int buttonId)
{
    if(isDialogRunning())
    {
        currentDialog->onButton(buttonId);
    }
    else
    {
        onClick(buttonId);
    }
}

void Gui::closeDialog(int returnValue)
{
    if(isDialogRunning())
    {
        dialogReturnValue = returnValue;
        currentDialog->onClose();
        onDialogFinished(currentDialog, dialogCallId);
        delete currentDialog;
        currentDialog = nullptr;
    }
}

void Gui::setGUIHandler(GuiHandler* handler)
{
    guiHandler = handler;
}

GuiHandler* Gui::guiHandler;

void Gui::onLoad() {}

void Gui::onClose() {}

void Gui::onKeyboard(Keyboard::Key) {}

void Gui::onKeyboardBase(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys)
{
    if(isDialogRunning())
    {
        currentDialog->onKeyboardBase(key, released, alt, shift, ctrl, sys);
    }
    else
    {
        //onKeyboard(key);
        onKeyboardEvent(key, released, alt, shift, ctrl, sys);
    }
}

void Gui::onTextBase(wchar_t c)
{
    if(isDialogRunning())
    {
        currentDialog->onTextBase(c);
    }
    else
    {
        onText(c);
    }
}

void Gui::onDialogFinished(Gui*, int) {}

bool Gui::isDialogRunning()
{
    return currentDialog != nullptr;
}

Text Gui::drawString(String tx, int height, Vector2f pos, Text::Style style)
{
    Text text = Text(tx, *guiHandler->getFont());
    text.setPosition(pos);
    text.setCharacterSize(height);
    text.setStyle(style);
    text.setFillColor(colors::stringColor);

    return text;
}

void Gui::reloadOnResize()
{
    onResize();

    if(isDialogRunning())
        currentDialog->reloadOnResize();
}

Text Gui::drawCenteredString(String tx, int height, Vector2f pos, Text::Style style)
{
	Text text = sf::Text(tx, *guiHandler->getFont(), height);
	text.setStyle(style);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos.x, pos.y);
	text.setFillColor(colors::stringColor);

	return text;
}

void Gui::onKeyboardEvent(Keyboard::Key, bool, bool, bool, bool, bool) {}

/////////////////////////////////////////////////////

bool Gui::handleOnMouseClick(Vector2f pos)
{
    return false;
}
bool Gui::eventOnMouseClick(Vector2f pos)
{
    return false;
}

bool Gui::handleOnMouseMove(Vector2f pos)
{
    return false;
}
bool Gui::eventOnMouseMove(Vector2f pos)
{
    return false;
}

bool Gui::handleOnKeyboard(Keyboard::Key key)
{
    return false;
}
bool Gui::eventOnKeyboard(Keyboard::Key key)
{
    return false;
}

bool Gui::handleOnKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys)
{
    return false;
}
bool Gui::eventOnKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys)
{
    return false;
}

bool Gui::handleOnDialogFinished(Gui* dialog, int callId)
{
    return false;
}
bool Gui::eventOnDialogFinished(Gui* dialog, int callId)
{
    return false;
}

bool Gui::handleOnButton(int buttonId)
{
    return false;
}
bool Gui::eventOnButton(int buttonId)
{
    return false;
}

bool Gui::handleOnUpdate()
{
    return false;
}
bool Gui::eventOnUpdate()
{
    return false;
}

bool Gui::handleOnText(wchar_t ch)
{
    return false;
}
bool Gui::eventOnText(wchar_t ch)
{
    return false;
}

bool Gui::handleOnLoad()
{
    return false;
}
bool Gui::eventOnLoad()
{
    return false;
}

bool Gui::handleOnClose()
{
    return false;
}
bool Gui::eventOnClose()
{
    return false;
}

bool Gui::handleOnResize()
{
    return false;
}
bool Gui::eventOnResize()
{
    return false;
}
//////////////////////////////////////////////////////

}
