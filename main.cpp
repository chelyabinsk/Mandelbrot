#include <iostream>
#include <fstream>
#include <string>
#include <complex>
#include <vector>

using namespace std;

vector<double> pointsx;
vector<double> pointsy;

class Mandelbrot
{
protected:
	complex<double> c;
	unsigned int numberofitterations;
public:
	Mandelbrot(complex<double> C, int Numberofitterations) :
		c(C), numberofitterations(Numberofitterations)
	{ /* Constructor*/
	}

	bool check()
	{
		complex<double> ztmp;

		for (int i = 0; i <= numberofitterations; i++)
		{
			ztmp = (ztmp * ztmp) + c;
			if (abs(ztmp) > 2)
				return false;
		}
		return true;
	}
};

class Square
{
protected:
	double xmin, xmax, ymin, ymax;
	unsigned int level;
	string name;

public:
	Square(double xMin, double xMax, double yMin, double yMax, string nam, unsigned int lvl) :
		xmin(xMin), xmax(xMax), ymin(yMin), ymax(yMax), name(nam), level(lvl)
	{
		// Constructor

		double length = ymax - ymin;

		double xhalfpoint = xmin + length / 2;
		double yhalfpoint = ymin + length / 2;

		double minsize = 0.01; // Should be enough for 1920x1080 0.002

							   //cout << level << endl;

							   // If can't spilt further into smaller squares, just do one point test
							   // Works well
		if (length <= minsize)
		{
			complex<double> c(xmin, ymin);
			Mandelbrot m(c, 80);

			if (m.check() == 1)
			{
				if (ymin == 0)
				{
					pointsx.push_back(xmin);
					pointsy.push_back(ymin);
				}
				else
				{
					pointsx.push_back(xmin);
					pointsy.push_back(ymin);

					pointsx.push_back(xmin);
					pointsy.push_back(ymax * -1);

				}

			}
		}

		// Check if can split into 4 more squares			
		else if (length > minsize)
		{


			Square  square1(xmin, xhalfpoint, ymin, yhalfpoint, "square1", level + 1);
			Square  square2(xhalfpoint, xmax, ymin, yhalfpoint, "square2", level + 1);
			Square  square3(xmin, xhalfpoint, yhalfpoint, ymax, "square3", level + 1);
			Square  square4(xhalfpoint, xmax, yhalfpoint, ymax, "square4", level + 1);
		}

	}

};


int main()
{
	double xmin, xmax, ymin, ymax;
	unsigned int level;
	string name;

	cout << "xmin: "; cin >> xmin;
	cout << "xmax: "; cin >> xmax;
	cout << "ymin: "; cin >> ymin;
	cout << "ymax: "; cin >> ymax;

	Square s(xmin, xmax, ymin, ymax, "First", 0);

	cout << "x: " << pointsx.size() << endl;
	cout << "y: " << pointsy.size() << endl;

	// Open .csv file

	ofstream myFile("output.csv");
	if (myFile.is_open())
	{
		for (int i = 0; i <= pointsx.size(); i++)
		{
			myFile << pointsx[i] << "," << pointsy[i] << endl;
		}
		myFile.close();
	}
	else cout << "Can't open .csv file";

	cin;
}