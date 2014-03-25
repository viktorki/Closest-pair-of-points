#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 20000, MAX_INT = 1000000000;
class Point
{
public:
	Point();
	Point(double, double);
	double getX() const;
	double getY() const;
	void setX(double);
	void setY(double);
	double distance(const Point&) const;
private:
	double x, y;
} queue[MAXN + 1];;
Point::Point()
{
	x = 0;
	y = 0;
}
Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}
double Point::getX() const
{
	return x;
}
double Point::getY() const
{
	return y;
}
void Point::setX(double x)
{
	this->x = x;
}
void Point::setY(double y)
{
	this->y = y;
}
double Point::distance(const Point &p) const
{
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
bool compare_x(const Point &p1, const Point &p2)
{
	return p1.getX() < p2.getX();
}
bool compare_y(const Point &p1, const Point &p2)
{
	return p1.getY() < p2.getY();
}
pair <Point, Point> find_closest_pair(Point points[], int left, int right)
{
	int mid, i, rear, front, j;
	double d1, d2, d3, m, temp3;
	pair <Point, Point> result, temp1, temp2;
	if (right - left == 1)
	{
		if (points[left].getY() > points[right].getY())
			swap(points[left], points[right]);
		return pair<Point, Point>(points[left], points[right]);
	}
	if (right - left == 2)
	{
		sort(points + left, points + right + 1, compare_y);
		d1 = points[left].distance(points[left + 1]);
		d2 = points[left].distance(points[right]);
		d3 = points[left + 1].distance(points[right]);
		if (d1 <= d2 && d1 <= d3)
			return pair<Point, Point>(points[left], points[left + 1]);
		if (d2 <= d1 && d2 <= d3)
			return pair<Point, Point>(points[left], points[right]);
		return pair<Point, Point>(points[left + 1], points[right]);
	}
	mid = (left + right) >> 1;
	temp1 = find_closest_pair(points, left, mid);
	temp2 = find_closest_pair(points, mid + 1, right);
	d1 = temp1.first.distance(temp1.second);
	d2 = temp2.first.distance(temp2.second);
	if (d1 < d2)
	{
		d3 = d1;
		result = temp1;
	}
	else
	{
		d3 = d2;
		result = temp2;
	}
	m = points[left].getX();
	for (i = left + 1; i <= mid; i++)
		if (m < points[i].getX())
			m = points[i].getX();
	rear = 0;
	for (i = mid + 1; i <= right; i++)
		if (points[i].getX() <= m + d3)
			queue[rear++] = points[i];
	queue[rear].setY(MAX_INT);
	front = 0;
	rear = 0;
	for (i = left; i <= mid; i++)
	{
		while (front < rear && queue[front].getY() >= points[i].getY() - d3)
			front++;
		while (queue[rear].getY() <= points[i].getY() + d3)
			rear++;
		for (j = front; j < rear; j++)
		{
			temp3 = points[i].distance(queue[j]);
			if (d3 > temp3)
			{
				d3 = temp3;
				result = pair<Point, Point>(points[i], queue[j]);
			}
		}
	}
	rear = 0;
	for (i = left; i <= mid; i++)
		if (points[i].getX() >= m - d3)
			queue[rear++] = points[i];
	queue[rear].setY(MAX_INT);
	front = 0;
	rear = 0;
	for (i = mid + 1; i <= right; i++)
	{
		while (queue[front].getY() >= points[i].getY() - d3 && front < rear)
			front++;
		while (queue[rear].getY() <= points[i].getY() + d3)
			rear++;
		for (j = front; j < rear; j++)
		{
			temp3 = points[i].distance(queue[j]);
			if (d3 > temp3)
			{
				d3 = temp3;
				result = pair<Point, Point>(points[i], queue[j]);
			}
		}
	}
	inplace_merge(points + left, points + mid + 1, points + right + 1, compare_y);
	return result;
}
pair <Point, Point> closest_pair(Point points[], int n)
{
	sort(points, points + n, compare_x);
	return find_closest_pair(points, 0, n - 1);
}
int main()
{
	int n, i;
	double x, y;
	Point points[MAXN];
	pair <Point, Point> result;
	while (1)
	{
		cout << "Points count: ";
		cin >> n;
		if (n < 2 || n > MAXN)
			cout << "Points count must be between 2 and " << MAXN << "!" << endl;
		else
			break;
	}
	cout << "Enter coordinates:" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> x >> y;
		points[i] = Point(x, y);
	}
	result = closest_pair(points, n);
	cout << fixed << setprecision(5);
	cout << endl;
	cout << "Closest pair:" << endl;
	cout << result.first.getX() << " " << result.first.getY() << endl;
	cout << result.second.getX() << " " << result.second.getY() << endl;
	cout << endl;
	cout << "Distance: " << result.first.distance(result.second) << endl;
	return 0;
}
