#include "poly.h"
using namespace std;
/*
Step 1. The member variables of polynomial are: head_ptr, tail_ptr, recent_ptr, and current_degree.
The head_ptr can be used to access the lead polynode of the polynomial. 
The tail_ptr can be used to access the last polynode of the polynomial.
rectent_ptr is a mutable variable that keeps track of the last polynode that was accessed and is used for efficiency.
Current_degree holds the value of the leading exponent.
 */

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if( fabs(c) < EPSILON && exponent == 0 )
		{
			head_ptr = new polynode();
			current_degree = 0;
			recent_ptr = head_ptr;
			tail_ptr = head_ptr;
		}
		else if( (fabs(c) >= EPSILON) && (exponent == 0) )
		{
			head_ptr = new polynode(c,0,nullptr,nullptr);
			current_degree = 0;
			recent_ptr = head_ptr;
			tail_ptr = head_ptr;
		}
		else if( fabs(c) < EPSILON && exponent > 0 )
		{
			head_ptr = new polynode();
			current_degree = 0;
			recent_ptr = head_ptr;
			tail_ptr = head_ptr;
		}
		else if( fabs(c) >= EPSILON && exponent > 0 )
		{
			head_ptr = new polynode(0,0,tail_ptr,nullptr);
			tail_ptr = new polynode(c,exponent,nullptr,head_ptr);
			recent_ptr = tail_ptr;
			current_degree = exponent;
		}
		
    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if(this == &source) 
		{ 
			return *this; 
			//clear list  no mem leaks
		} 
		if(source.head_ptr == nullptr) 
		{ 
			head_ptr = nullptr; 
			return *this; 
		} 
		head_ptr = new polynode(source.head_ptr->coef(),source.head_ptr->exponent());
		const polynode* source_curr = source.head_ptr->fore(); 
		polynode* curr = head_ptr; 
		while (source_curr != nullptr) 
		{ 
			curr = new polynode(source_curr->coef(),source_curr->exponent()); 
			curr = curr->fore(); 
			source_curr = source_curr->fore(); 
		}
		return *this;
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode(source.head_ptr->coef(),source.head_ptr->exponent());
		const polynode* source_curr = source.head_ptr->fore(); 
		polynode* curr = head_ptr; 
		while (source_curr != nullptr) 
		{ 
			curr = new polynode(source_curr->coef(),source_curr->exponent()); 
			curr = curr->fore(); 
			source_curr = source_curr->fore(); 
		}
    }

    polynomial::~polynomial()
    {
		clear();
    }

    void polynomial::clear()
    {
		while (tail_ptr != head_ptr) 
		{ 
			polynode* to_delete = tail_ptr; 
			tail_ptr = tail_ptr->back(); 
			delete to_delete; 
		}
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		delete head_ptr;		
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		double c = 0;
		if( recent_ptr->exponent() == exponent )
		{
			c = recent_ptr->coef();
		}
		return c;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		if( fabs(amount) > EPSILON)
		{
		set_recent(exponent);
		double base = recent_ptr->coef();
		amount = amount + base;
		assign_coef(amount,exponent);
		}
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		if( fabs(coefficient) < EPSILON && exponent > current_degree )//zero coefficient with exp greater than poly degree
		{
			return;
			
		}
		else if( recent_ptr->exponent() < exponent && fabs(coefficient) >= EPSILON)//non-zero coef with exp not in poly
		{
			if( recent_ptr == tail_ptr )
			{
				polynode* temp = new polynode(coefficient,exponent,nullptr,tail_ptr);
				tail_ptr->set_fore(temp);
				tail_ptr = temp;
				current_degree = tail_ptr->exponent();	
			}
			else if( recent_ptr == head_ptr ) //poly will have at least two entries, otherwise fall in previous case
			{
				recent_ptr = new polynode(coefficient,exponent,head_ptr->fore(),head_ptr);
				head_ptr->fore()->set_back(recent_ptr);
				head_ptr->set_fore(recent_ptr);
			}
			else
			{
				polynode* temp = new polynode(coefficient,exponent,recent_ptr->fore(),recent_ptr);
				recent_ptr->set_fore(temp);
				recent_ptr->fore()->set_back(temp);	
			}
		}
		else if( fabs(coefficient) >= EPSILON || exponent == 0)//change coefficient in poly
		{
			recent_ptr->set_coef(coefficient);
		}
		else if( fabs(coefficient) < EPSILON && exponent == current_degree )//remove tail of poly
		{
			tail_ptr = recent_ptr->back();
			delete recent_ptr;
			recent_ptr = tail_ptr;
			recent_ptr->set_fore(nullptr);
			tail_ptr->set_back(recent_ptr->back());
			current_degree = tail_ptr->exponent();
		}
		else
		{
			// in this last case, we must have a new zero coefficient for a polynode 
			//that is neither the head nor the tail. We just remove this polynode and set the 
			//recent_ptr to the previous polynode in the list. 
			polynode* to_delete = recent_ptr;
			to_delete->back()->set_fore(to_delete->fore());
			recent_ptr->fore()->set_back(recent_ptr->back());
			delete to_delete;
		}
    }

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		set_recent(exponent);
		unsigned int e = 0;
		if(recent_ptr->fore() != nullptr )
		{
			e = recent_ptr->fore()->exponent();
		}
		return e;
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		set_recent(exponent);
		unsigned int e = UINT_MAX;
		if(recent_ptr->back() != nullptr )
		{
			e = recent_ptr->back()->exponent();
		}
		return e;
    }
    
    void polynomial::set_recent(unsigned int exponent) const
    {
		if( exponent == 0)
		{
			recent_ptr = head_ptr;
		}
		else if( exponent >= current_degree )
		{
			recent_ptr = tail_ptr;
		}
		else if( exponent < recent_ptr->exponent() )
		{
			while( exponent > recent_ptr->exponent() && recent_ptr != nullptr )
			{
				recent_ptr = recent_ptr->back();
			}
		}
		else//exponent greater than recent ptr exponent
		{
			while( exponent > recent_ptr->exponent() && recent_ptr != nullptr )
			{
				recent_ptr = recent_ptr->fore();
			}
			if( recent_ptr->exponent() > exponent )
			{
				recent_ptr = recent_ptr->back();
			}
		}
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0)
			{
				out << " + ";
			}
		}while(expo != 0);
    }
    void polynomial::find_root(double& answer,bool& success,unsigned int& iterations,double guess,unsigned int maximum_iterations,double epsilon) const
    {
	}
	bool polynomial::exponent_in_poly(unsigned int exponent ) const
    {	
		bool boolean = false;
		for( recent_ptr = head_ptr ; recent_ptr == tail_ptr ; recent_ptr = recent_ptr->fore())
		{
			if( recent_ptr->exponent() == exponent)
			{
				boolean = true;
			}
		} 
		return boolean;
	}
}
