#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstdlib>

namespace LA 
{
	typedef std::vector<int> _long;
	struct long_int
	{
		_long data;
		signed char sign;

		long_int();
		~long_int();
		void set_a_zero();
		inline char digit(int i) const;
	};

	typedef class long_arifm
	{
	private:
		
		
		long_int to_long_int(int n);
		int long_int_abs_cmp(long_int left, long_int right);
		int long_int_cmp(long_int left, long_int right);
		void shl(long_int &number, int disp);
		
		

	public:
		long_int num;
		~long_arifm();
		void set(char new_num[]);
		void show();
		long_int get();
		std::string toString();

		long_int sum(long_int first, long_int second);
		long_int sub(long_int first, long_int second);
		long_int mul(long_int first, long_int second);
		long_int div(long_int first, long_int second);	
		
		long_arifm operator+ (long_arifm right);
		long_arifm operator- (long_arifm right);
		long_arifm operator* (long_arifm right);
		long_arifm operator/ (long_arifm right);
	} big_integer;
}

