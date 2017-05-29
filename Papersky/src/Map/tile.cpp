#include "Map\tile.h"


Tile::Tile()
{
	name = "Tile";
	TileName = "air";
	sf::Vector2f lefttop(0, 0);
	setPosition(lefttop);
	collisionbox.add_point(lefttop);
	collisionbox.setPosition(lefttop);
}


void Tile::setTile(TextElement tile, sf::Texture &texture, sf::Vector2f tile_position)
{
	collisionbox.clear();
	
	TileName = tile.get_variable_by_name("Name")->var[0];
	unsigned int collision_vertexs = 0;
	collision_vertexs = atoi(tile.get_variable_by_name("Vertex_amount")->var[0].c_str());
	unsigned int toppoints = 0;
	toppoints = tile.get_variable_by_name("Top_points")->var.size();


	for (int i = 0; i < collision_vertexs; i++)
	{
		sf::Vector2f point;
		point.x = atoi(tile.get_variable_by_name("Collision_shape")->var[2*i].c_str());
		point.y = atoi(tile.get_variable_by_name("Collision_shape")->var[2 * i + 1].c_str());
		collisionbox.add_point(point);

	}
	if (collision_vertexs > 2)
	{
		sf::Vector2f point2;
		point2.x = atoi(tile.get_variable_by_name("Collision_shape")->var[0].c_str());
		point2.y = atoi(tile.get_variable_by_name("Collision_shape")->var[1].c_str());
		collisionbox.add_point(point2);
	}

	for (int i = 0; i < toppoints; i++)
	{
		top_vertex_id.push_back(atoi(tile.get_variable_by_name("Top_points")->var[i].c_str()));
	}

	setPosition(tile_position);
	collisionbox.setPosition(tile_position);

	tile_sprite.setTexture(texture);

	sf::Vector2i rectpos(atoi(tile.get_variable_by_name("Position")->var[0].c_str()), atoi(tile.get_variable_by_name("Position")->var[1].c_str()));
	sf::Vector2i rectsize(atoi(tile.get_variable_by_name("Size")->var[0].c_str()), atoi(tile.get_variable_by_name("Size")->var[1].c_str()));;

	tile_sprite.setTextureRect(sf::IntRect(rectpos, rectsize));
	tile_sprite.setPosition(tile_position-sf::Vector2f(tile_size/2, tile_size/2));
	tile_sprite.setScale(tile_size / rectsize.x, tile_size / rectsize.y);
}

void Tile::setTileMapBorder(sf::Vector2i size)
{
	TileName = "Map_Border";
	collisionbox.add_point(sf::Vector2f(0,0));
	collisionbox.add_point(sf::Vector2f(0, size.y));
	collisionbox.add_point(sf::Vector2f(size.x, size.y));
	collisionbox.add_point(sf::Vector2f(size.x, 0));

	for (int i = 0; i < 4; i++)
	{
		top_vertex_id.push_back(i);
	}


}


void Tile::drawTile(sf::RenderWindow &window)
{
	window.draw(tile_sprite);
}

void Tile::updateCollisionBoxVertexArray()
{


	std::vector <sf::Vector2f> coli_points = collisionbox.get_points();
	for (int i = 0; i <coli_points.size()-1; i++)
	{

		//vertexarray.append( sf::Vertex(coli_points[i], sf::Color(0, 0, 255, 255)));
		//vertexarray.append(sf::Vertex(coli_points[i+1], sf::Color(0, 0, 255, 255)));


	}
	if(coli_points.size()>1)
	{
		//vertexarray.append(sf::Vertex(coli_points[coli_points.size()-1], sf::Color(0, 0, 255, 255)));
		//vertexarray.append(sf::Vertex(coli_points[0], sf::Color(0, 0, 255, 255)));
	
	}
	std::cout << collisionbox.get_points()[0].x << collisionbox.get_points()[0].y;
}
void Tile::drawCollisionBoxVertexArray(sf::RenderWindow &window, bool draw_shape, bool draw_lines, int draw_point)
{
	if(draw_shape)
	{
	sf::ConvexShape shape(collisionbox.get_points().size());
	for (int i = 0; i < collisionbox.get_points().size();i++)
	{
		shape.setPoint(i, collisionbox.get_points()[i]);
	}
	shape.setFillColor(sf::Color(255, 0, 0, 150));
	window.draw(shape);
	}
	//if(draw_lines)window.draw(vertexarray, sf::Lines);
	if (draw_point >= 0 && draw_point <collisionbox.get_points().size())
	{
		sf::CircleShape circle;
		circle.setRadius(5);
		circle.setFillColor(sf::Color::Yellow);
		circle.setPosition(collisionbox.get_points()[draw_point] - sf::Vector2f(5,5));
		window.draw(circle);
	}

}
Tile::~Tile()
{
//	delete[] vertexarray;
}
