#include <iostream>
#include <cmath>
using namespace std;

class CComplex
{
	float real;
	float imag;
public:
	CComplex()
	{
		this->real = 0.0;
		this->imag = 0.0;
	}

	CComplex(float real, float imag)
	{
		this->real = real;
		this->imag = imag;
	}
	CComplex& operator=(CComplex& complex)
	{
		this->real = complex.real;
		this->imag = complex.imag;
		return *this;
	}
	CComplex operator*(CComplex& complex)
	{
		CComplex temp;
		temp.real = this->real * complex.real - this->imag * complex.imag;
		temp.imag = this->real * complex.imag + complex.imag * this->real;
		return temp;
	}

	CComplex operator+(CComplex& complex)
	{
		CComplex temp;
		temp.real = this->real + complex.real;
		temp.imag = this->imag + complex.imag;
		return temp;
	}

	CComplex operator-(CComplex& complex)
	{
		CComplex temp;
		temp.real = this->real - complex.real;
		temp.imag = this->imag - complex.imag;
		return temp;
	}

	CComplex operator/(CComplex& complex)
	{
		if (complex.imag == 0 || complex.real == 0)
		{
			cout << "zero can't be div" << endl;
			exit(0);
		}
		CComplex temp;
		temp.real = (this->real * complex.real + this->imag * complex.imag) / (pow(complex.real, 2) + pow(complex.imag, 2));
		temp.imag = (this->imag * complex.real - this->real * complex.imag) / (pow(complex.real, 2) + pow(complex.imag, 2));
		return temp;
	}

	CComplex operator[](int index)
	{

	}

	friend bool operator==(CComplex& complex1, CComplex& complex2);
	friend bool operator!=(CComplex& complex1, CComplex& complex2);

	void print()
	{
		cout << "实部为：" << this->real << " 虚部为：" << this->imag << endl;
	}
};

bool operator==(CComplex& complex1, CComplex& complex2)
{
	if (complex1.real == complex2.real && complex1.imag == complex2.imag)
		return true;
	else
		return false;
}

bool operator!=(CComplex& complex1, CComplex& complex2)
{
	if (complex1.real != complex2.real || complex1.imag != complex2.imag)
		return true;
	else
		return false;
}

int main()
{
	CComplex complex1;
	cout << "complex1:";
	complex1.print();

	CComplex complex2(2.0, 2.0);
	cout << "complex2:";
	complex2.print();

	CComplex complex3 = complex2 + complex2;
	cout << "complex3:";
	complex3.print();

	CComplex complex4 = complex2 * complex2;
	cout << "complex4:";
	complex4.print();

	CComplex complex5 = complex3 - complex2;
	cout << "complex5:";
	complex5.print();

	CComplex complex6 = complex4 / complex2;
	cout << "complex6:";
	complex6.print();

	if (complex6 == complex2)
	{
		cout << "complex6 = complex2" << endl;
	}
	else
	{
		cout << "complex6 != complex2" << endl;
	}

	CComplex complex8(1.2, 2.3);
	cout << "complex8:";
	complex8.print();
	complex8 = complex3;
	cout << "complex8:";
	complex8.print();


	return 0;
}

