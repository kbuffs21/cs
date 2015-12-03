#include <iostream>
using namespace std;

class Playdough {
  public:
  	Playdough();
    Playdough(int v, string c);
    void describe(); // Prints information about the dough.
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

void Playdough::describe() {
	cout << "The Playdough has a volume of: " << (*this).volume << endl;
	cout <<	"The Playdough has a color of: " << (*this).color << endl;
}

Playdough squish_together(Playdough p1, Playdough p2)
{
	Playdough resultantDough = Playdough();
	resultantDough.volume = p1.volume + p2.volume;
	resultantDough.color = "pink"; // I could do if-statements and mix colors, but we're just going to statically set this to pink.
	return resultantDough;
}

int main() {
	Playdough redDough = Playdough(3, "red");
	redDough.describe();
	
	Playdough whiteDough = Playdough(3, "white");
	whiteDough.describe();

	Playdough result = squish_together(redDough, whiteDough);
	result.describe();
}