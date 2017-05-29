#include "Entity\player.h"
#include "Map\EntityList.h"
/*
player::player()
{
	sprite_count = 2;
	sprite = new game_sprite[sprite_count];
	acceleration.x = 0;
	velocity.x = 0;
	position.x = 0;
	acceleration.y = 0;
	velocity.y = 0;
	position.y = 0;

	sf::Vector2f p0(position.x - 16, position.y );
	sf::Vector2f p1(position.x + 16, position.y );
	sf::Vector2f p2(position.x + 16, position.y - 96);
	sf::Vector2f p3(position.x - 16, position.y - 96);
	shape.setPointCount(4);
	shape.setPoint(0, p0);
	shape.setPoint(1, p1);
	shape.setPoint(2, p2);
	shape.setPoint(3, p3);
	shape.setOrigin(position);

	sf::Color color(255, 255, 255, 100);
	shape.setFillColor(color);


///////////////////////////////////////// Tors
	std::vector < Animation > animations;

	std::string texture_localization = "main/texture/player/player.png";

	sf::Vector2i sprite_size(32,64);

	std::vector < sf::Vector2i > anim0frames;
	sf::Vector2i frame0(0, 0);
	sf::Vector2i frame1(32, 0);
	sf::Vector2i frame2(64, 0);
	sf::Vector2i frame3(96, 0);
	anim0frames.push_back(frame0);
	anim0frames.push_back(frame1);
	anim0frames.push_back(frame2);
	anim0frames.push_back(frame3);
	Animation walk_right("walk_right",0.1, sprite_size, anim0frames);


	std::vector < sf::Vector2i > anim3frames;
	sf::Vector2i frame30(0, 0);
	anim3frames.push_back(frame30);
	Animation idle_right("idle_right",0.1, sprite_size, anim3frames);

	std::vector < sf::Vector2i > anim4frames;
	sf::Vector2i frame40(0, 64);
	anim4frames.push_back(frame40);
	Animation idle_left("idle_left",0.1, sprite_size, anim4frames);

	std::vector < sf::Vector2i > anim1frames;
	sf::Vector2i frame10(0, 64);
	sf::Vector2i frame11(32, 64);
	sf::Vector2i frame12(64, 64);
	sf::Vector2i frame13(96, 64);
	anim1frames.push_back(frame10);
	anim1frames.push_back(frame11);
	anim1frames.push_back(frame12);
	anim1frames.push_back(frame13);
	Animation walk_left("walk_left",0.1, sprite_size, anim1frames);

	animations.push_back(walk_left);
	animations.push_back(walk_right);
	animations.push_back(idle_left);
	animations.push_back(idle_right);

	sf::Vector2f legs_position(16, 64);
	sprite[0].set_sprite(texture_localization, 0.1, sprite_size, animations, position);
	sprite[0].setOrigin(legs_position);

////////////////////// Glowa
	std::vector < Animation > head_animations;

	sf::Vector2i sprite_size1(32, 32);

	std::vector < sf::Vector2i > hleftframes;
	sf::Vector2i headleft(0, 160);
	hleftframes.push_back(headleft);
	Animation head_left("head_left",0.1, sprite_size1, hleftframes);

	std::vector < sf::Vector2i > hrigtframes;
	sf::Vector2i headright(0, 128);
	hrigtframes.push_back(headright);
	Animation head_right("head_right",0.1, sprite_size1, hrigtframes);
	
	head_animations.push_back(head_left);
	head_animations.push_back(head_right);

	sprite[1].set_sprite(texture_localization, 0.1, sprite_size1, head_animations, position);

	sf::Vector2f head_position(16, 92);
	sprite[1].set_sprite(texture_localization, 0.1, sprite_size1, head_animations, position);
	sprite[1].setOrigin(head_position);
}
player::player(float x, float y)
{
	position.x = x;
	position.y = y;
}

player::~player()
{
}

*/
/*
void player::move_left()
{
	std::cout << "MOVE_LEFT" << std::endl;
	is_turned_left = true;
	sprite[0].setanimation(0);
	sprite[1].setanimation(0);
	is_moving = true;
	if (velocity.x > 0) { velocity.x = 0; }

	if (velocity.x > -3)
	{
		move_via_vector_x(velocity.x / delta_time - 60);
	}
	else
	{ 
		move_via_vector_x(-300);
		//std::cout << "sYNKOSC" << std::endl;
	}
	}


void player::move_right()
{
	std::cout << "MOVE_RIGHT" << std::endl;
	is_turned_left = false;
	sprite[0].setanimation(1);
	sprite[1].setanimation(1);
	is_moving = true;
	if (velocity.x < 0) { velocity.x = 0; }

	if (velocity.x < 3)
	{
		move_via_vector_x(velocity.x / delta_time + 60);
	}
	else { move_via_vector_x(300);
	}
	//move_via_vector_x(500);

}


void player::p_update(float &deltatime)
{
	if (!is_moving)
	{
	velocity.x = 0;
	}

	if (velocity.x == 0 && is_standing)
	{

		velocity.y = 0;
	}

	if(velocity.x ==0)
	{ 
	if (is_turned_left)
	{
		sprite[0].setanimation(2);
	}
	else
	{
		sprite[0].setanimation(3);
	}
	}
	update(deltatime);
//	std::cout << "speed v " << velocity.x << " sprite_x "<< this << std::endl;

}

void player::p_draw(sf::RenderWindow &window)
{

	draw(window);

}

*/

Player::Player() 
	: Prop()
{
	Prop::Prop();
}


Player::~Player()
{
}


void Player::move_left()
{
	is_moving = true;
Impulse_velocity_x_to_max_speed(-20,-300);
}
void Player::move_right()
{
	is_moving = true;
Impulse_velocity_x_to_max_speed(20, 300);

}

void Player::move_up()
{
	//std::cout << "bottom" << is_collide_bottom << std::endl;
	if (is_collide_bottom)velocity.y = -1100;
}
void Player::move_down()
{
	//move(0, 20);
	//std::cout << "Player position: x " << getPosition().x << " y " << getPosition().y << std::endl;
}

void Player::fire()
{
	entlist->player_fire();
	std::cout << "pach";
}

bool Player::set_player(TextElement &setplayer, sf::Texture &texture)
{
	//set_prop(texture,setplayer);
	return 0;
}

void Player::handle_event(sf::Event &handleevent)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		face_left = true;
		move_left();
	}
	else
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			is_moving = 0;
			face_left = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move_right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// left key is pressed: move our character
		move_up();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// left key is pressed: move our character
		move_down();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
	//	PressingSpace();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		fire();
	}
}
void Player::Update_prop(float &delta_time, TileMap &tilemap)
{
	Prop::Update_prop(delta_time,tilemap);
	if (!is_moving) sprite[0].set_animation(3);
	else
	{
		if(velocity.x>0)sprite[0].set_animation(0);
		else sprite[0].set_animation(1);
		
	}
	auto pos = getPosition();
	int left = tilemap.get_tile(pos).y;
	int right = (tilemap.get_tilemap_size().y - 2);
	if (left >= right) { teleport(sf::Vector2f(50, 50)); };
}
