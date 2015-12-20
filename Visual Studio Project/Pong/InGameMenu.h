#pragma once


class InGameMenu {
public:
	enum MenuResult{Nothing, Exit, Resume, Restart};

	struct MenuItem {
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow &window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow &window);
	MenuResult HandleClick(int x, int y);
	std::vector<MenuItem> _menuItems;
};