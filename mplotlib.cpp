#include "mplotlib.h"

MPlotlib::MPlotlib(){
	
}//cunstructor END

MPlotlib::MPlotlib(char plot_name[]){
	_plot_name = plot_name;
	_plot_name += ".bmp";
}//cunstructor 2 END

void MPlotlib::set_max(float x_max, float y_max){
	_x_max = x_max;
	_y_max = y_max;
}

void MPlotlib::set_plot_name(char plot_name[]){
	_plot_name = plot_name;
	_plot_name += ".bmp";
}

void MPlotlib::set_grid(bool flag){
	_grid_flag = flag;
}

void MPlotlib::empty_plot(){
	image_drawer draw(_image);
   _image.save_image("empty_plot.bmp");
}//empty_plot END

void MPlotlib::_test(){
	image_drawer draw(_image);
	draw.rectangle(30,100 , 100 ,30);
	_image.save_image(_plot_name);
}

void MPlotlib::set_scale(float x_scale_value, float y_scale_value){
	_x_amount = x_scale_value;
	_y_amount = y_scale_value;
	
}

void MPlotlib::_set_scale(float x_dots[], float y_dots[]){
	image_drawer draw(_image);
	draw.pen_color(255,0,0); // red
	//min = 0 , max = height
	
	for (int i = 0; i < _size; i++)
	{
		//scaled_x between 0 and 1 
		float scaled_x = (x_dots[0] - x_dots[0]) / (canvas_widht - x_dots[0]);
		scaled_x *= _x_max; // convert to real numbers
		scaled_x += 10; // for x y lines in to 10 px canvas
		
		float scaled_y = (y_dots[0] - y_dots[0]) / (y_dots[_size-1] - y_dots[0]);
		scaled_y *= _y_max;
		scaled_y += 10;
	
		// x, y dogrularinin belittici cizgileri. Degerlere karsilik gelen pixel konumlarina cizer
		// olceklenmis degerlerin cizgileri set_scale() fonksiyonu ile yapilir
		draw.line_segment(scaled_x ,canvas_height -10 ,scaled_x, canvas_height); // x dots lines
		draw.line_segment(0 ,canvas_height - scaled_y  ,10, canvas_height - scaled_y); // y dotslines	
	}
}

void MPlotlib::sort_values(float x_dots[], float y_dots[]){
	float float_size = _size * 1.0;
//	std::sort(x_dots, float_size);
	
}

// feature scaling (min max normalization)
void MPlotlib::_make_scaling_lines(float x_dots[], float y_dots[]){ 
	image_drawer draw(_image);
	draw.pen_color(192,192,192); // gray
	
	for (int i = 0; i < _size; i++)
	{
		//scaled_x between 0 and 1 
		float scaled_x = (x_dots[i] - x_dots[0]) / (x_dots[_size-1] - x_dots[0]);
		scaled_x *= _x_max; // convert to real numbers
		scaled_x += 10; // for x y lines in to 10 px canvas
		
		float scaled_y = (y_dots[i] - y_dots[0]) / (y_dots[_size-1] - y_dots[0]);
		scaled_y *= _y_max;
		scaled_y += 10;
		
		printf("x de %f degeri %f inci pixelde\n",x_dots[i],scaled_x);
		printf("y de %f degeri %f inci pixelde\n",y_dots[i],scaled_y);
		
		// x, y dogrularinin belittici cizgileri. Degerlere karsilik gelen pixel konumlarina cizer
		// olceklenmis degerlerin cizgileri set_scale() fonksiyonu ile yapilir
		if (!_grid_flag)
		{
			draw.line_segment(scaled_x ,canvas_height -10 ,scaled_x, canvas_height); // x dots lines
			draw.line_segment(0 ,canvas_height - scaled_y  ,10, canvas_height - scaled_y); // y dotslines	
		}else{
			draw.line_segment(scaled_x ,canvas_height  ,scaled_x, 20); // x dots lines
			draw.line_segment(0 ,canvas_height - scaled_y  ,canvas_widht -10 , canvas_height - scaled_y); // y dotslines
		}
	}		
}

