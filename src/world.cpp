#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "player.hpp"

#include <SFML/Graphics.hpp>

World::World()
{
	if (!tile_set.loadFromFile("content/dirt-tiles.png"))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}
	tile.setTexture(tile_set);
}

void World::createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Player& player_rect, Player& player2_rect, bool& player_tile_collision, bool& player2_tile_collision, int player1_height, int player2_height)
{
	// Loop through tile_map and assign tile texture to tile
	// according to what string it is assigned to
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j != map_width; j++)
		{
			if (tile_map[i][j] == 'G')
			{
				tile.setTextureRect(sf::IntRect(0 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == 'B')
			{
				tile.setTextureRect(sf::IntRect(1 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == '0' || tile_map[i][j] == ' ')
			{
				continue;
			}

			// Set tile position
			tile.setPosition(sf::Vector2f(j * tile_width, i * tile_height));
			playerCollision(player_rect, player2_rect, player_tile_collision, player2_tile_collision, player1_height, player2_height);
			window.draw(tile);
		}
	}
}

void World::playerCollision(Player& player_rect, Player& player2_rect, bool& player_tile_collision, bool& player2_tile_collision, int player1_height, int player2_height)
{
	tile_top = tile.getPosition().y;
	auto player1 = player_rect.player;
	auto player2 = player2_rect.player;

	// Detect collision between player1 and tile
	if (player1.getGlobalHitbox().intersects(tile.getGlobalBounds()))
	{
		player_tile_collision = true;
		player_rect.player.setPosition(sf::Vector2f(player_rect.player.getPosition().x, tile.getPosition().y - player1_height / 2 + 1));
	}

	// Detect collision between player2 and tile
	if (player2.getGlobalHitbox().intersects(tile.getGlobalBounds()))
	{
		player2_tile_collision = true;
		player2_rect.player.setPosition(sf::Vector2f(player2_rect.player.getPosition().x, tile.getPosition().y - player2_height / 2 + 1));
	}
}