#include "collision.hpp"

bool check_line_collision(sf::Vector2f &Line1A, sf::Vector2f &Line1B, sf::Vector2f &Line2A, sf::Vector2f &Line2B)
{

	return 0;
}


double det_matrix(sf::Vector2f &x, sf::Vector2f &y, sf::Vector2f &z)
{
	return(x.x*y.y + y.x*z.y + z.x*x.y - z.x*y.y - x.x*z.y - y.x*x.y);
}

bool same_line(sf::Vector2f &x, sf::Vector2f &y, sf::Vector2f &z)
//Ta funkcja sprawdza, czy punkt z nale¿y do odcinka |xy|
{
	if (det_matrix(x,y,z) != 0) return(0); else
	{
		if (
			(std::min(x.x, y.x) <= z.x) && (z.x <= std::max(x.x, y.x)) && (std::min(x.y, y.y) <= z.y) && (z.y <= std::max(x.y, y.y))
			)
			return(1); else
			return(0);
	}
}



bool check_lines(sf::Vector2f &A, sf::Vector2f &B, sf::Vector2f &X, sf::Vector2f &Y)
{

	/*//Sprawdzanie, czy jakiœ punkt nale¿y do drugiego odcinka
	if (same_line(A, B, X) == 1) return true; else
		if (same_line(A, B, Y) == 1) return true; else
			if (same_line(A,X,Y) == 1) return true; else
				if (same_line(B,X,Y) == 1) return true; else*/
				//zaden punkt nie nalezy do drugego odcinka
	if (det_matrix(A, B, X)>=0 && det_matrix(A, B, Y) >= 0 || det_matrix(A, B, X) <= 0 && det_matrix(A, B, Y) <= 0)
	{
		return false;
	}
	else
		if (det_matrix(X, Y, A)>= 0 && det_matrix(X, Y, B) >= 0 || det_matrix(X, Y, A) <= 0 && det_matrix(X, Y, B) <= 0)
		{
			return false;
		}
		else //znaki wyznaczników sa równe
		{
			return true;
		}
					return false;
}


 sf::Vector2f &check_collision_with_line(std::vector <sf::Vector2f> &shape, sf::Vector2f &A, sf::Vector2f &B)
{
	for (int i = 0; i < shape.size()-1; i++)
	{
		if (check_lines(shape[i], shape[i + 1], A, B))
		{
			float a = (shape[i + 1].y - shape[i].y) / (shape[i + 1].x - shape[i].x);
			float b = shape[i].y - a*shape[i].x;
			return sf::Vector2f(a,b);
		}
			
	}
	if (1 <= shape.size())
	{
		if (check_lines(shape[shape.size() - 1], shape[0], A, B))
		{
			float a = (shape[0].y - shape[shape.size() - 1].y) / (shape[0].x - shape[shape.size() - 1].x);
			float b = shape[0].y - a*shape[0].x;
			return sf::Vector2f(a, b);
		}
	}
	else return sf::Vector2f(0,0);

	return sf::Vector2f(0, 0);
}

sf::Vector2f getline_intersection_point(sf::Vector2f &A, sf::Vector2f &B, sf::Vector2f &C, sf::Vector2f &D)
{
	sf::Vector2f point;
	point.x = ((B.x - A.x)*(D.x*C.y - D.y*C.x) - (D.x - C.x)*(B.x*A.y - B.y*A.x)) / ((B.y - A.y)*(D.x - C.x) - (D.y - C.y)*(B.x - A.x));
	point.y = ((D.y - C.y)*(B.x*A.y - B.y*A.x) - (B.y - A.y)*(D.x*C.y - D.y*C.x)) / ((D.y - C.y)*(B.x - A.x) - (B.y - A.y)*(D.x - C.x));
	return point;
}

bool check_and_get_line_intersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f &i)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p1.x - p0.x;     s1_y = p1.y - p0.y;
	s2_x = p3.x - p2.x;     s2_y = p3.y - p2.y;

	float s, t;
	s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		i = sf::Vector2f(p0.x + (t * s1_x), p0.y + (t * s1_y));

		return 1;
	}

	return 0; // No collision
}

