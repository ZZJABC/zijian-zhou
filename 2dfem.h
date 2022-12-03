#ifndef FEM2D_H_
#define FEM2D_H_

#include<iostream>
#include<vector>
using namespace std;

class Point
{
private:
	double x;
	double y;
	int num;      
	bool p;			//p = 1:first boundary condition exists
	bool q;			//q = 1:third boundary condition exists
public:
	Point() : x(0), y(0), num(0), p(0), q(0) {}
	Point(double x1, double y2, int num1, bool p1 = 0, bool q1 = 0): x(x1), y(y2), num(num1), p(p1), q(q1) {}
	~Point(){}
	void set_x(double x1) { x = x1; }
	void set_y(double y1) { y = y1; }
	void set_p(bool p1) { p = p1; }
	void set_q(bool q1) { q = q1; }
	double const get_x() { return x; }
	double const get_y() { return y; }
	double const get_p() { return p; }
	double const get_q() { return q; }
	int const get_num() { return num; }
	void const point_show() {
		cout << "Information of Point:" << endl;
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "num = " << num << endl;
		cout << "It " << (p == 1 ? "has " : "hasn't ") << "first boundary condition" << endl;
		cout << "It " << (q == 1 ? "has " : "hasn't ") << "third boundary condition" << endl;
	}
};

class Area
{
public:
	friend class Point;
	Point area_point[3];
	Area(Point p1, Point p2, Point p3, double ax1, double ay1, double b1, double f1);
	Area():ax(0), ay(0), be(0), fe(0) {}
	~Area(){}
	void set_point(Point p, int num = 0) { area_point[num] = p; }
	void set_ax(double ax1) { ax = ax1; }
	void set_ay(double ay1) { ay = ay1; }
	void set_b(double b1) { be = b1; }
	void set_f(double f1) { fe = f1; }
	double const get_ax() { return ax; }
	double const get_ay() { return ay; }
	double const get_b() { return be; }
	double const get_f() { return fe; }
	double const get_delta() { return delta; }
	double const get_point(vector<double> ans, double x, double y);
	vector<vector<double>> get_matrixK();
	vector<double> get_bi();
	void area_show();
private:
	double ax;
	double ay;
	double be;
	double fe;
	double a[3] =
	{ area_point[1].get_x() * area_point[2].get_y() - area_point[1].get_y() * area_point[2].get_x() ,
	  area_point[2].get_x() * area_point[0].get_y() - area_point[2].get_y() * area_point[0].get_x() ,
	  area_point[0].get_x() * area_point[1].get_y() - area_point[0].get_y() * area_point[1].get_x() };
	double b[3] =
	{ area_point[1].get_y() - area_point[2].get_y(),
	  area_point[2].get_y() - area_point[0].get_y(),
	  area_point[0].get_y() - area_point[1].get_y() };
	double c[3] =
	{ area_point[2].get_x() - area_point[1].get_x(),
	  area_point[0].get_x() - area_point[2].get_x(),
	  area_point[1].get_x() - area_point[0].get_x() };
	double delta = (b[0] * c[1] - b[1] * c[0]) / 2;
	vector<vector<double>> matrix_K;
	vector<double> bi;
};

Area::Area(Point p1, Point p2, Point p3, double ax1, double ay1, double b1, double f1) :area_point{ p1,p2,p3 }, ax(ax1), ay(ay1), be(b1), fe(f1) {}

void Area::area_show()
{
	cout << "Info of Area:" << endl;
	cout << "ax = " << ax << " ay = " << ay << " b = " << be << " f = " << fe << endl;
	cout << "Points of this area: " << endl;
	area_point[0].point_show();
	area_point[1].point_show();
	area_point[2].point_show();
	vector<vector<double>> matrix_K = get_matrixK();
	cout << "The matrix K is: " << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			cout << matrix_K[i][j] << " ";
			if (j == 2) cout << endl;
		}
	vector<double> bi = get_bi();
	cout << "The bi vector is: " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << bi[i] << " ";
	}
	cout << endl;
}

vector<vector<double>> Area::get_matrixK()
{
	vector<double> temp;
	vector<vector<double>>().swap(matrix_K);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			double K;
			if (i == j)
				K = (ax * b[i] * b[j] + ay * c[i] * c[j]) / (4 * delta) + delta * be / 6;
			else
				K = (ax * b[i] * b[j] + ay * c[i] * c[j]) / (4 * delta) + delta * be / 12;
			temp.push_back(K);
			if (j == 2) 
			{
				matrix_K.push_back(temp);
				vector<double>().swap(temp);
			}
		}
	return matrix_K;
}

vector<double> Area::get_bi() {
	vector<double>().swap(bi);
	for (int i = 0; i < 3; i++)
		bi.push_back(delta * fe / 3);
	return bi;
}

double const Area::get_point(vector<double> ans, double x, double y) {
	vector<double> N;
	N.push_back((a[0] + b[0] * x + c[0] * y) / (2 * delta));
	N.push_back((a[1] + b[1] * x + c[1] * y) / (2 * delta));
	N.push_back((a[2] + b[2] * x + c[2] * y) / (2 * delta));
	return (N[0] * ans[area_point[0].get_num()] + N[1] * ans[area_point[1].get_num()] + N[2] * ans[area_point[2].get_num()]);
}
#endif
