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

	//4 comparions rather than 2
	//segBuffer.minX = pnt1.x < pnt2.x ? pnt1.x : pnt2.x;
	//segBuffer.maxX = pnt1.x > pnt2.x ? pnt1.x : pnt2.x;
	////y is needed for special case in vertical parallel lines
	//segBuffer.maxY = pnt1.y > pnt2.y ? pnt1.y : pnt2.y;
	//segBuffer.minY = pnt1.y < pnt2.y ? pnt1.y : pnt2.y;

	if (pnt1.x > pnt2.x) {
		segBuffer.maxX = pnt1.x;
		segBuffer.minX = pnt2.x;
	}
	else {
		segBuffer.maxX = pnt2.x;
		segBuffer.minX = pnt1.x;
	}

	//y is needed for special case in vertical parallel lines
	if (pnt1.y > pnt2.y) {
		segBuffer.maxY = pnt1.y;
		segBuffer.minY = pnt2.y;
	}
	else {
		segBuffer.maxY = pnt2.y;
		segBuffer.minY = pnt1.y;
	}

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
	else if (!floatIsZero(rise)) {
		//run is zero, but rise isn't zero; line is vertical
		//the line can be defined as an x value, for example: x = 5;
		bufferLine.isVertical = true;
		bufferLine.xValue = pnt1.x;	//either pnt1 or pnt2's x value is applicable, since run's zero the values are the same.
		return true;
	}
	return false;
}

bool ee::utility::mxb::segmentsIntersect(const Segment& seg1, const Segment& seg2)
{
	Point interPnt(0, 0);

	LineStatus status;
	if (lineIntersects(seg1.line, seg2.line, interPnt, status)) {
		switch (status) {
			case LineStatus::INTERSECT:
				return valueInRange(interPnt.x, seg1.minX, seg1.maxX) && valueInRange(interPnt.x, seg2.minX, seg2.maxX);
			case LineStatus::PARALLEL:
				return parallelSegmentsOverlap(seg1, seg2);
			case LineStatus::ONE_VERTICAL_LINE: //perfectly vertical lines are not best defined in mx + b form, but x = constant form; special case to handle this
				return verticalLineIntersectionTest(seg1, seg2, interPnt);
			default:
				return false;
		}
	}
	return false;
}

#define NOT_ZERO_THRESHOLD 0.0001f
/**
 * This function assumes that the segments are parallel
 * @Invariant: segments are parallel
 */
bool ee::utility::mxb::parallelSegmentsOverlap(const Segment & seg1, const Segment & seg2)
{
	//invarient says lines are parallel, therefore if 1 line is vertical, so is the other
	bool linesAreVertical = std::abs(seg1.minX - seg1.maxX) < NOT_ZERO_THRESHOLD;
	if (linesAreVertical) {
		//vertical liens may have different x values, check that these parallel lines could potentially overlap
		//not using a comparison of the line field since vertical lines are not well represented with mx + b form 
		if (std::abs(seg1.minX - seg2.minX) < NOT_ZERO_THRESHOLD) {
			//lines can overlap, check if y values have any overlap
			return seg1.maxY > seg2.minY || seg2.maxY > seg1.minY;
		}
		else {
			//lines can not overlap, since they're vertical theses lines cannot intersect
			return false;
		}
	}
	else {
		//lines are parallel (by invariant) and have been shown not to be vertical
		if (std::abs(seg1.line.intercept - seg1.line.intercept) < NOT_ZERO_THRESHOLD) {
			//intercepts are same, therefore the range of the line needs to be checked for an overlap
			return seg1.maxX > seg2.minX || seg2.maxX > seg1.minX;
		}
		else {
			//intercepts are not the same, therefore the lines are parallel but cannot be overlapping
			return false;
		}
	}
	return false;
}

/**
 * This function should not be used to determine if two parallel segements intersect, only one segment must be vertical. 
 * Use the function designed for parallel lines to determine if two vertical parallel segments intersect.
 * @invariant: Assumes at least 1 is vertical
 * @invariant: Assumes no more than 1 line is vertical 
 */
bool ee::utility::mxb::verticalLineIntersectionTest(const Segment & seg1, const Segment & seg2, const Point& intersectionPnt)
{
	const Segment* verticalSeg = nullptr;
	const Segment* nonVertSeg = nullptr;

	if (seg1.line.isVertical) {
		verticalSeg = &seg1;
		nonVertSeg = &seg2;
	}
	//else {//assuming seg2.line.isVertical is true, preventing extra condition check 
	else if (seg2.line.isVertical){ //less efficient to do this check, but makes program less fragile
		verticalSeg = &seg2;
		nonVertSeg = &seg1;
	}
	else {
		//neither line is vertical, abort!
		return false;
	}

	bool ret = valueInRange(intersectionPnt.y, verticalSeg->minY, verticalSeg->maxY);
	ret &= valueInRange(intersectionPnt.x, nonVertSeg->minX, nonVertSeg->maxX);

	return ret;
}

/** 
 *  @return true if lines intersect
 */
bool ee::utility::mxb::lineIntersects(const Line& line1, const Line& line2, Point & bufferForResult, LineStatus& status)
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
	if (std::abs(diffSlope) >= 0.0001) {
		//non parallel slopes mean there is an intersection!
		float x = diffIntercept / diffSlope;
		float y = x * line1.slope + line1.intercept;
		bufferForResult.x = x;
		bufferForResult.y = y;
		status = LineStatus::INTERSECT;
		return true;
	}
	//if either are vertical, but not both vertical 
	else if (line1.isVertical || line2.isVertical && !(line1.isVertical && line2.isVertical)) {
		//vertical lines will have a zero slope, which can make lines appear parallel when they're actually perpendicular
		if (line1.isVertical) {
			//line1 is defined entirely by an x value, thus it must be the x value of the intersection
			bufferForResult.x = line1.xValue; 

			//determine y by substituting in the found 	//this is why both lines must not be vertical, this would not be mathematically correct
			bufferForResult.y = line2.slope * bufferForResult.x + line2.intercept; 
		}
		else {
			//line2 is the vertical line, see above branch for documentation
			bufferForResult.x = line2.xValue;
			bufferForResult.y = line1.slope * bufferForResult.x + line1.intercept;
		}
		status = LineStatus::ONE_VERTICAL_LINE;
		return true;
	}
	else {
		//if slopes are both zero, then the slopes are the same, simply check if y intercepts are same to determine if lines are the same
		status = LineStatus::PARALLEL;
		return std::abs(diffIntercept) <= 0.0001; //y intercept are the same when there difference is zero 
	}
	status = LineStatus::INVALID;
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
