#include "players.hpp"

Players::Players(float player_width, float player_height, float player_x, float player_y)
{
	player.setFillColor(sf::Color::White);
	player.setSize(sf::Vector2f(player_width, player_height));
	player.setPosition(sf::Vector2f(player_x, player_y));
}

void Players::drawTo(sf::RenderWindow& window)
{
	window.draw(player);
}

void Players::movePlayers(int player_speed, bool& player_tile_collision)
{
	velocity.x = 0;

	// velocity.y += gravity;
	if (player_tile_collision)
	{
		velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			velocity.y -= 15;
		}
	}
	else
	{
		velocity.y += gravity;
	}

	std::cout << velocity.y << "\n";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = player_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -player_speed;
	}

	player.move(velocity);
}

void Players::tileCollision()
{
	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + 50;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player.getTextureRect().width;
}