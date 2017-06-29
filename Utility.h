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
				float intercept;
			};

			/** A line within a given x range*/
			struct Segment {
				Line line;
				float minX;
				float maxX;
			};

			bool collision(const Rect& first, const Rect& second); //TODO update const correctness
			bool rectToSegments(const Rect& points, std::vector<Segment>& segBuffer);
			bool createSegment(const Point& pnt1, const Point& pnt2, Segment& segBuffer);
			bool createLine(const Point& pnt1, const Point& pnt2, Line& bufferLine);
			bool segmentsIntersect(const Segment& seg1, const Segment& seg2);
			bool lineIntersects(const Line& line1, const Line& line2, Point& bufferForResult);

			void vector2fToPnt(const sf::Vector2f & vec2, Point & pointToUpdate);

			bool rectangleEnclosed(const Rect& first, const Rect& second);
		}
	}
}

#include"Utility.inl"
