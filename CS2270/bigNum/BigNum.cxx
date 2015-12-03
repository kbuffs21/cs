
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
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity]; 
		digits[0] = 0;
		positive = true;      
		used = 1;
	}    

	BigNum::BigNum(int num)
	{
		digits = nullptr;

		if (num == 0) 
		{
			BigNum zero;
			*this = zero;
		}
    
		else 
		{
			if (num > 0) 
			{
				positive = true;
			}
			else 
			{
				positive = false;
				num = -num;
			}
      
			unsigned int i = 0, temp = num;
      
			// count the digits
			while (temp > 0) 
			{
				temp = temp/10; 
				i++;
			}

			capacity = i; 
		
			digits = new unsigned int[capacity];

			temp = num;
		
			for (used = 0; used < i; ++used) 
			{
				digits[used] = temp % 10;
				temp /= 10;
			}
		}
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		digits = nullptr;
		
		int len = strin.length();
		
		if (len == 0)
		{
			BigNum zero;
			*this = zero;
			return;
		}

		used = len;
		positive = true;
		
		int i = 0;

		if(strin[i] == '-')  
		{
			positive = false;
			i = 1;
			used--;
		}
		else if(strin[i] == '+')  
		{
			i = 1;
			used--;
		}
		
		capacity = used;
	
		digits = new unsigned int[capacity];

		for(unsigned int k = 0; k < used; ++k) 
		{
			digits[used - k - 1] = strin[i++] - '0';
		}
		
		if (used == 1 && digits[0] == 0)
			positive = true;
			
		trim();
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		digits = nullptr;
		
		// makes operator = do the work; use that function if you use this
		*this = anotherBigNum;
    }

    BigNum::~BigNum()
    {
		delete [] digits;
    }
        
    // assume doubling is done before passing in n
	void BigNum::resize(unsigned int n)
	{
		unsigned int *largerArray;

		if (n < used) return; // Can't allocate less than we are using

		capacity = n;
		largerArray = new unsigned int[capacity];
		
		copy(digits, digits + used, largerArray);
		
		delete [] digits;
		digits = largerArray;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if (this == &anotherBigNum)  return *this;
		
		if (digits != nullptr)
			delete [] digits;
			
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];
		
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
  
		return *this;
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		unsigned int i;  
		unsigned int sum;
		unsigned int carry = 0;
		unsigned int dub = 2 * capacity;     
		if (addend == 0)
		{                
			return *this;
		}
		if (positive != addend.positive)
		{
			return *this;
		}
		if (used < addend.used)
		{
			used = addend.used;
		}
		for(i=0; i < used; ++i)
		{
			sum = digits[i] + addend.digits[i] + carry;
			carry = sum / 10;
			sum = sum % 10;

			if (i < capacity)
			{
				digits[i] = sum;
			}
			else
			{
				resize(dub);
				used++;
				digits[i] = (sum);
			}
		}
		if (carry != 0)
		{
			resize(dub);
			used++;
			digits[i] = (carry);
		}
		return *this;
	}
	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		unsigned int min;
		unsigned int carry = 0;
		unsigned int i;
		if (this == &subtractand) 
		{
			*this = 0;
			return *this;
		}
		if (positive != subtractand.positive)
		{
			return *this;
		}
		if ((positive == true && (*this) < subtractand )||( positive == false && (*this) > subtractand))
		{
			*this = subtractand - *this;
			if (positive == true)
			{
				positive = false;
			}
			else         
			{     
				positive = true; 
			}
			return *this;
		}
		for(i=0; i < used; ++i)
		{
			min = digits[i] - subtractand.digits[i] - carry;
			carry = 0;
			if (min < 0)
			{  
				min += 10;
				carry = 1;
			}
			digits[i] = min;
		}
		trim();
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		if (positive != multiplicand.positive)
		{
			positive = false;
		}
		else
		{
			positive = true;
		}

		BigNum temp(*this);                       
		BigNum sum = 0;                          
		for(unsigned int i = 0 ; i < multiplicand.used; ++i)
		{
			sum += temp * multiplicand.digits[i]; 
			temp *= 10;      
		}
		*this = sum;
		return *this;
	}
	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		if(divisor == 0)
		{
			*this = BigNum(0);
		}
		else
		{
		}
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		if( digits[0] == 9)
		{
			digits[0] = 0;
			digits[1]++;
		}
		else
		{
			digits[0]++;
		}
	
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		if(digits[0] == 0 && used == 1)
		{
			return *this;
		}
		else if( digits[0] == 0)
		{
			digits[0] = 9;
			digits[1]--;
		}
		else
		{
			digits[0]--;
		}
	
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		*this = BigNum(0);
		if((a.used == 1 && a.digits[0] == 0 )||( b.used == 1 && b.digits[0] == 0))
		{
			return *this;
		}
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		*this = BigNum(0);
		if((a.used == 1 && a.digits[0] == 0 )||( b.used == 1 && b.digits[0] == 0))
		{
			return *this;
		}
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		*this = BigNum(0);
		if(a.used == 1 && a.digits[0] == 0 && b.used == 1 && b.digits[0] == 0)
		{
			return *this;
		}
		else if(a.used == 1 && a.digits[0] == 0)
		{
			*this = b;
			return *this;
		}
		else if(b.used == 1 && b.digits[0] == 0)
		{
			*this = a;
			return *this;
		}
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		if( a.used == 1 && a.digits[0] == 0 )
		{
			result = b;
		}
		if( b.used == 1 && b.digits[0] == 0 )
		{
			result = a;
		}
		else
		{
			/*BigNum result = a;
			BigNum addend = b;
			result += addend;*/
			BigNum result = 0;
		}
		return result;
	}
	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		if( a.used == 1 && a.digits[0] == 0 )
		{
			result = b;
		}
		if( b.used == 1 && b.digits[0] == 0 )
		{
			result = a;
		}
		else
		{
			/*BigNum result = a;
			BigNum subtractand = b;
			result -= subtractand;*/
			BigNum result = 0;
		}
		return result;
	}
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		if((a.used == 1 && a.digits[0] == 0 )||( b.used == 1 && b.digits[0] == 0))
		{
			return result;
		}
		if(a.used == 1 && a.digits[0] == 1)
		{
			result = b;
		}
		if(b.used == 1 && b.digits[0] == 1)
		{
			result = a;
		}
		else
		{/*
			result = a;
			result *= b;
		*/}
		return result;
	}


	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		if((a.used == 1 && a.digits[0] == 0 )||( b.used == 1 && b.digits[0] == 0))
		{
			return result;
		}
		else
		{
			if(a.positive == b.positive)
			{
				if(a.used == b.used)
				{
				
				}
				else if(b.used > a.used)
				{
				
				}
				else if(a.used > b.used)	
				{
					
				}
			}
		}
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if (a.positive == true && b.positive == false) return true;
		
		else if (a.positive == false && b.positive == true) return false;
		
		else 
		{
			if (a.used > b.used) 
			{
				if (a.positive == true) return true;
				else return false;
			}
			
			else if (a.used < b.used) 
			{
				if (a.positive == true) return false;
				else return true;
			}
	
			else 
			{
				for (unsigned int i = 0; i < a.used; ++i) 
				{
					if (a.digits[a.used - 1 - i] < b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return false;
						else return true;
					}
					if (a.digits[a.used - 1 - i] > b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return true;
						else return false;
					}
				}
			}          
		}
		return false;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return ((a > b) || (a == b));
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		return !(a >= b);
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return !(a > b);
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if ((a.positive != b.positive) || (a.used != b.used))
			return false;

		for (unsigned int i = 0; i < a.used; i++) 
		{
			if (a.digits[a.used - 1 - i] != b.digits[b.used - 1 - i]) 
				return false;
		}

		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
	}

	// trim leading zeros
	void BigNum::trim()
	{
		while (used > 1 && digits[used-1] == 0)
			used--;
	}
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		unsigned int i = 0;
		unsigned int j = 0;

		if (bignum.positive == false)  os << '-';

		for (i=0; i<bignum.used; ++i) 
		{
			os << bignum.digits[bignum.used - i - 1];
			if (j < 60) ++j; 
			else 
			{
				os << endl;
				j = 0;
			}
		}
    
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string str;
		is >> str;

		BigNum temp = str;
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



