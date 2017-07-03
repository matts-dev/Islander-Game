#pragma once
#include<vector>
#include<SFML/System.hpp>


namespace ee {
	/** A class that houses utility functions */
	namespace utility
	{
		template<typename T>
		bool valueInRange(const T value, const T min, const T max);

		bool floatIsZero(const float value, const float delta = 0.00001f);

		//collision using slope intercept form
		namespace mxb {
			/** Basic point class defined by X and Y coordinate*/

			struct Point {
				float x = 0;
				float y = 0;
				Point(float x = 0, float y = 0) : x(x), y(y) {}
			};

			/** Rectangled defined in terms of points */
			struct Rect {
				Point pntTopLeft;
				Point pntTopRight;
				Point pntBottomRight;
				Point pntBottomLeft;
				Rect() : pntTopLeft(), pntTopRight(), pntBottomRight(), pntBottomLeft() {}
			};

			/** slope intercept line */
			struct Line {
				float slope;
				union {
					float intercept;	//only a valid value if isVertical is false
					float xValue;		//only a valid value if isVertical is true
				};
				bool isVertical = false;
			};

			/** A line within a given x range*/
			struct Segment {
				Line line;
				//special line case (vertical) prevent proper point calculation from line
				//points intentionaly decoupled from each other,
				float minX;
				float maxX;

				//for vertical line comparison 
				float minY;
				float maxY;
			};

			enum class LineStatus : sf::Int8{  //TODO currently debugging, but when done change this to std::uint8 (cstdint.h)
				PARALLEL,
				INTERSECT,
				ONE_VERTICAL_LINE,
				INVALID,
			};

			bool collision(const Rect& first, const Rect& second); //TODO update const correctness
			bool rectToSegments(const Rect& points, std::vector<Segment>& segBuffer);
			bool createSegment(const Point& pnt1, const Point& pnt2, Segment& segBuffer);
			bool createLine(const Point& pnt1, const Point& pnt2, Line& bufferLine);
			bool segmentsIntersect(const Segment& seg1, const Segment& seg2);
			bool parallelSegmentsOverlap(const Segment& seg1, const Segment& seg2);
			bool verticalLineIntersectionTest(const Segment& seg1, const Segment& seg2, const Point& intersectionPnt);
			bool lineIntersects(const Line& line1, const Line& line2, Point& bufferForResult, LineStatus& status);

			void vector2fToPnt(const sf::Vector2f & vec2, Point & pointToUpdate);

			bool rectangleEnclosed(const Rect& first, const Rect& second);
		}
	}
}

#include"Utility.inl"
