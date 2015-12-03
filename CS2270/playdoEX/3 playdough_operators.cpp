#include <iostream>
using namespace std;

class Playdough {
  public:
  	Playdough();
    Playdough(int v, string c);
    friend ostream &operator<<(ostream &os, const Playdough& p);
    friend Playdough operator+(const Playdough& p1, const Playdough& p2);
  private:
    int volume;
    string color;
};

Playdough::Playdough() {
	// Do nada
}

Playdough::Playdough(int v, string c) {
	(*this).volume = v;
	(*this).color = c;
}

ostream &operator<<(ostream &os, const Playdough& p) {
	os << "The Playdough has a volume of: " << p.volume << endl;
	os << "The Playdough has a color of: " << p.color << endl;
}

Playdough operator+(const Playdough& p1, const Playdough& p2)
{
	Playdough resultantDough = Playdough();
	resultantDough.volume = p1.volume + p2.volume;
	resultantDough.color = "pink"; // I could do if-statements and mix colors, but we're just going to statically set this to pink.
	return resultantDough;
}

int main() {
	Playdough redDough = Playdough(3, "red");
	cout << redDough;
	
	Playdough whiteDough = Playdough(3, "white");
	cout << whiteDough;

	Playdough result = redDough + whiteDough;
	cout << result;
}