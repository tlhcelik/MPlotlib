#ifndef _MPLOTLIB_
#define _MPLOTLIB_

#include <stdio.h>
#include "bitmap_image.hpp"

class MPlotlib
{
public:
	MPlotlib(); //cunstructor
	MPlotlib(char plot_name[]); //cunstructor2
	
	void set_grid(bool flag); // flag is true -> open grid
	
	void empty_plot();
	void set_max(float x_max,float y_max);
	void set_plot_name(char plot_name[]);
	
	int draw_plot(float x_dots[], float y_dots[], int size, char type);
	//int draw_plot(float x_dots[], float y_dots[], char type);  
	
	void sort_values(float x_dots[], float y_dots[]);
	void _test();
	
	void set_scale(float x_scale_value, float y_scale_value);
		
	float x_pos = 0;
	float y_pos = 0;
	 
private:
	float canvas_widht;
	float canvas_height;
	
	std::string  _plot_name = "default_plot.bmp";
	
	bitmap_image _image;
	
	float _x_max;
	float _y_max;
	
	float _x_amount;
	float _y_amount;
	
	float _first_x_pos_pixel;
	float _first_y_pos_pixel;
	
	int _size;
	
	bool _grid_flag = false; // default false
	
	int _draw_plot_circle(float x_dots[], float y_dots[], int size);
	int _draw_plot_block (float x_dots[], float y_dots[], int size);
	
	int _create_canvas	(int w, int h); // not using 
	void _make_scaling_lines(float x_dots[], float y_dots[]);	
	void _set_scale(float x_dots[], float y_dots[]);
	
};

	
#endif // _MPLOTLIB_
