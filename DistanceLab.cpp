#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const string MENU = "\n\n***********************************************\n"
"********************* MENU ********************\n"
"***********************************************\n"
"* *\n"
"* *\n"
"* 1) Enter city Information *\n"
"* 2) Calculate distance between two cities *\n"
"* 3) Print All cities *\n"
"* 4) Quit *\n"
"* *\n"
"* *\n"
"***********************************************\n";
class Point
{
public:
	Point(void);
	void CityCoord(void);
	double Dist(const Point& other) const;
private:
	double x, y;
	friend ostream& operator << (ostream& os, const Point& p)
	{
		return os << p.x << ", " << p.y;
	}
};
Point::Point(void)
{
	x = y = 0.0;
}
void Point::CityCoord(void)
{
	char comma;
	for (; ; )
	{
		cout << "Enter point x,y (Please enter comma also) : ";
		cin >> x >> comma >> y;
		if (cin.good()) break;
		cin.clear();
		cin.sync();
		cout << "\b!!!!Only Numbers Please!!!!\n";
	}
	string dummy;
	getline(cin, dummy);
}
double Point::Dist(const Point & other) const
{
	return sqrt(pow(x - other.x, 2.0) + pow(other.y - y, 2.0));
}
class City
{
public:
	void CityCoord_cityname()
	{
		cout << "Please enter city name: " << flush;
		getline(cin, cityname);
	}
	void CityCoord_p()
	{
		p.CityCoord();
	}
	string get_cityname() const { return cityname; }
	double Dist(const City& other) const
	{
		return p.Dist(other.p);
	}
private:
	string cityname;
	Point p;
	friend ostream& operator << (ostream& os, const City& c)
	{
		return os << c.cityname << ", (" << c.p << ")";
	}
};
int CityCoordChar(const string & msg)
{
	cout << msg << flush;
	string reply;
	getline(cin, reply);
	if (reply.size())
		return reply[0];
	return 0;
}
void CityCoordCity(vector < City > & c)
{
	City cty;
	cty.CityCoord_cityname();
	cty.CityCoord_p();
	c.push_back(cty);
}
void showDist(const vector < City > & c)
{
	City a, b;
	a.CityCoord_cityname();
	vector < City > ::const_iterator it, ita, itb;
	ita = c.end();
	for (it = c.begin(); it != c.end(); ++it)
	{
		if (it->get_cityname() == a.get_cityname())
		{
			ita = it;
			break;
		}
	}
	if (ita == c.end())
	{
		cout << a.get_cityname() << " NOT found.\n";
		return;
	}
	b.CityCoord_cityname();
	itb = c.end();
	for (it = c.begin(); it != c.end(); ++it)
	{
		if (it->get_cityname() == b.get_cityname())
		{
			itb = it;
			break;
		}
	}
	if (itb == c.end())
	{
		cout << b.get_cityname() << " NOT found.\n";
		return;
	}
	cout << "\nThe distance from " << a.get_cityname()
		<< " to " << b.get_cityname()
		<< " is " << ita->Dist(*itb) << endl << endl;
}
void print_info_all(const vector < City >& c)
{
	cout << "\nAll cites listed:\n";
	vector < City > ::const_iterator it;
	for (it = c.begin(); it != c.end(); ++it) cout << *it << endl;
	cout << endl;
}
int main()
{
	vector< City > cities;
	int reply = 0;
	do
	{
		cout << MENU << flush;
		reply = CityCoordChar("\nEnter your choice (1..4) : ");
		switch (reply)
		{
		case '1': CityCoordCity(cities); break;
		case '2': showDist(cities); break;
		case '3': print_info_all(cities); break;
		case '4': cout << "\nExiting... Thank you for using program.\n\n\n"; break;
		default: cout << "\nInvalid entry. Please try again.\n";
		}
	} while (reply != '4');
}