#include "L.h"
///Constuct Line using 2 points
L::L(Pt  p1,Pt  p2) {
	
	start = p1;
	end = p2;
	
	double base = end.x_coordinate - start.x_coordinate;
	double per = end.y_coordinate - start.y_coordinate;
	double ag = atan(per / base);
	
	if (base == 0)
	{
		if (per >= 0)
		{
			angle = PI / 2.0f;
		}
		else {
			angle =-1*( PI / 2.0f);
		}
	}
	else if (base < 0)
	{
		if (per >= 0)
		{
			angle = PI + ag;
		}
		else {
			angle = - PI + ag;
		}
	}
	else{
		angle=ag;
	}
	
}
///solves y-mx-c for a give point using this line
double L::solveLine(Pt p/**<Point to be solved*/)
{
	double m = tan(angle);
	return p.y_coordinate - m * p.x_coordinate - getIntersept();
}
///Construct line using 1 point and a slop
L::L(Pt  p1/**<Point*/, double temp_slop/**<angle of line from x axis*/) {
	start = p1;
	angle=temp_slop;
	// line->start = p1;
	// line->angle = temp_slop;

}
// static double L::getAngle(L l1/*base*/,L l2/*edge*/) {
// 	// return l2.angle - l1.angle;
// 	return 20;

// }
///Returns the y intersept of a line
double L::getIntersept() {
	return start.y_coordinate - tan(angle)*start.x_coordinate;
}
