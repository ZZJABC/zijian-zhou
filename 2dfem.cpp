#include "2dfem.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>



int main()
{
	using namespace std;
	//step 1: Area Discrete

	int point_num = 12;                                              //Point number 
	int area_num = 12;											    //Area number
	int a = 0;
	vector<Area> areaarry;									   //define area vector
	vector <vector<int>> Narry(3, vector<int>(area_num));     //define N vector
	cout << "Default mode?<1:yes/0:no>: " << flush;
	cin >> a;
	if (a == 1)                                               // default data
	{
		
		vector<Point> pointarry;                                   //define point vector
		
		
		
		pointarry.push_back(Point(0, 0, 0));
		pointarry.push_back(Point(0.5, 0, 1));
		pointarry.push_back(Point(1, 0, 2));
		pointarry.push_back(Point(0.08, 0.56, 3));
		pointarry.push_back(Point(0.58, 0.56, 4));
		pointarry.push_back(Point(1.08, 0.56, 5));
		pointarry.push_back(Point(0.17, 1.19, 6));
		pointarry.push_back(Point(0.67, 1.19, 7));
		pointarry.push_back(Point(1.17, 1.19, 8));
		pointarry.push_back(Point(0.25, 1.75, 9));
		pointarry.push_back(Point(0.75, 1.75, 10));
		pointarry.push_back(Point(1.25, 1.75, 11));

		double ax = 1, ay = 1, b = 0, f = 1;

		Narry[0][0] = 0;
		Narry[1][0] = 1;
		Narry[2][0] = 3;

		Narry[0][1] = 1;
		Narry[1][1] = 4;
		Narry[2][1] = 5;

		Narry[0][2] = 1;
		Narry[1][2] = 2;
		Narry[2][2] = 4;

		Narry[0][3] = 2;
		Narry[1][3] = 5;
		Narry[2][3] = 4;

		Narry[0][4] = 3;
		Narry[1][4] = 4;
		Narry[2][4] = 6;

		Narry[0][5] = 4;
		Narry[1][5] = 7;
		Narry[2][5] = 6;

		Narry[0][6] = 4;
		Narry[1][6] = 5;
		Narry[2][6] = 7;

		Narry[0][7] = 5;
		Narry[1][7] = 8;
		Narry[2][7] = 7;

		Narry[0][8] = 6;
		Narry[1][8] = 7;
		Narry[2][8] = 9;

		Narry[0][9] = 7;
		Narry[1][9] = 10;
		Narry[2][9] = 9;
		
		Narry[0][10] = 7;
		Narry[1][10] = 8;
		Narry[2][10] = 10;

		Narry[0][11] = 8;
		Narry[1][11] = 11;
		Narry[2][11] = 10;

		
			
		areaarry.push_back(Area(pointarry[0], pointarry[1], pointarry[3], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[1], pointarry[4], pointarry[3], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[1], pointarry[2], pointarry[4], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[2], pointarry[5], pointarry[4], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[3], pointarry[4], pointarry[6], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[4], pointarry[7], pointarry[6], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[4], pointarry[5], pointarry[7], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[5], pointarry[8], pointarry[7], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[6], pointarry[7], pointarry[9], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[7], pointarry[10], pointarry[9], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[7], pointarry[8], pointarry[10], ax, ay, b, f));
		areaarry.push_back(Area(pointarry[8], pointarry[11], pointarry[10], ax, ay, b, f));
		}
	
	else
	{

		cout << "How many points the question have?: " << flush;
		cin >> point_num;

		cout << "How many area the question have?: " << flush;
		cin >> area_num;

		vector<Point> pointarry;                                   //define point vector
		//vector<Area> areaarry;									   //define area vector
		//vector <vector<int>> Narry(3, vector<int>(area_num));     //define N vector

		for (int i = 0; i < point_num; i++)                        //input points' info
		{
			double x_temp;                                         //store the x_axis
			double y_temp;										   //store the y_axis
			cout << "Please input point[" << i << "]'s cordination: " << flush;
			cin >> x_temp >> y_temp;
			pointarry.push_back(Point(x_temp, y_temp, i));

			//pointarry[i].point_show();
		}

		int def = 0;											  //default mode
		double ax, ay, b, f;

		cout << "Does ax, ay, b and f unchanged?: <1:yes/0:no>" << flush;
		cin >> def;
		if (def == 1)//All area have same equation
		{
			cout << "Please input the default ax ay b and f: " << flush;
			cin >> ax >> ay >> b >> f;
		}

		for (int i = 0; i < area_num; i++)
		{
			int N1, N2, N3;
			Area area_temp;
			cout << "which three points area[" << i << "] have?(in CCW): " << flush;
			cin >> N1 >> N2 >> N3;
			Narry[0][i] = N1;
			Narry[1][i] = N2;
			Narry[2][i] = N3;

			if (def != 1)
			{
				cout << "Please input ax, ay, b, and f: " << flush;
				cin >> ax >> ay >> b >> f;

				area_temp = Area(pointarry[N1], pointarry[N2], pointarry[N3], ax, ay, b, f);
			}
			else
			{
				area_temp = Area(pointarry[N1], pointarry[N2], pointarry[N3], ax, ay, b, f);
			}
			areaarry.push_back(area_temp);
		}
	}

	////information for matrix N
	cout << "The Matrix N:" << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j <area_num; j++)
		{
			cout << Narry[i][j] << " ";
			if (j == area_num - 1) cout << endl;
		}
			

