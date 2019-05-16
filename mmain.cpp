# include "triangulation.h"
# define start_vertex 0
# define end_vertex 1
# define split_vertex 2
# define merge_vertex 3
# define regular_vertex 4

DCEL d1;
set< int >status;
map< int,Pt > helper;
map<pair<Pt,Pt> ,int> indx;
map<int,pair<Pt,Pt> > r_indx;
map<Pt,int>vis;
int num__line;
vector<pair<Pt,int> >mvector;
map<Pt,int> cache;
int st = 0;
vector<pair<Pt,Pt> >ans;

triangulation::triangulation(DCEL * dtemp){
    d1=dtemp;

}

/// Function returns the next point for the required point
Pt get_nxt_Pt (Pt p/**<given point*/)
{
    record curr = d1.getLine(p);
    if(vis[p] == 1)
    {
        record nxt = *(curr.twin);
        Pt p1 = nxt.origin;
        return p1;
    }
    else
    {
        record nxt = *(curr.previous);
        Pt p1 = nxt.origin;
        return p1;
    }
}

/// Function returns the previous point for the required point
Pt get_prev_Pt(Pt p/**<given point*/)
{
    record curr = d1.getLine(p);
    if(vis[p] == 1)
    {
        record nxt = *curr.previous;
        Pt p1 = nxt.origin;
        return p1;
    }
    else
    {
        record nxt = *curr.next;
        Pt p1 = nxt.origin;
        return p1;
    }
}

/// Function returs the orientation of 3 points 
/** Functions returns the orientation of the points and tells whether they are clock-wise 
 or counter-clockwise */