bool check_and_get_lines_intersection(std::vector<sf::Vector2f> &shape, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f &position)
{
	bool intersect = false;
	std::vector<sf::Vector2f> all_points;
	for (int i = 0; i < shape.size()-1;i++)
	{
		sf::Vector2f m_vector;

		if (check_and_get_line_intersection(shape[i], shape[i + 1], p2, p3, m_vector))
		{
			intersect = true;
			all_points.push_back(m_vector);
		}
	}
	if (all_points.size() != 0)
	{
		position = all_points[0];
		float current_distance = (all_points[0].x - p2.x)*(all_points[0].x - p2.x) + (all_points[0].y - p2.y)*(all_points[0].y - p2.y);
	for (int i = 1; i < all_points.size();i++)
	{
		float distance = (all_points[i].y - p2.y)*(all_points[i].y - p2.y) + (all_points[i].x - p2.x)*(all_points[i].x - p2.x);
		if (distance < current_distance) 
		{
			current_distance = distance;
			position = all_points[i];
		}
	}
}
	return intersect;
}


sf::Vector2i check_collision(sf::ConvexShape &shapeX, sf::ConvexShape &shapeY)
{
	sf::Vector2i collision;
	for (int i = 0; i < shapeX.getPointCount() - 1; i++)
	{
		for (int j = 0; j < shapeY.getPointCount() - 1; j++)
		{
			if (check_lines(shapeX.getPoint(i), shapeX.getPoint(i + 1), shapeY.getPoint(j), shapeX.getPoint(j + 1)))
			{
				collision.x = i;
				collision.y = j;
				return collision;
			}
			if (1 <= shapeY.getPointCount())
			{
				if (check_lines(shapeX.getPoint(i), shapeX.getPoint(i + 1), shapeY.getPoint(shapeY.getPointCount()), shapeY.getPoint(0)))
				{
					collision.x = i;
					collision.y = shapeY.getPointCount();
					return collision;
				}
			}
		}
	}
		if (1 <= shapeX.getPointCount())
		{
			for (int z = 0; z < shapeY.getPointCount() - 1; z++)
			{
				if (check_lines(shapeX.getPoint(shapeX.getPointCount()), shapeX.getPoint(0), shapeY.getPoint(z), shapeX.getPoint(z + 1)))
				{
					collision.x = shapeX.getPointCount();
					collision.y = z;
					return collision;
				}
				if (1 <= shapeY.getPointCount())
				{
					if (check_lines(shapeX.getPoint(shapeX.getPointCount()), shapeX.getPoint(0), shapeY.getPoint(shapeY.getPointCount()), shapeY.getPoint(0)))
					{
						collision.x = shapeX.getPointCount();
						collision.y = shapeY.getPointCount();
						return collision;
					}
				}
			}
		}
		return collision;
	}

bool intersects_convex(std::vector<sf::Vector2f> &shape, sf::Vector2f &point)
{
	int i, j;
	bool c = 0;
	for (i = 0, j = shape.size() - 1; i < shape.size(); j = i++) 
	{
		if (((shape[i].y>point.y) != (shape[j].y>point.y)) && (point.x < (shape[j].x - shape[i].x) * (point.y - shape[i].y) / (shape[j].y - shape[i].y) + shape[i].x)) c = !c;
			
	}
	return c;
}

unsigned int get_nearest_wall(std::vector<sf::Vector2f> &shape, sf::Vector2f &point)
{
	unsigned int near_wall_id = shape.size();

	if (shape.size() > 2)
	{
		float a = (shape[0].y - shape[shape.size() - 1].y) / (shape[0].x - shape[shape.size() - 1].x);
		float b = shape[0].y - a*shape[0].x;
		int nearest_lenght = (point.x*a - point.y + b)/sqrt(a*a + 1);

	for (int i = 1; i < shape.size();i++)
	{
		float a = (shape[i+1].y - shape[i].y) / (shape[i+1].x - shape[i].x);
		float b = shape[i].y - a*shape[i].x;
		int current_lenght = (point.x*a - point.y + b) / sqrt(a*a + 1);
		if (nearest_lenght > current_lenght)
		{
			near_wall_id = i;
			nearest_lenght = current_lenght;
		}
	}
	}
	return near_wall_id;
}



Wall operator >(Wall & wall1, Wall & wall2)
{
	if (wall1.distance > wall2.distance) return wall1;
	else
	{
		return wall2;
	}

}

Wall operator <(Wall & wall1, Wall & wall2)
{
	if (wall1.distance < wall2.distance) return wall1;
	else
	{
		return wall2;
	}

}
