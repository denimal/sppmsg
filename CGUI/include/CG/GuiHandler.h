#pragma once

#include <CG/Gui.h>
#include <SFML/Graphics.hpp>

#define instanceof(x,type) (dynamic_cast<type*>(&x))
#define instanceof_ptr(x,type) (dynamic_cast<type*>(x))

using namespace sf;

namespace cg
{
namespace colors
{
    extern Color buttonColor;
    extern Color buttonOutline;
    extern Color buttonDisabledColor;
    extern Color buttonMouseOverColor;

    extern Color guiYesNoColor;
    extern Color guiYesNoOutline;

    extern Color stringColor;
    extern Color bgColor;
    extern int textSize;

    extern Color textBoxColor;
    extern Color textBoxOutline;
    extern Color textBoxFocusOutline;
    extern Color textBoxDisabledColor;
    extern Color textBoxTooltipColor;

    extern float sliderHeight;
    extern Color sliderColor;
    extern Color sliderOutline;
    extern Color sliderDisabledColor;
    extern Color sliderSliderColor;
    extern Color sliderSliderOutline;
}
/// Define the SFML Event handler. \return True if the event was handled (we don't want to handle GUI events), false otherwise
typedef bool(*EventHandler)(Event);

class GuiHandler
{
protected:
    View guiView;
    Gui* displayedGui;
    Gui* guiToDisplay;

private:
    RenderWindow* window;
    EventHandler eventHandler;
    int returnValue;
    Font* guiFont;
    bool externalWindow;
    bool externalFont;
    bool newGuiSet;
    bool running;
public:
    /// Default constructor
    GuiHandler();

    /// Constructor \param wnd - The SFML Window,
    /// If the window is NULL, you must create the window by createWindow function
    GuiHandler(RenderWindow* wnd, Font* font);

    /// Default destructor.
    virtual ~GuiHandler();

    /// \return Currently used SFML window.
    virtual RenderWindow* getWindow();

    /// Creates the window with the new parameters. If fullscreen, the xSize and ySize are not used.
    virtual RenderWindow* createWindow(int xSize, int ySize, String title, bool fullscreen = false);

    /// Sets the window. If NULL, the window must be created by createWindow().
    virtual void setWindow(RenderWindow* wnd = NULL);

    /// Loads the new font used with rendering.
    virtual bool loadFont(String fileName);

    /// Sets the current font.
    virtual void setFont(Font* font);

    /// Returns the current font.
    virtual Font* getFont();

    /// Runs the single GUI tick.
    virtual int runTick();

    /// Sets the current EventHandler.
    virtual void setEventHandler(EventHandler handler);

    /// Runs a single event handler for current GUI.
    virtual void handleEvent(Event& event);

    /// Draws current GUI to the window \param fullRender - if the window should be cleared and displayed. \param gameView - The SFML view, which should be restored after GUI rendering.
    virtual void drawGui(bool fullRender = true, View gameView = View(Vector2f(0.f,0.f),Vector2f(0.f,0.f)));

    /// Sets the specified GUI to load. The GUI is loaded on next tick.
	/// The GUI must be created dynamically (by "new"!)
    virtual void displayGui(Gui* gui, bool init = false);

    /// Closes current GUI.
    virtual void closeGui();

    /// is the GUI loaded?
    virtual bool isGuiLoaded();

    /// \return Currently used GUI.
    virtual Gui* getCurrentGUI();

    /// \return The window center
    virtual Vector2f getCenter();

    /// \return The window size
    virtual Vector2f getSize();

    /// Sets return value to specified.
    virtual void close(int ret = 0);

    /// Initializes the previously set GUI. Called internally.
    virtual void initializeGui();

    /// Run main loop and return program return value.
    virtual int run();

    // Called on load. in 1.1 ??
    //virtual void load();
protected:
    /// Handle mouse move event internally (GUI loop).
    virtual void tickEventMouseMove(Vector2f pos);

	/// Handle mouse click event internally (GUI loop).
    virtual void tickEventMouseClick(Vector2f pos, bool release, Mouse::Button button);
};
}
