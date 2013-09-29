#include "long_arifm.h"

using namespace LA;

long_int::long_int()
{
	set_a_zero();
}

void long_int::set_a_zero()
{
	sign = 1;
	data.clear();
	data.push_back(0);
}

char inline long_int::digit(int i) const
{
	return data[i];
}

long_int::~long_int() 
{
	data.clear();
}

long_arifm::~long_arifm()
{
	num.data.clear();
}

void long_arifm::set(char new_num[])
{
	unsigned int i;
	
	if (new_num[0] == '-')
	{
		i = 1;
		num.sign = -1;
	}
	else
	{
		i = 0;
		num.sign = 1;
	}

	num.data.clear();
	for (; i < std::strlen(new_num); i++)
	{
		num.data.push_back(new_num[i] - '0');
	}
	std::reverse(num.data.begin(), num.data.end());
}

void long_arifm::show()
{
	if (num.sign == -1)
		std::cout << '-';

	int flag = 0;
	for (int i = num.data.size() - 1; i >= 0; i--)
	{
		if (flag || num.digit(i) != 0)
		{
			flag = 1;
			std::cout << (char)(num.digit(i) + '0');
		}
	}
	if (!flag) std::cout << '0';
	std::cout << '\n';
}

std::string long_arifm::toString()
{
	std::string s;
	if (num.sign == -1)
		s += '-';

	int flag = 0;
	for (int i = num.data.size() - 1; i >= 0; i--)
	{
		if (flag || num.digit(i) != 0)
		{
			flag = 1;
			s += (char)(num.digit(i) + '0');
		}
	}
	if (!flag) s += '0';
	return s;
	//std::cout << '\n';
}

long_int long_arifm::get()
{
	return this->num;
}

long_int long_arifm::to_long_int(int n)
{
	if (n < 0)
	{
		num.sign = -1;
		n = -n;
	} 
	else num.sign = 1;

	int i = 0, p10 = 1;

	while((n / p10) > 0)
	{
		p10 *= 10;
		i++;
	}

	p10 /= 10;
	i--;
	num.data.resize(i + 1);
	for (; i >= 0; i--)
	{
		num.data[i] = n / p10;
		n %= p10;
		p10 /= 10;
	}
	return num;
}

int long_arifm::long_int_abs_cmp(long_int left, long_int right)
{	
	while (left.data.size() < right.data.size())
		left.data.push_back(0);
	while (left.data.size() > right.data.size())
		right.data.push_back(0);
	
	for (int i = left.data.size() - 1; i >= 0; i--)
	{
		if (left.digit(i) == right.digit(i)) continue;
		if (left.digit(i) > right.digit(i)) return 1;
		if (left.digit(i) < right.digit(i)) return -1;
	}
	return 0;
}

int long_arifm::long_int_cmp(long_int left, long_int right)
{
	if(left.sign == 1 && right.sign == -1)return 1;
	if(left.sign == -1 && right.sign == 1)return -1;
	if(left.sign == 1 && right.sign == 1)return long_int_abs_cmp(left,right);
	if(left.sign == -1 && right.sign == -1)return -long_int_abs_cmp(left,right);
	return 0;
}

long_int long_arifm::sum(long_int first, long_int second)
{
	int p;
	long_int temp = first;

	while (temp.data.size() < second.data.size())
		temp.data.push_back(0);
	while (temp.data.size() > second.data.size())
		second.data.push_back(0);

	if (temp.sign == second.sign)
	{
		p = 0;
		
		for (unsigned int i = 0; i < temp.data.size(); i++)
		{
			p += temp.digit(i) + second.digit(i);
			temp.data[i] = p % 10;
			p /= 10;
		}

		if (p > 0)
			temp.data.push_back(p);
	} else {
		if (temp.sign == -1)
			std::swap(temp, second);
		int cmp = long_int_abs_cmp(temp, second);
		if (cmp ==0)
			temp.set_a_zero();
		else if (cmp > 0)
		{
			second.sign = 1;
			sub(first, second);
		} else {
			second.sign = 1;
			sub(second, first);
			temp = second;
			temp.sign = -1;
		}
	}
	return temp;
}

