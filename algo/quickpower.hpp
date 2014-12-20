template<class T>
T quick_power(const T& a, int d)
{
	T res(1);
	T m = a;
	while (d > 0)
	{
		if (d % 2 == 0)
		{
			m = m * m;
			d /= 2;
		}
		else
		{
			res *= m;
			d--;
		}
    }
	return res;
}