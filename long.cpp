#include <iostream>
#include <clocale>
#include <string>
#include <vector>

using namespace std;

///////////////////////////////////////////////// GLOBAL VARIABLES



///////////////////////////////////////////////// LONG CLASS
class Long
{
private:

	vector<int> v;

	int z;

public:

	void input()
	{
		string s;

		cin >> s;

		z = 1;

		if (s[0] == '-')
		{
			z = -1;

			s.erase(0, 1);
		}

		while (s.empty() == false && s[0] == '0')
			s.erase(0, 1);

		if (s.empty() == true)
		{
			v.push_back(0);

			z = 1;
		}

		while (s.empty() == false)
		{
			v.push_back(atoi(s.substr(s.size() - 1, 1).c_str()));

			s.erase(s.size() - 1, 1);
		}
	}

	void output()
	{
		if (z < 0)
			cout << "-";

		for (int i = v.size() - 1; i >= 0; i--)
			cout << v[i];

		cout << endl;
	}

	void null()
	{
		v.insert(v.cbegin(), 0);
	}

	void operator=(Long l)
	{
		v = l.v;

		z = l.z;
	}

	Long operator+(Long l)
	{
		if (z < 0 && l.z > 0)
			return l - *this;

		if (z > 0 && l.z < 0)
			return *this - l;

		Long res = v.size() > l.v.size() ? *this : l;

		l = v.size() > l.v.size() ? l : *this;

		int e = 0;

		for (int i = 0; i < res.v.size(); i++)
		{
			res.v[i] += e;
			res.v[i] += i < l.v.size() ? l.v[i] : 0;

			if (res.v[i] > 9)
			{
				res.v[i] -= 10;

				e = 1;

				if (i == res.v.size() - 1)
					res.v.push_back(0);
			}
			else
				e = 0;
		}

		return res;
	}

	Long operator-(Long l)
	{
		if (z < 0 && l.z > 0)
		{
			l.z = -1;

			return *this + l;
		}

		if (z > 0 && l.z < 0)
		{
			l.z = 1;

			return *this + l;
		}

		Long res;

		if (v.size() == l.v.size())
		{
			int i;

			for (i = 0; i < v.size(); i++)
				if (v[i] != l.v[i])
					break;

			if (v[i] > l.v[i] || i == v.size())
				res = *this;
			else
			{
				res = l;
				l = *this;

				res.z = -1;
			}
		}
		else if (v.size() > l.v.size())
			res = *this;
		else
		{
			res = l;
			l = *this;

			res.z = -1;
		}

		int e = 0;

		for (int i = 0; i < res.v.size(); i++)
		{
			res.v[i] -= e;
			res.v[i] -= i < l.v.size() ? l.v[i] : 0;

			if (res.v[i] < 0)
			{
				res.v[i] += 10;

				e = 1;

				if (i == res.v.size() - 1)
				{
					res.z = -1;

					res.v[i] = -(res.v[i] - 10);
				}
			}
			else
				e = 0;
		}

		while (res.v.size() > 1 && res.v[res.v.size() - 1] == 0)
			res.v.pop_back();

		return res;
	}

	Long operator*(Long l)
	{
		Long r = v.size() > l.v.size() ? *this : l;

		l = v.size() > l.v.size() ? l : *this;

		int z = l.z * r.z;

		l.z = r.z = 1;

		int e = 0;

		Long l0, res;

		res.z = 1;

		res.null();

		for (int i = 0, n = 0; i < l.v.size(); i++, n++)
		{
			l0 = r;

			for (int j = 0; j < l0.v.size(); j++)
			{
				l0.v[j] *= l.v[i];
				l0.v[j] += e;

				if (l0.v[j] > 9)
				{
					e = l0.v[j] / 10;

					l0.v[j] -= e * 10;

					if (j == l0.v.size() - 1)
						l0.v.push_back(0);
				}
				else
					e = 0;
			}

			for (int i = 0; i < n; i++)
				l0.null();

			res = res + l0;
		}

		res.z = z;

		return res;
	}

	Long operator/(Long l)
	{

	}
};

///////////////////////////////////////////////// MAIN FUNCTION
int main()
{
	setlocale(0, "");

	Long l, l1, l0;

	char op;

	cout << "Введите первое число:" << endl;

	l.input();

	cout << endl << "Введите знак операции:" << endl;

	cin >> op;

	cout << endl << "Введите второе число:" << endl;

	l1.input();

	if (op == '+')
		l0 = l + l1;
	else if (op == '-')
		l0 = l - l1;
	else if (op == '*')
		l0 = l * l1;
	else
	{
		cout << endl << "Такой операции нет" << endl;

		return 0;
	}

	cout << endl << "Результат:" << endl;

	l0.output();
}
/////////////////////////////////////////////////













