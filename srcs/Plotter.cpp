#include "Plotter.hpp"
#include "Maths.hpp"
#include <limits>

Plotter::Plotter( int w, int h ) : width(w), height(h), grid(w, std::vector<bool>(h, false)) {}

void	Plotter::set( int x, int y )
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		grid[x][y] = true;
}

void	Plotter::drawLine( float x0, float y0, float x1, float y1 )
{
	int steps = static_cast<int>(maths::max(maths::abs(x1 - x0), maths::abs(y1 - y0)) * 2);

	for (int i = 0; i <= steps; i++)
	{
		float t = (float)i / steps;
		set(x0 + t * (x1 - x0), y0 + t * (y1 - y0));
	}
}

void	Plotter::display()
{
	for (int y = height - 1; y >= 0; y -= 4)
	{
            for (int x = 0; x < width; x += 2)
			{
                int code = 0;

                if (get(x, y))     code |= 0x1;
                if (get(x, y-1))   code |= 0x2;
                if (get(x, y-2))   code |= 0x4;
                if (get(x+1, y))   code |= 0x8;
                if (get(x+1, y-1)) code |= 0x10;
                if (get(x+1, y-2)) code |= 0x20;
                if (get(x, y-3))   code |= 0x40;
                if (get(x+1, y-3)) code |= 0x80;

                if (code == 0) std::cout << " ";
                else
				{
                    unsigned int hex = 0x2800 + code;
                    std::cout << (char)(0xE2) << (char)(0xA0 + (hex >> 6 & 0x3)) << (char)(0x80 + (hex & 0x3F));
                }
            }
            std::cout << "\n";
        }
}

bool	Plotter::get( int x, int y )
{
	return (x >= 0 && x < width && y >= 0 && y < height) ? grid[x][y] : false;
}
