#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 20000;
const double MAX_DOUBLE = 1000000000;
struct point
{
	int n;
	double x, y;
} p[MAXN], q[MAXN];
int n;
double d(point p1, point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
bool compare_x(point p1, point p2)
{
	return p1.x < p2.x;
}
bool compare_y(point p1, point p2)
{
	return p1.y < p2.y;
}
bool convex(point p1, point p2, point p3)
{
	return (p2.x - p1.x) * (p3.y - p2.y) >(p3.x - p2.x) * (p2.y - p1.y);
}
pair <point, point> closest_pair(int l, int r)
{
	int rear, i, front, j;
	double d1, d2, d3, m, temp3;
	pair <point, point> temp1, temp2, result;
	if (r - l == 1)
	{
		if (p[l].y > p[r].y)
			swap(p[l], p[r]);
		return pair<point, point>(p[l], p[r]);
	}
	if (r - l == 2)
	{
		sort(p + l, p + r + 1, compare_y);
		d1 = d(p[l], p[l + 1]);
		d2 = d(p[l], p[r]);
		d3 = d(p[l + 1], p[r]);
		if (d1 <= d2 && d1 <= d3)
			return pair<point, point>(p[l], p[l + 1]);
		if (d2 <= d1 && d2 <= d3)
			return pair<point, point>(p[l], p[r]);
		return pair<point, point>(p[l + 1], p[r]);
	}
	temp1 = closest_pair(l, l + r >> 1);
	temp2 = closest_pair((l + r >> 1) + 1, r);
	d1 = d(temp1.first, temp1.second);
	d2 = d(temp2.first, temp2.second);
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
	m = p[l].x;
	for (i = l + 1; i <= l + r >> 1; i++)
	if (m < p[i].x)
		m = p[i].x;
	rear = 0;
	for (i = (l + r >> 1) + 1; i <= r; i++)
	if (p[i].x <= m + d3)
		q[rear++] = p[i];
	q[rear].y = MAX_DOUBLE;
	front = 0;
	rear = 0;
	for (i = l; i <= l + r >> 1; i++)
	{
		while (q[front].y >= p[i].y - d3 && front < rear)
			front++;
		while (q[rear].y <= p[i].y + d3)
			rear++;
		for (j = front; j < rear; j++)
		{
			temp3 = d(p[i], q[j]);
			if (d3 > temp3)
			{
				d3 = temp3;
				result = pair<point, point>(p[i], q[j]);
			}
		}
	}
	rear = 0;
	for (i = l; i <= l + r >> 1; i++)
	if (p[i].x >= m - d3)
		q[rear++] = p[i];
	q[rear].y = MAX_DOUBLE;
	front = 0;
	rear = 0;
	for (i = (l + r >> 1) + 1; i <= r; i++)
	{
		while (q[front].y >= p[i].y - d3 && front < rear)
			front++;
		while (q[rear].y <= p[i].y + d3)
			rear++;
		for (j = front; j < rear; j++)
		{
			temp3 = d(p[i], q[j]);
			if (d3 > temp3)
			{
				d3 = temp3;
				result = pair<point, point>(p[i], q[j]);
			}
		}
	}
	inplace_merge(p + l, p + (l + r >> 1) + 1, p + r + 1, compare_y);
	return result;
}
int main()
{
	int i, j;
	pair <point, point> result;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p, p + n, compare_x);
	result = closest_pair(0, n - 1);
	printf("%.5lf %.5lf\n", result.first.x, result.first.y);
	printf("%.5lf %.5lf\n", result.second.x, result.second.y);
	printf("%.5lf\n", d(result.first, result.second));
	return 0;
}