int MPlotlib::draw_plot(float x_dots[], float y_dots[], int size, char type){
	_size = size;
	
	canvas_height = _y_max + 50;
	canvas_widht  = _x_max + 50;
	
	bitmap_image image(canvas_widht, canvas_height);
	_image = image;
	
	// set background color
	_image.set_all_channels(255,255,255); //white
	
	image_drawer draw(_image);
	
	draw.pen_width(1);
	
	// draw area canvas corners
	draw.pen_color(0, 0, 0); // black
	draw.rectangle(0,canvas_height - 1, canvas_widht - 1 ,10);
	
	//set x and y line
	draw.vertical_line_segment(20 ,canvas_height - 10 ,10); // y line
	draw.horiztonal_line_segment(10 ,canvas_widht -10 , canvas_height-10); // x line
	
	_make_scaling_lines(x_dots,y_dots); // deger cizgileri
	_set_scale(x_dots,y_dots); // real lines
	 
	switch(type){
		case 'c':	_draw_plot_circle(x_dots, y_dots, size);	return 1; 	// draw to circle type
		case 'b':	_draw_plot_block(x_dots, y_dots, size);		return 1;	// draw to block type
		default	: 	return 0;
	}
	return 0;
}

int MPlotlib::_draw_plot_circle(float x_dots[], float y_dots[], int size){
	
	image_drawer draw(_image);
	draw.pen_color(255, 0, 0); // red
	
	float pixel_per_dot = (canvas_widht - 20.0) / _size; // 20.0 -> x line uzunlugu
		
	for (int i = 0; i < size; i++){
		float my_x_pos = (x_dots[i] - x_dots[0]) / (x_dots[_size-1] - x_dots[0]);
		my_x_pos *= _x_max;
		
		float my_y_pos = (y_dots[i] - y_dots[0]) / (y_dots[_size-1] - y_dots[0]);
		my_y_pos *= _y_max;
		
		draw.circle(my_x_pos +10 , canvas_height - my_y_pos - 10.0 , 3);
		// got to left bottom dots
		// canvas_height - y_dots[i] left bottom
		// x_dots[i] + 10 x and y line to inner 
	}
	
	_image.save_image(_plot_name);
	return 0;
} // circle plot END

int MPlotlib::_draw_plot_block(float x_dots[], float y_dots[], int size){
		image_drawer draw(_image);
	
	// draw area canvas
	draw.pen_color(255, 0, 0); // red
	
	for (int i = 0; i < size; i++){
		draw.circle(x_dots[i], canvas_height - y_dots[i], 3);
		// got to left bottom dots
		// canvas_height - y_dots[i] left bottom
		// x_dots[i] + 10 x and y line inner 
	}
   
   _image.save_image(_plot_name);
return 0;
} // block plot END



/*

	printf("x size : %d",size);
	printf("x dots first eleman : %d",x_dots[0]);


	
	for (int i = 0; i < _size; i++)
	{
		//scaled_x between 0 and 1 
		float scaled_x = (x_dots[i] - x_dots[0]) / (x_dots[_size-1] - x_dots[0]);
		scaled_x *= _x_max; // convert to real numbers
		scaled_x += 10; // for x y lines in to 10 px canvas
		
		float scaled_y = (y_dots[i] - y_dots[0]) / (y_dots[_size-1] - y_dots[0]);
		scaled_y *= _y_max;
		scaled_y += 10;
		
		printf("x de %f degeri %f inci pixelde\n",x_dots[i],scaled_x);
		printf("y de %f degeri %f inci pixelde\n",y_dots[i],scaled_y);
		
		// x, y dogrularinin belittici cizgileri. Degerlere karsilik gelen pixel konumlarina cizer
		// olceklenmis degerlerin cizgileri set_scale() fonksiyonu ile yapilir
		draw.line_segment(scaled_x ,canvas_height -10 ,scaled_x, canvas_height); // x dots lines
		draw.line_segment(0 ,canvas_height - scaled_y  ,10, canvas_height - scaled_y); // y dotslines	
	
	}	
	
	//draw.line_segment(10,20,canvas_widht - (canvas_widht - 10), canvas_height - 10); // y line
	//draw.line_segment(10, canvas_height - 10, canvas_widht - 10, canvas_height - 10); // x line
*/

