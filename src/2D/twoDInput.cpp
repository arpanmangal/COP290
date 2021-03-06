#include <iostream>
#include "include/2D/twoDInput.h"
#include "include/2D/Edge.h"
#include "include/2D/twoDPoint.h"
#include <fstream>
#include "include/2D/twoDProjection.h"
#include "include/2D/twoDProjectionView.h"

using namespace std;

// Constructor and Destructor
twoDInput::twoDInput()
{
    // empty constructor
}

twoDInput::~twoDInput()
{
    // empty destructor
}

// TODO: Check duplicate Edge
void twoDInput::addEdge(int start, int end)
{
    int pointSet_size = pointSet.size();

    if (start < 0 || end < 0 || start >= pointSet_size || end >= pointSet_size)
    {
        cout << "Point set size is " << pointSet_size << " and you are entering " << start << " and " << end<< std::endl;
    }
    else
    {
        // valid points start and end
        edgeSet.push_back(new Edge(start, end));
    }
}

twoDProjectionView *twoDInput::getProjectionDrawing(const char * path)
{
    ifstream file;
    file.open(path, ios::in);
    if (!file)
    {
     cout<<"File not found\n";   
    }

    int number_of_views,number_of_points, number_of_edges;
    twoDProjection *frontview, *topview, *sideview;
    int start, end;
    float x, y;
    twoDPoint *point;

    file>>number_of_views;

    //reading frontview
    file >> number_of_points;
    for (int i = 0; i < number_of_points; i++)
    {
        file >> x >> y;
        point = new twoDPoint(x, y);
        pointSet.push_back(point);
    }

    
    if (number_of_points < 2)
    {
        cout << "\nGo Away! Too Less points !!" << std::endl;
        return nullptr;
    }

    file >> number_of_edges;
    for (int i = 0; i < number_of_edges; i++)
    {
        file >> start >> end;
        try
        {
            addEdge(start, end);
        }
        catch (std::string e)
        {
            // invalid edge

            cout << "Invalid Edge!!" << std::endl;
            continue;
        }
    }

    frontview = new twoDProjection();
    frontview->add_pointSet(pointSet);
    frontview->add_edgeSet(edgeSet);
    //frontview->printer();
    //std::cout<<"Added front view\n";

    //reading top view
    edgeSet = EdgeVector2D();
    pointSet = PointVector2D();

    file >> number_of_points;
    for (int i = 0; i < number_of_points; i++)
    {
        file >> x >> y;
        point = new twoDPoint(x, y);
        pointSet.push_back(point);
    }

    if (number_of_points < 2)
    {
        cout << "\nGo Away! Too Less points !!" << std::endl;
        return nullptr;
    }

    file >> number_of_edges;
    for (int i = 0; i < number_of_edges; i++)
    {
        file >> start >> end;
        try
        {
            addEdge(start, end);
        }
        catch (std::string e)
        {
            // invalid edge

            cout << "Invalid Edge!!" << std::endl;
            continue;
        }
    }

    topview = new twoDProjection();
    topview->add_pointSet(pointSet);
    topview->add_edgeSet(edgeSet);
    //topview->printer();
    //std::cout<<"Added top view\n";

    //reading side view
    if (number_of_views == 3)
    {
        edgeSet = EdgeVector2D();
        pointSet = PointVector2D();

        file >> number_of_points;
        cout<<pointSet.size()<<endl;
        for (int i = 0; i < number_of_points; i++)
        {
            file >> x >> y;
            point = new twoDPoint(y, x);
            pointSet.push_back(point);
        }
        
        int start, end;
        if (number_of_points < 2)
        {
            cout << "\nGo Away! Too Less points !!" << std::endl;
            return nullptr;
        }

        file >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            file >> start >> end;
            try
            {
                addEdge(start , end );
            }
            catch (std::string e)
            {
                // invalid edge
                cout << "Invalid Edge!!" << std::endl;
                continue;
            }
        }

        sideview = new twoDProjection();
        sideview->add_pointSet(pointSet);
        sideview->add_edgeSet(edgeSet);
        //sideview->printer();
        //cout<<"Added Side View\n";
    }
    else
    {
        sideview = NULL;
    }

    twoDProjectionView * retVal = new twoDProjectionView(frontview,topview,sideview);
    return retVal;
}
