/**Defines interface for a 2D Projection drawing
Defines a drawing as a set of points and edges*/

//=================================
// include guard
#ifndef _twoDProjection_h
#define _twoDProjection_h

//=================================
// included dependencies
#include <vector>
class twoDPoint;
class twoDEdge;

typedef std::vector<twoDPoint *> PointVector2D;
typedef std::vector<twoDEdge *> EdgeVector2D;

class twoDProjection{
	private:
		PointVector2D PointSet;
		EdgeVector2D EdgeSet;
	public:
		twoDProjection(){}

		void add_pointSet(PointVector2D const & a);

		void add_edgeSet(EdgeVector2D const & a);

		friend class twoDProjectionView;
};

#endif