#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <CG/Widget.h>
#include <string>
#include <CG/WidgetContainer.h>
#include <CG/Config.h>

using namespace std;
using namespace sf;

namespace cg
{
class GuiHandler;

class Gui : public WidgetContainer
{
public:
    /// Default constructor
    Gui();

    /// Destructor
    virtual ~Gui();

    /// current dialog id, unique for each GUI
	int dialogCallId;

	/// current dialog return value
	int dialogReturnValue;

	/// Draws this GUI and all his dialogs.
	virtual void drawAll(RenderWindow& wnd);

	/// Runs dialog with specified ID
	virtual void runDialog(Gui* dialog, int callId);

	//////                        EVENT FUNCTIONS                         //////
	// All event functions returns true if event was handled, false otherwise //
	// event handled - we don't want to handle it in parent GUI.              //
	//{
        /// Called if the user presses left mouse button. \return Clicked widget
        virtual bool handleOnMouseClick(Vector2f pos);
        virtual bool eventOnMouseClick(Vector2f pos);

        /// Called if the user moves mouse.
        virtual bool handleOnMouseMove(Vector2f pos);
        virtual bool eventOnMouseMove(Vector2f pos);

        /// Called when the keyboard key is pressed.
        virtual bool handleOnKeyboard(Keyboard::Key key);
        virtual bool eventOnKeyboard(Keyboard::Key key);

        /// Called on any keyboard event.
        virtual bool handleOnKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys);
        virtual bool eventOnKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys);

        /// Called if the dialog GUI is finished. Params: dialog ID, return value
        virtual bool handleOnDialogFinished(Gui* dialog, int callId);
        virtual bool eventOnDialogFinished(Gui* dialog, int callId);

        /// Called by Game when the button is clicked.
        virtual bool handleOnButton(int buttonId);
        virtual bool eventOnButton(int buttonId);

        /// Called every tick.
        virtual bool handleOnUpdate();
        virtual bool eventOnUpdate();

        /// Called when the text is entered.
        virtual bool handleOnText(wchar_t ch);
        virtual bool eventOnText(wchar_t ch);

        /// Called on load.
        virtual bool handleOnLoad();
        virtual bool eventOnLoad();

        /// Called if the GUI is closed.
        virtual bool handleOnClose();
        virtual bool eventOnClose();

        /// Called when the window is resized.
        virtual bool handleOnResize();
        virtual bool eventOnResize();
    //}

    // Old event functions - kept for compatibility.
    CG_DEPRECATED virtual void reloadOnResize();
    CG_DEPRECATED virtual Widget* onMouseClick(Vector2f pos);
    CG_DEPRECATED virtual Widget* onMouseClick(Vector2f pos, bool release, Mouse::Button button);
    CG_DEPRECATED virtual void onMouseMove(Vector2f pos);
    CG_DEPRECATED virtual void onKeyboard(Keyboard::Key key);
    CG_DEPRECATED virtual void onKeyboardEvent(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys);
    CG_DEPRECATED virtual void onDialogFinished(Gui* dialog, int callId);
    CG_DEPRECATED virtual void onButton(int buttonId);
    CG_DEPRECATED virtual void onUpdate();
    CG_DEPRECATED virtual void onText(wchar_t ch);
    CG_DEPRECATED virtual void onLoad();
    CG_DEPRECATED virtual void onClose();
    CG_DEPRECATED virtual void onResize();
    CG_DEPRECATED virtual void onKeyboardBase(Keyboard::Key key, bool released, bool alt, bool shift, bool ctrl, bool sys);
    CG_DEPRECATED virtual void onTextBase(wchar_t ch);

    ////////////////////////////////////////////////////////////////////////////

	/// Called by dialog function, calls onDialogFinished (child closes)
	virtual void close(int returnValue);

	/// Closes dialog by GUI (parent closes)
	virtual void closeDialog(int returnValue);

	/// Checks if the dialog is running.
	bool isDialogRunning();

	/// Draw string \return The sf::Text instance
	static Text drawString(String tx, int height, Vector2f pos, Text::Style style = Text::Regular);

	/// Draw centered string \return The sf::Text instance
    static Text drawCenteredString(String tx, int height, Vector2f pos, Text::Style style = Text::Regular);

    /// Sets the current GUI Handler.
    static void setGUIHandler(GuiHandler* handler);

    static GuiHandler* guiHandler;

protected:
	Gui* parent;

private:
	Gui* currentDialog;
};
}
