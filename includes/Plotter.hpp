#pragma once

#include "RuntimeTypes.hpp"
#include <string>
#include <vector>
#include <iostream>

class Plotter
{
	private:
		int		width;
		int		height;
		std::vector<std::vector<bool>>	grid;

		bool	get( int x, int y );
	
	public:
		Plotter( int w, int h );
		~Plotter() = default;

		void 	set( int x, int y );
		void	drawLine( float x0, float y0, float x1, float y1 );
		void	display();
};
