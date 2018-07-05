# MPlotlib
Mathematical plotting library use to Bitmap

**Example**
```c
#include "mplotlib.cpp"

int main()
{
	MPlotlib mp2("m2");		
	mp2.set_max(200 ,200); // bitmap file width and height	
	mp2.set_grid(true); // open grid

	float x2[] = {0.80 ,1.10 ,2.13 ,3.20 ,4.25 ,5.72 ,6.85 ,7.110 ,8.120 ,9.155};
	float y2[] = {.80 ,2.10 ,3.20 ,4.30 ,5.40 ,6.99 ,7.111 ,8.129 ,8.137 ,9.210};
	
	std::sort(x2, x2 + 10); // array_size + array
	std::sort(y2, y2 + 10); // array_size + array
	
	mp2.draw_plot(x2 ,y2 ,10 ,'c');
	
	return 0;
}

```

**İncluding Libray and Create Object**
```c
#include "mplotlib.h"
MPlotlib mp("plot_name");
```
**Setting plot name**
```c
mp.set_plot_name("plot_name");
```
**Set grid**
```c
mp.set_grid(true); // open grid
mp.set_grid(false); // close grid, default use
```
_Grid Close_
![fig 1.](https://github.com/tlhcelik/MPlotlib/blob/master/pics/no_grid.png)

_Grid Open_
![fig 2.](https://github.com/tlhcelik/MPlotlib/blob/master/pics/yes_grid.png)

**Setting max values**
```c
mp.set_max(maximum_x_value, maximum_y_values);
```
**Sorting your arrays**
```c
float x2[] = {.80 ,1.10 ,2.13 ,3.20 ,4.25 ,5.72 ,6.85 ,7.110 ,8.120 ,9.155};
float y2[] = {.80 ,2.10 ,3.20 ,4.30 ,5.40 ,6.99 ,7.111 ,8.129 ,8.137 ,9.210};

std::sort(x2, x2 + array_size);
std::sort(y2, y2 + array_size);

```
