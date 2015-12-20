#pragma once
#include <vector>

class MainMenu {
public:
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem {
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow &renderWindow);

private:
	MenuResult GetMenuResponse(sf::RenderWindow &renderWindow);
	MenuResult HandleClick(int x, int y);
	std::vector<MenuItem> _menuItems;
};
