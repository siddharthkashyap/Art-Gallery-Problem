#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include "L.h"
#include "Pt.h"
struct record {
	Pt origin;
	record * twin;
	void * face;
	record * next;
	record * previous;
	friend ostream & operator << (ostream &out, const record &p)
	{
		out << "origin " << p.origin << "\t,\t" << "next origin" << p.next->origin;
		return out;
	}
};
class DCEL {


public:
	
	struct face {
		record * start;
	};
	vector<record*> list;

	vector<face*> faces;

	DCEL(vector<Pt>);
	DCEL();
	record getLine(Pt);
	// in i-1 and ith edge i-1 goes from p1 to p2 and i  goes from p2 to p1
	void addEdge(Pt,Pt);
	
};