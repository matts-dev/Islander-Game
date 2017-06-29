#include<cmath>
#include "Utility.h"

bool ee::utility::mxb::collision(const Rect& first, const Rect& second)
{
	//create segments based on the points of the rectangle
	std::vector<Segment> rect1;
	std::vector<Segment> rect2;
	rectToSegments(first, rect1);
	rectToSegments(second, rect2);

	//make sure that no segments overlap
	for (Segment& seg1 : rect1) {
		for (Segment& seg2 : rect2) {
			if (segmentsIntersect(seg1, seg2)) {
				return true;
			}
		}
	}
	return rectangleEnclosed(first, second);
}

bool ee::utility::mxb::rectToSegments(const Rect & points, std::vector<Segment>& segBuffer)
{
	segBuffer.clear();
	//for (int i = 0; i < 4; ++i) {
	//	segBuffer.push_back(Segment());
	//} //TODO delete this if not necessary
	segBuffer.resize(4);

	bool ret = createSegment(points.pntTopLeft, points.pntTopRight, segBuffer[0]);
	ret &= createSegment(points.pntTopRight, points.pntBottomRight, segBuffer[1]);
	ret &= createSegment(points.pntBottomRight, points.pntBottomLeft, segBuffer[2]);
	ret &= createSegment(points.pntBottomLeft, points.pntTopLeft, segBuffer[3]);

	return ret;
}

bool ee::utility::mxb::createSegment(const Point & pnt1, const Point & pnt2, Segment & segBuffer)
{
	bool ret = false;
	ret = createLine(pnt1, pnt2, segBuffer.line);
	segBuffer.minX = pnt1.x < pnt2.x ? pnt1.x : pnt2.x;
	segBuffer.maxX = pnt1.x > pnt2.x ? pnt1.x : pnt2.x;
	return ret;
}

bool ee::utility::mxb::createLine(const Point& pnt1, const Point& pnt2, Line& bufferLine)
{
	float rise = pnt1.y - pnt2.y;
	float run = pnt1.x - pnt2.x;
	if (!floatIsZero(run)) {
		bufferLine.slope = rise / run;

		//y = mx + b; b = y - mx; //either point can be substituted into for y and x
		bufferLine.intercept = pnt1.y - bufferLine.slope * pnt1.x;
		return true;
	}
	return false;
}

bool ee::utility::mxb::segmentsIntersect(const Segment& seg1, const Segment& seg2)
{
	Point interPnt(0, 0);
	if (lineIntersects(seg1.line, seg2.line, interPnt)){
		return valueInRange(interPnt.x, seg1.minX, seg2.maxX) 
			&& valueInRange(interPnt.y, seg2.minX, seg2.maxX);
	}
	return false;
}

bool ee::utility::mxb::lineIntersects(const Line& line1, const Line& line2, Point & bufferForResult)
{
	// uses slope intercept form of lines to determine if intersections occur (y = mx + b)
	// the intersection point of two lines is found by setting the two line equations equal to each other (mx + b = wx + d) and solving for X
	// y can then be be calculated using either of the two line formulas and the found x value 
	//
	// mx + b = wx + d
	// mx - wx = d - b
	// x (m - w) = d - b
	// x = (d - b) / (m - w)    //divide by zero check needed

	//----------------------------------------------------------------------------------------

	//line1 = wx + d; line2 = mx + b
	float diffIntercept = line1.intercept - line2.intercept;
	float diffSlope = line2.slope - line1.slope;

	//ensure diff slope isn't zero, diff slope zero means lines are parallel without any intersection (also do not want to divide by 0)
	if (std::abs(diffSlope) >= 0.0001){
		//non parallel slopes mean there is an intersection!
		float x = diffIntercept / diffSlope;
		float y = x * line1.slope + line1.intercept;
		bufferForResult.x = x;
		bufferForResult.y = y;
		return true;
	}
	return false;
}

void ee::utility::mxb::vector2fToPnt(const sf::Vector2f & vec2, Point & pointToUpdate)
{
	pointToUpdate.x = vec2.x;
	pointToUpdate.y = vec2.y;
}

bool ee::utility::mxb::rectangleEnclosed(const Rect & first, const Rect & second)
{
	//TODO implement, using width/height, a check to determine if any point is 
	//within the hypotenuse distance (the angle between the furthest points in a rectangle)
	//if a point is within this distance to all other points, then it is contained within the rectangle 
	//eg 10x10 sqaure, if a point is 5 away from all 4 points, then it is contained in the sqaure
	//NOTE: since the intersections are checked first, I may only need to write a function to 
	//check an individual point (since there cannot be any points within or points outside)
	return false;
}

bool ee::utility::floatIsZero(const float value, const float delta)
{
	return std::abs(value) < delta;
}
