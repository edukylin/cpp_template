#include <iostream>

using namespace std;

// 2. 模板类特化
// 所谓泛化版本，是指通常情况下所写的模板类；
// 所谓特化版本，是需要特殊对待的模板类版本；
// 模板类特化版本，是通过模板类的泛化版本来生成的，故而需要先有泛化版本，进而有特化版本；
// 2.1 模板类的全特化
// 概念：就是把模板类泛化版本中的所有模板参数都用具体的类型来代替，所构成的一个特殊的版本（全特化版本）；
// 理解：模板类的泛化与全特化版本，可以理解为两个完全不同的类，只是名称相同而已；
// 2.2 普通成员函数的全特化；
// 2.3 静态成员变量的全特化；
// 注意：模板类进行了普通成员函数或者静态成员变量的全特化，则不能使用完全相同的模板参数进行模板类的全特化；
// 2.4 模板类的偏特化（局部特化）
// [a] 模板参数数量的偏特化；
// [b] 模板参数范围的偏特化(int -> const int, T -> T*, T -> T&, T -> T&&)；

// 模板类 - 全特化；
namespace _nmsp1
{
	// 模板类（泛化版本）；
	template<typename T, typename U>
	class TC
	{
	public:
		TC()
		{
			cout << "func: TC<T, U>::TC()." << endl;
		}
		void func();
	public:
		static int m_number;
	};
	// 模板类（泛化版本） - 普通成员函数类外定义；
	template<typename T, typename U>
	void TC<T, U>::func()
	{
		cout << "func: void TC<T, U>::func()." << endl;
	}
	// 模板类（泛化版本） - 静态成员变量类外定义；
	template<typename T, typename U>
	int TC<T, U>::m_number = 100;
	
	// 模板类 - 普通成员函数全特化；
	// template<>
	void TC<int, double>::func()
	{
		cout << "func: void TC<int, double>::func()." << endl;
	}

	// 模板类 - 静态成员变量全特化；
	// template<>
	// error: "_nmsp1::TC<T, U>::m_number [with T=int, U=double]" must precede its first use();
	int TC<int, double>::m_number = 200;

	// 模板类（全特化版本） - 所有模板参数都用具体类型类代替；
	template<>
	class TC<int, int>
	{
	public:
		TC()
		{
			cout << "func: TC<int, int>::TC()." << endl;
		}
		void func();
		void func_new();
	};
	// 模板类（全特化版本） - 普通成员函数类外定义；
	void TC<int, int>::func()
	{
		cout << "func: void TC<int, int>::func()." << endl;
	}
	// 模板类（全特化版本） - 静态成员变量类外定义；
	void TC<int, int>::func_new()
	{
		cout << "func: void TC<int, int>::func_new()." << endl;
	}
}

// 模板类 - 偏特化（基于模板参数数量）；
namespace _nmsp2
{
	// 模板类（泛化版本）；
	template<typename T, typename U>
	class TC
	{
	public:
		TC()
		{
			cout << "func: TC<T, U>::TC()." << endl;
		}
		void func();
	public:
		static int m_number;
	};
	// 模板类（泛化版本） - 普通成员函数类外定义；
	template<typename T, typename U>
	void TC<T, U>::func()
	{
		cout << "func: void TC<T, U>::func()." << endl;
	}
	// 模板类（泛化版本） - 静态成员变量类外定义；
	template<typename T, typename U>
	int TC<T, U>::m_number = 100;

	// 模板类（偏特化版本） - 模板参数数量；
	template<typename U>
	class TC<int, U>
	{
	public:
		TC()
		{
			cout << "func: TC<int, U>::TC()." << endl;
		}
		void func();
	public:
		static int m_number;
	};
	// 模板类（偏特化版本） - 普通成员函数类外定义；
	template<typename U>
	void TC<int, U>::func()
	{
		cout << "func: void TC<int, U>::func()." << endl;
	}
	// 模板类（偏特化版本） - 静态成员变量类外定义；
	template<typename U>
	int TC<int, U>::m_number = 200;
}

// 模板类 - 偏特化（基于模板参数范围）；
namespace _nmsp3
{
	// 模板类（泛化版本）；
	template<typename T, typename U>
	class TC
	{
	public:
		TC()
		{
			cout << "func: TC<T, U>::TC()." << endl;
		}
		void func();
	public:
		static int m_number;
	};
	// 模板类（泛化版本） - 普通成员函数类外定义；
	template<typename T, typename U>
	void TC<T, U>::func()
	{
		cout << "func: void TC<T, U>::func()." << endl;
	}
	// 模板类（泛化版本） - 静态成员变量类外定义；
	template<typename T, typename U>
	int TC<T, U>::m_number = 100;

	// 模板类（偏特化版本） - 模板参数数量；
	template<typename T, typename U>
	class TC<const T, U*>
	{
	public:
		TC()
		{
			cout << "func: TC<const T, U*>::TC()." << endl;
		}
		void func();
	public:
		static int m_number;
	};
	// 模板类（偏特化版本） - 普通成员函数类外定义；
	template<typename T, typename U>
	void TC<const T, U*>::func()
	{
		cout << "func: void TC<const T, U*>::func()." << endl;
	}
	// 模板类（偏特化版本） - 静态成员变量类外定义；
	template<typename T, typename U>
	int TC<const T, U*>::m_number = 200;
}

int main()
{	
	// 1. 模板类全特化测试；
	// 1.1 模板类泛化版本；
	_nmsp1::TC<int, float> tc1;
	tc1.func();
	cout << tc1.m_number << endl;
	// 1.2 模板类全特化版本；
	_nmsp1::TC<int, int> tc2;
	tc2.func();
	tc2.func_new();
	// 1.3 模板类普通成员函数/静态成员变量全特化版本；
	_nmsp1::TC<int, double> tc3;
	tc3.func();
	cout << tc3.m_number << endl;

	// 2. 模板类偏特化测试（基于模板参数数量）；
	// 2.1 模板类泛化版本；
	_nmsp2::TC<char, float> tc4;
	tc4.func();
	cout << tc4.m_number << endl;
	// 2.2 模板类偏特化版本（基于模板参数数量）；
	_nmsp2::TC<int, float> tc5;
	tc5.func();
	cout << tc5.m_number << endl;

	// 3. 模板类偏特化测试（基于模板参数范围）；
	// 3.1 模板类泛化版本；
	_nmsp3::TC<int, float> tc6;
	tc6.func();
	cout << tc6.m_number << endl;
	// 3.2 模板类偏特化版本（基于模板参数范围）；
	_nmsp3::TC<const int, float*> tc7;
	tc7.func();
	cout << tc7.m_number << endl;

	return 0;
}
