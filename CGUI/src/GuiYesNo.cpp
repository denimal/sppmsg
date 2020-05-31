#include <CG/GuiYesNo.h>
#include <CG/GuiHandler.h>

namespace cg
{
GuiYesNo::GuiYesNo(String text)
{
    message = text;
}

void GuiYesNo::onDraw(RenderWindow& wnd)
{
	// Background 1
	RectangleShape rsx(guiHandler->getSize());
	rsx.setFillColor(Color(0, 0, 0, 80));
	wnd.draw(rsx);

	//////////////////////////////////////////////
	//	|---------------------------|
	//	|       |15%|   |15%|       |
	//	|--25%--|Yes|20%| No|--25%--|
	//	|---------------------------|
	//////////////////////////////////////////////

	// Text
	Text tx = Gui::drawCenteredString(message, 30, Vector2f(guiHandler->getCenter().x, 300));

	// Background 2
	RectangleShape rsb(Vector2f(tx.getLocalBounds().width + 40.f, tx.getLocalBounds().height + 90.f));
	rsb.setOrigin(rsb.getSize() / 2.f);
	rsb.setFillColor(colors::guiYesNoColor);
	rsb.setPosition(guiHandler->getCenter().x, 340);
	rsb.setOutlineColor(colors::guiYesNoOutline);
	rsb.setOutlineThickness(2.5f);
	wnd.draw(rsb);

	wnd.draw(tx);
	bYes.draw(wnd);
	bNo.draw(wnd);

	Gui::onDraw(wnd);
}

void GuiYesNo::onClick(int button)
{
	if (button == 1)
    {
		close(1);
    }
	if (button == 0)
    {
		close(0);
    }
}

void GuiYesNo::onLoad()
{
	addWidget(&bYes);
	addWidget(&bNo);
}
void GuiYesNo::onResize()
{
	// Simulate button's position
	Text tx = Gui::drawCenteredString(message, 30, Vector2f(guiHandler->getCenter().x, 300));
	tx.setOrigin(tx.getLocalBounds().width / 2, tx.getLocalBounds().height / 2);
	tx.setPosition(guiHandler->getCenter().x, 300);

	RectangleShape rsb(Vector2f(tx.getLocalBounds().width + 40.f, tx.getLocalBounds().height + 90.f));
	rsb.setOrigin(rsb.getSize() / 2.f);
	rsb.setFillColor(Color(110, 100, 65));
	rsb.setPosition(guiHandler->getCenter());

	bYes = Button(this, Vector2f(rsb.getSize().x * 0.30f, 40.f), Vector2f(rsb.getPosition().x - rsb.getSize().x *0.40f, tx.getGlobalBounds().top + tx.getGlobalBounds().height + 20.f), "Yes", 1);
	bNo = Button(this, Vector2f(rsb.getSize().x * 0.30f, 40.f), Vector2f(rsb.getPosition().x + rsb.getSize().x *0.10f, tx.getGlobalBounds().top + tx.getGlobalBounds().height + 20.f), "No", 0);
}
}
