#pragma once
#include "Pt.h"

using namespace std;
///Class of line object
class L {

public:
	
	Pt start;///<Starting point
	Pt end;///<Ending point
	double angle;///<angle from x-axis
	//L();
	L();
	L(Pt  p1, Pt  p2);///<Constructor in 2 point form
	L(Pt  p, double slop);///<Constructon in point slope form
	//~L();
	///Function to return angle between 2 lines
	static double getAngle(L l1,L l2){
		
		return (l2.angle - l1.angle);

	}
	//
	double getIntersept();///<Function to return y intersept of a line
	double solveLine(Pt);///<Solve y-mx-c for the given point
	friend ostream & operator << (ostream &out, const L &l)
	{
		out << l.start << "\t" << l.end<<"\t"<<l.angle/PI*180;
		return out;
	}
	

};