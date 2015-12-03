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
		
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode(c, 0);
		if (exponent == 0 || fabs(c) < EPSILON)
		{
			recent_ptr = head_ptr;
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else
		{
			head_ptr->set_coef(0);
			polynode* p = new polynode(c, exponent, nullptr, head_ptr);
			head_ptr->set_fore(p);
			tail_ptr = p;
			recent_ptr = p;
			current_degree = exponent;
		}
    }
		/* store machine epsilon
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
		
    }*/

    polynomial& polynomial::operator=(const polynomial& source)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		if (this == &source)
			return *this;
		if (head_ptr != nullptr)
		{	
			clear();
			delete head_ptr;
		}
		tail_ptr = nullptr;
		head_ptr = nullptr;
		recent_ptr = nullptr;
	
		if (source.head_ptr != nullptr)
		{
			head_ptr = new polynode(source.head_ptr->coef(), source.head_ptr->exponent());
			tail_ptr = head_ptr;
			recent_ptr = head_ptr;
			current_degree = 0;
	
			for (unsigned int expo = source.next_term(0); expo != 0; expo = source.next_term(expo))
				assign_coef(source.coefficient(expo), expo);
		}
		return *this;
		/* store machine epsilon
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
		return *this;*/
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = nullptr;
		*this = source;
		/* store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode(source.head_ptr->coef(),source.head_ptr->exponent());
		const polynode* source_curr = source.head_ptr->fore(); 
		polynode* curr = head_ptr; 
		while (source_curr != nullptr) 
		{ 
			curr = new polynode(source_curr->coef(),source_curr->exponent()); 
			curr = curr->fore(); 
			source_curr = source_curr->fore(); 
		}*/
    }

    polynomial::~polynomial()
    {
		clear();
		delete head_ptr;
		head_ptr = nullptr;
		tail_ptr = nullptr;
		recent_ptr = nullptr;
		current_degree = 0;
    }

    void polynomial::clear()
    {
		polynode* curr_node = head_ptr;
		while (head_ptr->fore() != nullptr)
		{
			curr_node = head_ptr->fore();
			delete head_ptr;
			head_ptr = curr_node;
		}
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		current_degree = 0;
		tail_ptr = head_ptr;
		recent_ptr = head_ptr;
		/*
		while (tail_ptr != head_ptr) 
		{ 
			polynode* to_delete = tail_ptr; 
			tail_ptr = tail_ptr->back(); 
			delete to_delete; 
		}
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		delete head_ptr;*/		
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		if (recent_ptr->exponent() == exponent)
			return recent_ptr->coef();
		return 0;
		/*
		set_recent(exponent);
		double c = 0;
		if( recent_ptr->exponent() == exponent )
		{
			c = recent_ptr->coef();
		}
		return c;*/
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);
		if (fabs(amount) < EPSILON)
			return;
		else
		{
			if (recent_ptr->exponent() < exponent)
			{
				polynode* new_node = new polynode(amount, exponent, recent_ptr->fore(), recent_ptr);
				if (recent_ptr->fore() != nullptr)
					recent_ptr->fore()->set_back(new_node);
				else
					tail_ptr = new_node;
				recent_ptr->set_fore(new_node);
				if (exponent > current_degree && fabs(amount) >= EPSILON)
					current_degree = exponent;
			}
			else
			{
				if (exponent == 0)
					recent_ptr->set_coef(recent_ptr->coef() + amount);
				else
				{
					if (exponent == current_degree)
					{	
						if (fabs(amount + recent_ptr->coef()) < EPSILON)
						{
							tail_ptr = recent_ptr->back();
							delete recent_ptr;
							recent_ptr = tail_ptr;
							tail_ptr->set_fore(nullptr);
							current_degree = tail_ptr->exponent();
						}
						else
							recent_ptr->set_coef(recent_ptr->coef() + amount);
					}
					else
					{
						if (fabs(amount + recent_ptr->coef()) < EPSILON)
						{
							recent_ptr->back()->set_fore(recent_ptr->fore());
							recent_ptr->fore()->set_back(recent_ptr->back());
							delete recent_ptr;
							recent_ptr = recent_ptr->back();
						}
						else
							recent_ptr->set_coef(recent_ptr->coef() + amount);
					}
				}
			}
		}
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		if (fabs(coefficient) < EPSILON && exponent > current_degree)
			return;
		else
			if (recent_ptr->exponent() < exponent)
			{
				polynode* new_node = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
				if (recent_ptr->fore() != nullptr)
				{
					recent_ptr->fore()->set_back(new_node);
				}
				else
				{
					tail_ptr = new_node;
				}
				recent_ptr->set_fore(new_node);
				if (exponent > current_degree)
					current_degree = exponent;
				recent_ptr = new_node;
			}
			else
				if (fabs(coefficient) > EPSILON || exponent == 0)
				{
					recent_ptr->set_coef(coefficient);
					if (exponent > current_degree)
						current_degree = exponent;
				}
				else
					if (exponent == current_degree)
					{
						tail_ptr = recent_ptr->back();
						delete recent_ptr;
						recent_ptr = tail_ptr;
						tail_ptr->set_fore(nullptr);
						current_degree = tail_ptr->exponent();
					}
					else
					{
						recent_ptr->back()->set_fore(recent_ptr->fore());
						recent_ptr->fore()->set_back(recent_ptr->back());
						polynode* to_delete = recent_ptr;
						recent_ptr = recent_ptr->back();
						delete to_delete;
					}
			
    }
    /*
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
    }*/

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		if (exponent >= current_degree) 
		{
			return 0;
		}
		set_recent(exponent);   
		if (recent_ptr->fore() == nullptr) 
		{
			return 0;
		}
		return recent_ptr->fore()->exponent();
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if (exponent <= 0) return UINT_MAX;
		set_recent(exponent - 1);
		if (recent_ptr == nullptr) return UINT_MAX;
		if (recent_ptr->exponent() == 0 && fabs(recent_ptr->coef()) < EPSILON)
			return UINT_MAX;
		else
		{
			return recent_ptr->exponent();
		}
		return UINT_MAX;
    }
    
    void polynomial::set_recent(unsigned int exponent) const
     {
		if (exponent == 0)
		{
			recent_ptr = head_ptr;
		}
		else
			if (exponent >= current_degree)
			{
				recent_ptr = tail_ptr;
			}
			else
				if (exponent < recent_ptr->exponent())
				{
					while (recent_ptr->back() != nullptr && recent_ptr->exponent() > exponent)
					recent_ptr = recent_ptr->back();
				}
				else
				{	
					while (recent_ptr->fore() != nullptr && recent_ptr->exponent() < exponent)
						recent_ptr = recent_ptr->fore();
					if (recent_ptr->exponent() > exponent)
						recent_ptr = recent_ptr->back();
				}
	}
	/*
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
	}*/
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		set_recent(0);
		if( recent_ptr->exponent() == 0)//add poly coef
		{
			total = total + recent_ptr->coef();
		}
		while(recent_ptr != nullptr)
		{
			double temp = x;
			for(unsigned int i = 1 ; i < (recent_ptr->exponent()) ; ++i)
			{
				temp = temp * x;
			}
			temp = temp * (recent_ptr->coef());
			total = total + temp;
			recent_ptr = recent_ptr->fore();			
		}
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		set_recent(0);
		if( recent_ptr->exponent() == 0 )
		{
			recent_ptr = recent_ptr->fore();
		}
		while( recent_ptr != nullptr )
		{
			double c = (recent_ptr->coef())*(recent_ptr->exponent());
			unsigned int e = (recent_ptr->exponent())-1;
			p_prime.assign_coef(c,e);
			recent_ptr = recent_ptr->fore();
		}
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p = p1;
		p2.set_recent(0);
		while( p2.recent_ptr!=nullptr ) 
		{
			double c = p2.recent_ptr->coef();
			unsigned int e = p2.recent_ptr->exponent();
			p.add_to_coef(c,e);
			p2.recent_ptr = p2.recent_ptr->fore();
		}
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p = p1;
		p2.set_recent(0);
		while( p2.recent_ptr!=nullptr ) 
		{
			double c = (-1*p2.recent_ptr->coef());
			unsigned int e = p2.recent_ptr->exponent();
			p.add_to_coef(c,e);
			p2.recent_ptr = p2.recent_ptr->fore();
		}
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
			p1.set_recent(0);
			p2.set_recent(0);
			double c1 = 0.0;
			double c2 = 0.0;
			double c = 0.0;
			unsigned int e1 = 0;
			unsigned int e2  = 0;
			unsigned int e = 0;
			while(p1.recent_ptr != nullptr)
			{
				p2.set_recent(0);
				while(p2.recent_ptr != nullptr )
				{
					c1 = p1.recent_ptr->coef();
					c2 = p2.recent_ptr->coef();
					c = c1 * c2;
					e1 = p1.recent_ptr->exponent();
					e2 = p2.recent_ptr->exponent();
					e = e1 + e2;
					p.add_to_coef(c,e);
					p2.recent_ptr = p2.recent_ptr->fore();
				}
				p1.recent_ptr = p1.recent_ptr->fore();
			}
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0) out << " + ";
		} while(expo != 0);
		return out;
    }
    void polynomial::find_root(double& answer,bool& success,unsigned int& iterations,double guess,unsigned int maximum_iterations,double epsilon) const
    {
		polynomial prime = this->derivative();
		double p = guess;
		double f = 0.0;
		double fp = 0.0;
		iterations = 0;
		if( prime.eval(p) == 0 )
		{
			success = false;
		}
		for( iterations = 0; iterations <= maximum_iterations; ++iterations ) 
		{		
			f = this->eval(p);
			fp = prime.eval(p);
			p = (p - (f/fp));
			if ( fabs(f) < epsilon )
			{
				success = true;
				answer = p;
				break;
			}
		}	
	}
}