long_int long_arifm::sub(long_int first, long_int second)
{
	long_int temp = first;
	while (temp.data.size() < second.data.size())
		temp.data.push_back(0);
	while (temp.data.size() > second.data.size())
		second.data.push_back(0);
	
	if (second.sign == -1)
	{
		second.sign = 1;
		temp = sum(temp, second);
		return temp;
	}

	if (temp.sign == -1)
	{
		temp.sign = 1;
		temp = sum(temp, second);
		temp.sign = - temp.sign;
		return temp;
	}

	int cmp = long_int_abs_cmp(temp, second);
	if (cmp == 0)
	{
		temp.set_a_zero();
		return temp;
	}

	if (cmp < 0)
	{
		std::swap(temp, second);
		temp = sub(temp, second);
		temp.sign = -temp.sign;
		return temp;
	}

	int p =0;
	for (unsigned i = 0; i < temp.data.size(); i++)
	{
		p = temp.digit(i) - second.digit(i) - p;
		temp.data[i] = (p + 10) % 10;
		if (p < 0) p = 1;
		else p = 0;
	}
	return temp;
}

long_int long_arifm::mul(long_int first, long_int second)
{
	first.sign *= second.sign;
	long_int tmp;
	tmp.data.resize(first.data.size() + second.data.size());

	for (size_t i = 0; i < first.data.size(); ++i)
		for (int j = 0, carry = 0; j < (int)second.data.size() || carry; ++j) {
			long long cur = tmp.data[i + j] + first.data[i] * 1ll * (j < (int)second.data.size() ? second.data[j] : 0) + carry;
			tmp.data[i + j] = int (cur % 10);
			carry = int (cur / 10);
		}
		while (tmp.data.size() > 1 && tmp.data.back() == 0)
			tmp.data.pop_back();

	tmp.sign = first.sign;
	return tmp;
}

void long_arifm::shl(long_int &number, int disp)
{
	int i;
	long_int tmp;
	tmp.data.resize(number.data.size() + disp);
	for(i = 0; i < tmp.data.size(); i++)
	{
		if (i - disp >= 0 && i - disp < number.data.size())
			tmp.data[i] = number.data[i - disp];
	}
	number = tmp;
}

long_int long_arifm::div(long_int first, long_int second)
{ 
	long_int res, zero;
	long_int t_first = first, t_second = second;
	res.set_a_zero(); zero.set_a_zero();
	int i, j;
	int res_sign = first.sign * second.sign;
	first.sign = second.sign = 1;
	if (long_int_cmp(first, zero) == 0) return zero;
	if (long_int_cmp(second, zero) == 0)
	{
		first.set_a_zero();
		return zero;
	}

	res.data.resize(first.data.size());
	i = first.data.size() - second.data.size();
	shl(second, i);
	long_int tmp;
	for (; i >= 0; i--)
	{
		tmp.set_a_zero();
		j = 0;
		do {
			tmp = sum(tmp, second);
			j++;
		} while (long_int_abs_cmp(tmp, first) <= 0);

		tmp = sub(tmp, second);
		j--;
		first = sub(first, tmp);
		res.data[i] = j;

		shl(second, -1);
	}
	res.sign = res_sign;
	long_int temp = t_second;
	mul(temp, res);
	std::swap(temp, t_first);
	temp = sub(temp, t_first);
	if (long_int_cmp(temp, zero) < 0)
		res = sub(res, to_long_int(1)); 
	return res;
}

long_arifm long_arifm::operator+ (long_arifm right)
{
	long_arifm res;
	res.num = sum(num, right.get());
	return res;
}

long_arifm long_arifm::operator- (long_arifm right)
{
	long_arifm res;
	res.num = sub(num, right.get());
	return res;
}

long_arifm long_arifm::operator* (long_arifm right)
{
	long_arifm res;
	res.num = mul(num, right.get());
	return res;
}

long_arifm long_arifm::operator/ (long_arifm right)
{
	long_arifm res;
	res.num = div(num, right.get());
	return res;
}
