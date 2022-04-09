#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Renderer.h"
#include "Scene.h"
#include "Database.h"
#include "Sprite.h"
#include "Player.h"


class UI {
	sf::Sprite heartBorder, heart, diamond, key;
	sf::Sprite background, button;
	sf::Text text[3];
	std::string amountOfCoins = "", keyString = "";
	sf::Text coinsText, keyText;
	int scrW, scrH;
	float currentFrame = 0, currentKey = 0;

public:
	bool gamePaused = false;
	UI() {
		coinsText.setFont(DATABASE.fonts.at(0));
		coinsText.setCharacterSize(40);
		coinsText.setFillColor(sf::Color::Yellow);
		coinsText.setOutlineColor(sf::Color::Black);
		coinsText.setOutlineThickness(2);
		coinsText.setPosition(sf::Vector2f(120, 165));
		keyText.setFont(DATABASE.fonts.at(0));
		keyText.setCharacterSize(40);
		keyText.setFillColor(sf::Color::Yellow);
		keyText.setOutlineColor(sf::Color::Black);
		keyText.setOutlineThickness(2);
		keyText.setPosition(sf::Vector2f(120, 290));
		heartBorder.setTexture(DATABASE.textures.at(9));
		heart.setTexture(DATABASE.textures.at(10));
		diamond.setTexture(DATABASE.textures.at(12));
		key.setTexture(DATABASE.textures.at(16));
		heart.setScale(sf::Vector2f(4, 4));
		heartBorder.setScale(sf::Vector2f(4, 4));
		diamond.setScale(sf::Vector2f(6, 6));
		key.setScale(sf::Vector2f(3, 3));
		scrW = sf::VideoMode::getDesktopMode().width;
		scrH = sf::VideoMode::getDesktopMode().height;




		background.setTexture(DATABASE.textures.at(0));
		background.setTextureRect(sf::IntRect(1160, 81, 1294 - 1160, 190 - 81));
		background.setScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width / background.getGlobalBounds().width, sf::VideoMode::getDesktopMode().height / background.getGlobalBounds().height));
		button.setTexture(DATABASE.textures.at(2));
		button.setTextureRect(sf::IntRect(0, 0, 200, 60));
		button.setScale(2, 1.5);

		text[0].setString("Pause");
		text[0].setFillColor(sf::Color::Red);
		text[0].setOutlineColor(sf::Color::White);
		text[0].setOutlineThickness(5);
		text[0].setCharacterSize(200);
		text[0].setFont(DATABASE.fonts.at(0));
		text[0].setOrigin(text[0].getGlobalBounds().width / 2, text[0].getGlobalBounds().height / 2);
		text[0].setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 200));
		text[1].setString("Continue");
		text[2].setString("Main menu");

		for (int i = 1; i < 3; i++) {
			text[i].setFont(DATABASE.fonts.at(0));
			text[i].setFillColor(sf::Color::Red);
			text[i].setCharacterSize(80);
			text[i].setOutlineColor(sf::Color::White);
			text[i].setOutlineThickness(2);
			text[i].setOrigin(text[i].getGlobalBounds().width / 2, text[i].getGlobalBounds().height / 2);
		}
		for (int i = 2; i <= 3; i++)
			text[i - 1].setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2, 275 + 180 * i));
	}

	void Update(float time) {
		currentFrame += time * 0.003;
		currentKey += time * 0.003;
	}
	void Draw(Player player) {
		amountOfCoins = player.coinsCollected <= 0 ? "" : std::to_string(player.coinsCollected);
		keyString = std::to_string(player.keysFound) + " / " + std::to_string(3) + " keys found.";
		coinsText.setString(amountOfCoins);
		keyText.setString(keyString);
		for (int i = 0; i < player.lives; i++)
		{
			heart.setPosition(50 + i * 80, 50);
			window.Renderer.draw(heart);
		}
		for (int i = 0; i < 5; i++)
		{
			heartBorder.setPosition(50 + i * 80, 50);
			window.Renderer.draw(heartBorder);
		}
		if (currentFrame >= 5)
			currentFrame = 0;
		diamond.setTextureRect(sf::IntRect(0 + 8 * (int)currentFrame, 0, 8, 9));
		diamond.setPosition(50, 160);
		if (currentKey >= 12)
			currentKey = 0;
		key.setTextureRect(sf::IntRect(10 + (int)currentKey * 32, 0, 12, 32));
		key.setPosition(50, 270);
		window.Renderer.draw(key);
		window.Renderer.draw(coinsText);
		window.Renderer.draw(keyText);
		window.Renderer.draw(diamond);
		if (gamePaused)
			PauseMenu();
	}

	void PauseMenu() {
		window.Renderer.draw(background);
		sf::Mouse mouse;
		sf::Vector2i mousePos = mouse.getPosition(window.Renderer);
		for (int i = 2; i <= 3; i++) {

			button.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2 - 100 * 2, 250 + 180 * i));
			if (CheckCollision(button.getGlobalBounds(), mousePos)) {
				button.setColor(sf::Color(100, 0, 0, 255));
			}
			else button.setColor(sf::Color::White);
			window.Renderer.draw(button);
			window.Renderer.draw(text[i - 1]);
		}
		window.Renderer.draw(text[0]);



	}
	bool CheckCollision(sf::FloatRect rect, sf::Vector2i mousePos) {
		if (mousePos.x < rect.left)
			return false;
		if (mousePos.y < rect.top)
			return false;
		if (mousePos.x > rect.left + rect.width)
			return false;
		if (mousePos.y > rect.top + rect.height)
			return false;
		return true;
	}

	int MouseClicked(sf::Mouse mouse) {
		for (int i = 2; i <= 3; i++) {
			button.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2 - 100 * 2, 250 + 180 * i));
			if ((CheckCollision(button.getGlobalBounds(), mouse.getPosition(window.Renderer)))) {
				return i;
			}
		}
	}



};
