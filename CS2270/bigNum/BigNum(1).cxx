// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		positive = true;
		used = capacity = 1;
		digits = new unsigned int[capacity];
		digits[0] = 0;
	}    

	BigNum::BigNum(int num)
	{
		if(num < 0)
		{
			positive = false; 
			num = num * -1;
			int numalt = num;
			int count = 0;
			while(num >= 1)
			{
				num = num/10;
				count++;
			}
			used = capacity = count;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i < capacity; ++i)
			{
				if(numalt >= 1)
				{
					digits[i] = numalt%10;
					numalt = ((numalt/10) - ((numalt%10)/10));
				}
				else 
				{
					digits[i] = 0;
				}
			}
		
		}	
		else if(num == 0)
		{
			positive = true;
			used = capacity = 1;
			digits = new unsigned int[capacity];
			digits[0] = 0;
		}
		else if(num > 0)
		{
			int numalt = num;
			positive = true;
			int count = 0;
			while(num >= 1)
			{
				num = num/10;
				count++;
			}
			used = capacity = count;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i < capacity; ++i)
			{
				if(numalt >= 1)
				{
					digits[i] = numalt%10;
					numalt = ((numalt/10) - ((numalt%10)/10));
				}
				else 
				{
					digits[i] = 0;
				}
			}
		
			
		} 
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		used = capacity = strin.length();
		if( strin[0] == '-')
		{
			positive = false;
			used--; 
			digits = new unsigned int[used+1];
			for(unsigned int i = 0; i <= used; ++i)
			{
				if(strin[i] <= 57 && strin[i] >= 48)
				{
					digits[(used - i)] = (strin[i] - 48);
				}
			}
		}
		else if(strin[0] == '+')
		{
			positive = true;
			used--;
			digits = new unsigned int[used+1];
			for(unsigned int i = 0; i <= used; ++i)
			{
				if(strin[i] <= 57 && strin[i] >= 48)
				{
					digits[(used - i)] = (strin[i] - 48);
				}
			}
		}
		else
		{
			positive = true;
			digits = new unsigned int[used];
			for(unsigned int i = 0; i <= used; ++i)
			{
				if(strin[i] <= 57 && strin[i] >= 48)
				{
					digits[((used - 1) - i)] = (strin[i] - 48);
				}
				
			}
		}	
		
	}
	
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];
		for(unsigned int i = 0; i < capacity; ++i)
			{
				digits[i] = anotherBigNum.digits[i];
			}
    }

    BigNum::~BigNum()
    {
		delete [] digits;	
		delete [] newdigits;	
    }
    
    void BigNum::resize(unsigned int n)
	{
		newdigits = new unsigned int[n];
		for (unsigned int i = 0; i < capacity ; ++i)
			{
				newdigits[i] = digits[i];
			}
		for (unsigned int i = capacity; i < n ; ++i)
			{
				newdigits[i] = 0;
			}
		delete [] digits;	
		digits = newdigits;
		capacity = n;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if(& anotherBigNum == this)	
			return *this;
		else 
		{
			delete [] digits;
			positive = anotherBigNum.positive;
			used = anotherBigNum.used;
			capacity = anotherBigNum.capacity;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i < capacity; ++i)
				{
					digits[i] = anotherBigNum.digits[i];
				}
			return *this;
		}
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		bool gt = false;
		if( a.positive == true && b.positive == false)
			gt = true;
		else if( a.positive == b.positive )
		{
			if(a.used > b.used)
				gt = true;
			else if( a.used == b.used)
			{
				unsigned int used = a.used;	
				if(a.digits[(used-1)] > b.digits[(used-1)])
				gt = true;
			}
		}
		return gt;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		bool ge = (a < b);
		return !ge;
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		bool lt = false;
		if( a.positive == false && b.positive == true)
			lt = true;
		else if( a.positive == b.positive )
		{
			if(a.used < b.used)
				lt = true;
			else if( a.used == b.used )
			{
				unsigned int used = a.used;	
				if(a.digits[(used-1)] < b.digits[(used-1)])
				lt = true;
			}
		}
		return lt;
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		bool le = (a > b);
		return !le;
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		bool e = false;
		if( a.positive == b.positive )
		{
			if(a.used == b.used)
			{
				unsigned int count = 0;
				unsigned int used = a.used;
				for(unsigned int i = 0; i < (used-1); ++i)
				{
					if(a.digits[i] == b.digits[i])
					{
						count++;
					}
				}
				if(count == used)
				e = true;
			}	
		}
		return e;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		bool e = (a == b);
		return !e;
	}

	// trim leading zeros
	void BigNum::trim()
	{
		/*For(unsigned int k = used; k = 0; --k)]
		{
			if( digits[k] != 0)
			{
				break
			}
			used--;
		}*/
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if(bignum.positive == false)
		{
			os << '-';
		}
			for(unsigned int k = 0; k <= bignum.used; --k)
			{
				os << bignum.digits[(k - 1)];
			}
		
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string a;
		is >> a;
		BigNum temp = BigNum(a);
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }



#endif



