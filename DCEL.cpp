#include "DCEL.h"
DCEL::DCEL(){}

DCEL::DCEL(vector<Pt> input)
{
	
	face * f1=(face*)malloc(sizeof(face));
	faces.push_back(f1);
	for (int i = 0; i < input.size()-1; i++)
	{
		record * e1=(record*)malloc(sizeof(record));
		record * e2 = (record*)malloc(sizeof(record));;
		e1->origin = input[i];
		e2->origin = input[i+1];
		
		e1->face = faces[0];
		e2->face = faces[0];
		list.push_back(e1);
		list.push_back(e2);
		
	}
	for (int i = 0; i < list.size(); i += 2)
	{
		list[i]->twin = list[i + 1];
		list[i+1]->twin = list[i];
	}

	for (int i = 0; i < list.size(); i += 2)
	{
		int next_index = (i + 2) % (int)list.size();
		int prev_index = (i - 2 + (int)list.size()) % (int)list.size();
		list[i]->next = list[next_index];
		list[i]->previous = list[prev_index];
	}
	for (int i = 1; i < list.size(); i += 2)
	{
		int next_index = (i + 2) % (int)list.size();
		int prev_index = (i - 2 + (int)list.size()) % (int)list.size();
		list[i]->previous = list[next_index];
		list[i]->next = list[prev_index];
	}
	f1->start = list[0];
	
}
record DCEL::getLine(Pt vertex) {
	for (int i = 0; i < list.size(); i++)
	{
		Pt og = list[i]->origin;
		if (og == vertex)
			return *list[i];
	}
}
void DCEL::addEdge(Pt p1, Pt p2)
{
	
	record * edStartp1=list[0];
	record * edStartp2=list[0];
	int flag = 0;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->origin == p1)
		{
			for (int j = 0; j < list.size(); j++)
			{
				if (list[j]->origin == p2 && list[i]->face == list[j]->face)
				{
					edStartp1 = list[i];
					edStartp2 = list[j];
					
					flag = 1;
					break;
				}
			}
			if(flag==1)
			{
				break;
			}
		}
	}

	record * edg1=(record*)(malloc(sizeof(record)));
	record * edg2=(record*)(malloc(sizeof(record)));;
	edg1->origin = p1;
	edg2->origin = p2;

	edg1->next = edStartp2;
	edg2->next = edStartp1;

	edg1->previous = edStartp1->previous;
	edg2->previous = edStartp2->previous;
	

	edg1->previous->next = edg1;
	edg2->previous->next = edg2;

	edg1->next->previous = edg1;
	edg2->next->previous = edg2;

	edg1->twin = edg2;
	edg2->twin = edg1;

	face * fl = (face *)edStartp1->face;
	for (int i = 0; i < faces.size(); i++)
	{
		if (faces[i] == fl)
			faces.erase(faces.begin()+i);
	}

	face * f1=(face*)malloc(sizeof(face));
	face * f2=(face*)malloc(sizeof(face));

	f1->start = edg1;
	f2->start = edg2;
	
	faces.push_back(f1);
	faces.push_back(f2);
	list.push_back(edg1);
	list.push_back(edg2);
	edg1->face = &f1;
	edg2->face = &f2;

	record * tmp = edg1->next;

	while (tmp != edg1)
	{
		tmp->face = &f1;
		tmp = tmp->next;

	}

	tmp = edg2->next;
	while (tmp != edg2)
	{
		tmp->face = &f2;
		tmp = tmp->next;

	}

	
}

// int main() {
// 	vector<Pt> inp;
// 	Pt p1(1,1);
// 	inp.push_back(p1);
// 	Pt p2(0,1);
// 	inp.push_back(p2);
// 	Pt p3(0,0);
// 	inp.push_back(p3);
// 	Pt p4(1,0);
// 	inp.push_back(p4);
// 	Pt p5(1, 1);
// 	inp.push_back(p5);
// 	DCEL el(inp);
// 	el.addEdge(p1, p3);
// 	cout << el.getLine(p1);

// }