int orientation(Pt p1/**<given point p1*/, Pt p2/**<given point p2*/ , Pt p3 /**<given point p3*/) 
{ 
    int val = (p2.y_coordinate - p1.y_coordinate) * (p3.x_coordinate - p2.x_coordinate) - 
              (p2.x_coordinate - p1.x_coordinate) * (p3.y_coordinate - p2.y_coordinate); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

/// returns the type of point
/** returns the type of point as start,end,split,merge or regular vertex*/
int triangulation :: check_type(Pt p /**<given point*/)
{
   if(cache.find(p) != cache.end())
    return cache[p];

   Pt p1 = get_nxt_Pt(p);
   Pt p2 = get_prev_Pt(p);
   cout << p <<" "<< p1 <<" "<< p2<<"\n";
   int x =  orientation(p1,p,p2);
   if(p1.y_coordinate < p.y_coordinate && p2.y_coordinate < p.y_coordinate)
   {
       if(x == 1)
         return cache[p] = start_vertex;
       else if(x == 2)
         return cache[p] = split_vertex; 
   }
   else if(p1.y_coordinate > p.y_coordinate && p2.y_coordinate > p.y_coordinate)
   {
       if(x == 1)
         return cache[p] = end_vertex;
       if(x == 2)
         return cache[p] = merge_vertex;  
   }

   return cache[p] = regular_vertex;
}


/// returns the left edge of a given point
int find_left(Pt p/**<given point*/)
{
    double x = p.x_coordinate;
    double y = p.y_coordinate;
    map<double,int> ind;
    set<double> ss;
    for(auto it:status)
    {
        pair<Pt,Pt> pts = r_indx[it];
        double max_y = max(pts.first.y_coordinate,pts.second.y_coordinate);
        double min_y = min(pts.first.y_coordinate,pts.second.y_coordinate);
        double y1 = pts.first.y_coordinate,x1 = pts.first.x_coordinate;
        double y2 = pts.second.y_coordinate,x2 = pts.second.x_coordinate;

        if(y > max_y || y < min_y)
            continue;
        double nx = ((y-y1)*(x1-x2)/(y1-y2)) + x1;
        ind[nx] = it;
        ss.insert(nx);
    }
    auto it1 = ss.upper_bound(x-0.00001);
	int s = ss.size();
	if (s == 1)
	{
		it1 = ss.begin();
		return ind[*it1];
	}
		
    it1--;
    return ind[*it1];
}

/// handles regular point
void triangulation :: handle_regular_vertex(Pt p/**<given point*/)
{
    Pt p1 = get_nxt_Pt(p);
    Pt p2 = get_prev_Pt(p);
    cout << "regular vertex"<<"\n";
    cout << p <<" "<< p1 <<" "<< p2<<"\n";
    if( p1.y_coordinate < p.y_coordinate)
    {
        int id = indx[make_pair(p,p1)];
        cout << id <<" "<< helper[id-1]<<"\n ";
        if((id-1) >=0 && check_type(helper[id-1])== merge_vertex)
        {
            d1->addEdge(p,helper[id-1]);
            st = 1;
            ans.push_back(make_pair(p,helper[id-1]));
        }
        status.erase(id-1);
        status.insert(id);
        helper[id] = p;
    }
    else
    {
        int id = find_left(p);
        cout << id <<" "<<helper[id]<< "\n";
        if((id)>=0 && check_type(helper[id]) == merge_vertex)
        {
            d1->addEdge(p,helper[id]);
            ans.push_back(make_pair(p,helper[id]));
            st = 1;
        }
        helper[id] = p;
    }
    cout << "regular vertex ends"<<"\n";
}

/// handle start vertex
void triangulation :: handle_start_vertex(Pt p/**<given point*/)
{
     Pt p1 = get_nxt_Pt(p);
     cout <<"start vertex "<< p <<" "<< p1<<"\n";
     status.insert(indx[make_pair(p,p1)]);
     helper[indx[make_pair(p,p1)]] = p;
     cout << indx[make_pair(p,p1)]<<" "<< helper[indx[make_pair(p,p1)]]<<"\n";
     cout << "start ends"<<"\n";
}


/// handle end vertex
void triangulation :: handle_end_vertex(Pt p/**<given point*/)
{
    Pt p1 = get_nxt_Pt(p);
    int id = indx[make_pair(p,p1)];
    Pt p2 = helper[(id-1)%num__line];
    cout << "helper = "<< p2 <<"\n";
    if(check_type(p2) == merge_vertex)
    {
        d1->addEdge(p,p2);
        ans.push_back(make_pair(p,p2));
        st = 1;
    }
    status.erase(id-1);
}

/// handle split vertex
void triangulation :: handle_split_vertex(Pt p/**<given point*/)
{
    Pt p1 = get_nxt_Pt(p);
    int id = find_left(p);
    cout << "split vertex starts"<<"\n";
    cout << p <<" "<< helper[id] <<"\n";
    d1->addEdge(p,helper[id]);
    ans.push_back(make_pair(p,helper[id]));
    helper[id] = p;
    status.insert(indx[make_pair(p,p1)]);
    helper[indx[make_pair(p,p1)]] = p;
    cout << "split vertex ends"<<"\n";
}


/// handle merge vertex
void triangulation :: handle_merge_vertex(Pt p/**<given point*/)
{
    Pt p1 = get_nxt_Pt(p);
    int id = indx[make_pair(p,p1)];
    Pt p2 = helper[(id-1+num__line)%num__line];
    if(check_type(p2) == merge_vertex)
    {
        d1->addEdge(p,p2);
        ans.push_back(make_pair(p,p2));
        st = 1;
    }
    status.erase(id-1);
    id = find_left(p);
    if(check_type(helper[id]) == merge_vertex)
    {
	        d1->addEdge(p,helper[id]);
            ans.push_back(make_pair(p,helper[id]));
            st = 1;
    }
    helper[id] = p;
}

/// decompose the given polygon into Y-monotone polygon
void triangulation :: make_monotone(vector<Pt> v/**<given vector of point*/)
{
    priority_queue<Pt>q;
    for(int i=0;i<v.size();i++)
        q.push(v[i]);
    int cnt = 0;

    while(!q.empty())
    {
        Pt p = q.top();
        q.pop();
        if(vis[p] == 1)
        {
            if(cnt == 1)
              continue;
            else
            {
                cnt ++;
            }
              
        }
        int type = check_type(p);
        cout << p <<" "<< type <<"\n";
        if(type == start_vertex)
            handle_start_vertex(p);

        else if(type == end_vertex)
            handle_end_vertex(p);

        else if(type == split_vertex)
            handle_split_vertex(p);
        
        else if(type == merge_vertex)
            handle_merge_vertex(p);

        else if(type == regular_vertex)
            handle_regular_vertex(p);
    
    }
}


/// triangulate the given Y-monotone polygon
void triangulate()
{
    cout << "triangulate"<<"\n";
    stack<pair<Pt,int> > s;
    for(int i=0;i<mvector.size();i++)
        cout << mvector[i].first <<" "<< mvector[i].second <<"\n";
    s.push(mvector[0]);s.push(mvector[1]);
    int k = mvector.size();
    cout << mvector.size()-1<<"\n";
    for(int i = 2;i<(int)mvector.size()-1;i++)
    {
        cout <<s.top().first <<" "<< s.top().second <<" "<< mvector[i].first <<" "<< mvector[i].second <<"\n";
        if(s.top().second != mvector[i].second)
        {
            while(!s.empty())
            {
                pair<Pt,int> pp = s.top();
                s.pop();
                if(!s.empty())
                {
                    cout << "add edge between "<< pp.first <<" "<< mvector[i].first<<"\n";
                    ans.push_back(make_pair(pp.first,mvector[i].first));
                }
                else
                {
                    s.push(mvector[i-1]);
                    s.push(mvector[i]);
                    cout << pp.first <<" "<< mvector[i].first <<"\n";
                    break;
                }
                
            }
        }
        else
        {
            pair<Pt,int> u = s.top();
            s.pop();
            pair<Pt,int> prev = u;
            pair<Pt,int> v;
            while(!s.empty())
            {
                v = s.top();
                cout <<"u ="<< u.first <<" v= "<< v.first <<" "<< mvector[i].first <<"\n";
                int dir = orientation(u.first,v.first,mvector[i].first);
                int int_side = mvector[i].second;
                
                if(int_side != dir)
                {
                    cout << "add edge between "<< v.first <<" "<< mvector[i].first <<"\n";
                    ans.push_back(make_pair(v.first,mvector[i].first));
                    s.pop();
                    prev = v;
                }
                else
                {
                    break;
                }
            }
            s.push(prev);
            s.push(mvector[i]);
        }
        
    }
    s.pop();
    while(!s.empty())
    {
        pair<Pt,int> p = s.top();
        cout << p.first <<"\n";
        s.pop();
        if(s.empty())
            break;
        cout << "add edge between "<< mvector[k-1].first <<" "<< p.first <<"\n";   
    }
    
}


int main()
{
    int n;
    cin >> n;
	num__line = n-1;
    vector<Pt>v;
    double x,y;
    Pt lst;
    for(int i=1;i<=n;i++)
    {
        cin >> x >> y;
        v.push_back(Pt(x,y));
        lst = Pt(x,y);
    }
    vis[lst] = 1;
    for(int i=0;i<(int)v.size()-1;i++)
    {
        indx[make_pair(v[i],v[i+1])] = i;
        r_indx[i] = make_pair(v[i],v[i+1]);
    }
    d1 = DCEL(v);
    triangulation tri(&d1);
    tri.make_monotone(v);
    //cout << faces.size();
	for (auto i : d1.faces)
	{
		cout << i->start->origin << endl;
        mvector.clear();
		record * start = i->start;
		record * next = start;
        record * nstart = start;
        record *nnext = start;
        Pt minp = Pt(10000,1000);
        Pt maxp = Pt(0,0);
		do {
			cout <<"point "<< next->origin << endl;
            //mvector.push_back(next->origin);
            if(maxp < next->origin)
            {
                maxp = next->origin;
                nstart = next;
                nnext = next;
            }
            if(next->origin < minp)
            {
                minp = next->origin;
            }
			next = next->next;
		} while (!(start->origin == next->origin));
        cout << nstart->origin <<" "<< nnext->origin <<"\n";
        cout << maxp<<" "<< minp<<"\n";

        int fl;
        if(st)
          fl = 1;
        else
           fl = 2;
        do{
            cout << "npoint = "<< nnext->origin <<"\n";
            if(nnext->origin == minp)
            if(st)
                fl = 2;
            else
               fl = 1;    
            mvector.push_back(make_pair(nnext->origin,fl));
            nnext = nnext->next;
        }while(!(nstart->origin == nnext->origin));

        sort(mvector.rbegin(),mvector.rend());
       // for(int i=0;i<mvector.size();i++)
            //cout << mvector[i].first <<" "<< mvector[i].second<<"\n";
        
        triangulate();   
        for(int i=0;i<ans.size();i++)
            cout << ans[i].first <<" "<< ans[i].second <<"\n";
	}
}
