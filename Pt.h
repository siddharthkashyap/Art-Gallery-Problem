#pragma once
#include <iostream>
#include <utility>
#define PI 3.14159265
#include <math.h>
#include <string.h>
using namespace std;
///Point class
class Pt {
public:
	double x_coordinate;///<x coordinate of a point
	double y_coordinate;///<y coordinate of a point
	Pt(double x, double y);///<constuctor for a point
	Pt();
	//Some operation on points
	bool operator < (const Pt& p) const
    {
		if(this->y_coordinate!=p.y_coordinate)
        return (this->y_coordinate < p.y_coordinate);
		else
		{
			return(this->x_coordinate > p.x_coordinate);
		}
		
	}
	bool operator > (const Pt& p) const
    {
		if(this->y_coordinate!=p.y_coordinate)
        return (this->y_coordinate > p.y_coordinate);
		else
		{
			return(this->x_coordinate<p.x_coordinate);
		}
		
	}
	bool operator == (const Pt& p) const
	{
		if (this->x_coordinate == p.x_coordinate&&this->y_coordinate == p.y_coordinate)
			return true;
		else
			return false;

	}
	
	friend ostream & operator << (ostream &out, const Pt &p)
	{
    out << p.x_coordinate<<","<<p.y_coordinate;
    return out;
	}
	

	
};

	