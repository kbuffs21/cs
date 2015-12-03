#include <iostream>
using namespace std;

class Playdough {
  public:
  	Playdough();
    Playdough(int v, string c);
    Playdough squish_together(Playdough p);
    void describe(); // Prints information about the dough.
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

void Playdough::describe() {
	cout << "The Playdough has a volume of: " << (*this).volume << endl;
	cout <<	"The Playdough has a color of: " << (*this).color << endl;
}

Playdough Playdough::squish_together(Playdough p)
{
	Playdough resultantDough = Playdough();
	resultantDough.volume = (*this).volume + p.volume;
	resultantDough.color = "pink"; // I could do if-statements and mix colors, but we're just going to statically set this to pink.
	return resultantDough;
}

int main() {
	Playdough redDough = Playdough(3, "red");
	redDough.describe();
	
	Playdough whiteDough = Playdough(3, "white");
	whiteDough.describe();

	Playdough result = redDough.squish_together(whiteDough);
	result.describe();
}