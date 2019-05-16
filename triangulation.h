# include "DCEL.h"

/// class for triangulation of any given polygon
class triangulation
{
    public:
    DCEL * d1;
    void make_monotone(vector<Pt>);///<decompose into y-monotone polygon
    void triangulate_monotone_polygon();///<triangulate y-monotone polygon
    int check_type(Pt);///< gives the type of given point
    triangulation(DCEL*);
    void handle_start_vertex(Pt);///<handles start vertex
    void handle_end_vertex(Pt);///<handles end vertex
    void handle_split_vertex(Pt);///<handles split vertex
    void handle_merge_vertex(Pt);///<handles merge vertex
    void handle_regular_vertex(Pt);///<handles regular vertex
};