// step 2:Unit Interpolation	
	vector <vector<double>> K(point_num, vector<double>(point_num,0));  //the total K matrix
	vector<double> B(point_num, 0);										// the total b matrix
	

	vector <vector<double>> K_temp(3, vector<double>(3));
	vector <double> B_temp(3);
	 for (int i = 0; i < area_num; i++)
	{
		B_temp = areaarry[i].get_bi();
		K_temp = areaarry[i].get_matrixK();

		cout << "[" << i << "]" << "The matrix K_temp is :"  << endl;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				cout.flags(ios::left);
				cout.width(10);
				cout << K_temp[i][j];

				if (j == 2) cout << endl;
			}


		for (int j = 0; j < 3; j++)
		{
			B[Narry[j][i]] += B_temp[j];
			for (int k = 0; k < 3; k++)
			{
				K[Narry[j][i]][Narry[k][i]] += K_temp[j][k];
				
			}
		}
		vector<vector<double>>().swap(K_temp);
		vector<double>().swap(B_temp);
	}


// step3: Add Dirichlet Conditions
	 int di_num;
	 double p;
	 int serial_num;
	 if (a == 1)
	 {
		 K[0][0] = pow(10, 70);
		 B[0] = 0 * pow(10, 70);

		 K[1][1] = pow(10, 70);
		 B[1] = 0 * pow(10, 70);

		 K[2][2] = pow(10, 70);
		 B[2] = 0 * pow(10, 70);

		 K[9][9] = pow(10, 70);
		 B[9] = 10 * pow(10, 70);

		 K[10][10] = pow(10, 70);
		 B[10] = 10 * pow(10, 70);

		 K[11][11] = pow(10, 70);
		 B[11] = 10 * pow(10, 70);
	 }
	 else
	 {
		 cout << "How many points have dirichlet conditions?: " << flush;
		 cin >> di_num;
		 while (di_num > 0 && di_num < point_num)
		 {
			 cout << "[" << di_num << "] Please input the point's serial number and the value of p: " << flush;
			 cin >> serial_num >> p;
			 K[serial_num][serial_num] = pow(10, 70);
			 B[serial_num] = p * pow(10, 70);
			 di_num--;
		 }
	 }

	 // Show the final K matrix and B matrix
	cout << "The matrix K is: " << endl;
	for (int i = 0; i < point_num; i++)
		for (int j = 0; j < point_num; j++)
		{
			cout.flags(ios::left);
			cout.width(12);
			//cout << setiosflags(ios::fixed);
			cout  <<  K[i][j];
			
			if (j == point_num - 1) cout << endl << endl;
		}
	cout << "The b is: " << endl;
		for (int j = 0; j < point_num; j++)
		{
			cout.flags(ios::left);
			cout.width(10);
			cout << B[j];
		}
		cout << "<<<" << endl;
		cout << "<<<" << endl;
		cout << "<<<" << endl;

//step4: Solve Equation using Gauss-Seidel Method
		double e = pow(10, -5);                 // Iterative Error
		int ite_num = 0;						 // Iterative number
		vector <double> res_0(point_num, 0);     // Initial Solution vector
		double e_now = 1;                        // Error at Present
		double res_x = 0;					     // Store the last solution
		cout << endl;
		cout << "[" << ite_num << "]" << "Current solution: {0}" << endl;
		while (e_now > e && ite_num < 50)
		{
			e_now = 0;
			ite_num++;
			cout << "[" << ite_num << "]" << "Current solution: ";
			for (int i = 0; i < point_num; i++)
			{ 
				res_x = res_0[i];
				res_0[i] = B[i] / K[i][i];
				for (int j = 0; j < i; j++)
				{
					res_0[i] -= K[i][j] * res_0[j] / K[i][i];
				}
				for (int j = i + 1; j < point_num; j++)
				{
					res_0[i] -= K[i][j] * res_0[j] / K[i][i];
				}
				cout.flags(ios::left);
				cout.width(10);
				cout << res_0[i] << " ";
				e_now += abs(res_0[i] - res_x);
			}
			cout << endl;
			cout << "Error: " << e_now << endl;	
		}
		cout << "<<<" << endl;
		cout << "<<<" << endl;
		cout << "<<<" << endl;


//step 5: input x y and get solution
		double x;
		double y;
		int m;
		cout << "Which area does the point in?(start from 0): " << flush;
		cin >> m;
		cout << "Please input x and y of the point(-1 -1 to quit): " << flush;
		cin >> x >> y;
		while (x != -1 || y != -1)
		{
			cout << "The solution is: " << areaarry[m].get_point(res_0,x,y) << endl;
			cout << "Which area does the point in?(start from 0): " << flush;
			cin >> m;
			cout << "Please input x and y of the point(-1 -1 to quit): " << flush;
			cin >> x >> y;
		}
	return 0;
}