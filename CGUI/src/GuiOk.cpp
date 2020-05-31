#include <CG/GuiOk.h>
#include <CG/GuiHandler.h>

namespace cg
{
GuiOk::GuiOk(string text, GuiOkType type)
{
    guiOkType = type;
    message = text;
}
void GuiOk::onDraw(RenderWindow& wnd)
{
    Text tx = Gui::drawCenteredString(message, cg::colors::textSize, Vector2f(guiHandler->getCenter().x, 300));
	tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
	tx.setPosition(guiHandler->getCenter().x, 300);

	RectangleShape rsb(Vector2f(tx.getLocalBounds().width + 40.f, tx.getLocalBounds().height + 90.f));
	rsb.setOrigin(rsb.getSize() / 2.f);
	rsb.setFillColor(colors::guiYesNoColor);
	rsb.setOutlineColor(colors::guiYesNoOutline);
	rsb.setOutlineThickness(2.5f);
	rsb.setPosition(guiHandler->getCenter().x, 340);

	wnd.draw(rsb);
	wnd.draw(tx);

	b1.draw(wnd);
}
void GuiOk::onClick(int button)
{
    close(button);
}
void GuiOk::onLoad()
{
    addWidget(&b1);
}
void GuiOk::onResize()
{
    // Simulate button's position
	Text tx = Gui::drawCenteredString(message, 30, Vector2f(guiHandler->getCenter().x, 300));
	tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
	tx.setPosition(guiHandler->getCenter().x, 300);

	RectangleShape rsb(Vector2f(tx.getLocalBounds().width + 40.f, tx.getLocalBounds().height + 90.f));
	rsb.setOrigin(rsb.getSize() / 2.f);
	rsb.setFillColor(Color(110, 100, 65));
	rsb.setPosition(guiHandler->getCenter());

	b1 = Button(this, Vector2f(rsb.getSize().x * 0.40f, 40.f), Vector2f(rsb.getPosition().x - rsb.getSize().x * 0.20f, tx.getGlobalBounds().top + tx.getGlobalBounds().height + 20.f), "Ok", 0);
}
}

