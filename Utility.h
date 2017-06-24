#pragma once
#include<vector>

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
				Point(float x, float y) : x(x), y(y) {}
			};

			/** Rectangled defined in terms of points */
			struct Rect {
				Point pnt1;
				Point pnt2;
				Point pnt3;
				Point pnt4;
				float rotation;
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

			bool collision(const Rect& first, const Rect& second);
			bool rectToSegments(const Rect& points, std::vector<Segment>& segBuffer);
			bool createSegment(const Point& pnt1, const Point& pnt2, Segment& segBuffer);
			bool createLine(const Point& pnt1, const Point& pnt2, Line& bufferLine);
			bool segmentsIntersect(const Segment& seg1, const Segment& seg2);
			bool lineIntersects(const Line& line1, const Line& line2, Point& bufferForResult);
		}
	}
}

#include"Utility.inl"
