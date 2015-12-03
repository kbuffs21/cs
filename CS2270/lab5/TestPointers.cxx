#include "MyClass.cxx"


// Pass by value
void fun1(MyClass a)
{
	a.setX(1);
}


// Pass by reference
void fun2(MyClass& a)
{
	a.setX(2);
}



// Pass by pointer
void fun3(MyClass* a)
{
	a->setX(3);
}


// Using double pointers! Coz why stop at single pointers? :)
void fun4(MyClass** a)
{
	(*a)->setX(4);
}



int main() 
{
	MyClass a;
	MyClass* b;
	MyClass** c;
	
	cout << endl << "----Calling fun1----" << endl;
	
	fun1(a); 
	a.printX(); //'x' and 'a' are two different variables so changing one doesn't change the other and x remains zero.



	cout << endl << "----Calling fun2----" << endl;	
	
	fun2(a); 
	a.printX(); // since 'x' and 'a' both represent the same memory slot, then changing either variable changes the other.


	
	cout << endl << "----Calling fun3----" << endl;
	
	b = &a;     
	fun3(b);   
	a.printX(); //'b' represents the dereferenced pointer to 'a' so 'b' will always refer to the current value of 'a'.



	cout << endl << "----Calling fun4----" << endl;
	
	c = &b;    
	fun4(c);    
	a.printX(); // 'c' is a double pointer, first to 'b' then to 'a'. when 'a' is updated so is 'b' and consequently 'c' 
	
	//Dereferencing using single pointer
	cout << "\n\nTwo ways of dereferencing, \n1. Using '.' operator\n2. Using '->' operator\n\n";
	
	
	(*b).printX(); 
	b->printX();      
	
	//the first way derefs pointer first then calls function as it normally would.  
	//the second way of deref uses an arrow to indicate a pointer on lhs and no dot is needed.
	

	cout << "\n\n----Understanding arrays as pointers----" << endl;
	MyClass arr[5];
	
	arr[0].setX(10);
	arr[1].setX(20);
	arr[2].setX(30);
	arr[3].setX(40);
	arr[4].setX(50);
	
	cout << "----Running for loop for array variable 'arr' with 5 slots----" << endl << endl;
	
	//for every iteration of 'i' the loop prints the memory location of the ith slot in the array, 
	//then prints the deref value of that slot in the array through pointer arithmetic 
	//and finally prints the ith array value through traditionally calling the value explicitly.
	for (unsigned int i=0; i<5; i++)
	{
		cout << "i = " << i << endl;
		cout << "memory location (arr + i) = " << arr+i << endl;
		cout << "  (*(arr + i)).printX() prints ";
		(*(arr+i)).printX();
		cout << "        arr[i].printX() prints ";
		arr[i].printX();
		cout << endl;
	}
	
	
	
	return 0;


}

