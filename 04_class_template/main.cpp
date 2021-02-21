#include <iostream>

using namespace std;

// 1. 模板类
// 1.1 基本概念
// 所谓模板类，实际上是建立一个通用类，其数据成员、成员函数的返回值类型和形参类型不具体指定，用一个虚拟类型来代表；
// 使用模板类定义对象时，系统会使用给定的实际类型取代模板类中的虚拟类型，进而实现了不同类的功能；
// 简单理解：模板类是生产类的模具，通过给定的模板参数生成具体的类，即实例化一个特定的类；
// 典型范例：vector<int>，引入模板类，是为了减少代码冗余；
// 1.2 基本范例
// vector：类名或者模板类，vector<T>：类型名（具体类型）；
// 类模板中，只有被调用的成员函数才会被实例化；
// 1.3 模板参数推断
// C++17中，类模板的模板参数类型，可以通过构造函数实际参数进行推断；
namespace _nmsp1
{
	// 模板类定义；
	template <typename T/*元素类型*/>
	class vector  // vector：类名或者模板类，vector<T>：类型名（具体类型）；
	{
	public:
		// 构造函数；
		vector()
		{ 
			cout << "func: vector::vector()." << endl;
		}
		vector(T tv1)
		{
			cout << "func: vector::vector(T tv1)." << endl;
		}
		vector(const vector& vec);				 // 拷贝构造（被调用的函数才会被实例化）；
		vector<T>& operator=(const vector& vec); // 拷贝赋值（被调用的函数才会被实例化）；
	public:
		typedef T* iterator; // 迭代器；
	public:
		// 普通成员函数；
		void m_func();
		// 静态成员函数；
		static void static_func();
	public:
		iterator begin();  // 迭代器起始位置（被调用的函数才会被实例化）；
		iterator end();    // 迭代器结束位置（被调用的函数才会被实例化）；
	};
	// 类模板实现 - 成员函数；
	template<typename T>
	void vector<T>::m_func()
	{
		cout << "func: void vector::m_func()." << endl;
	}
	// 类模板实现 - 静态函数；
	template<typename T>
	void vector<T>::static_func()
	{
		cout << "func: void vector::static_func()." << endl;
	}
}

// 1.4 推断指南（deduction guide）
// C++17新增概念：主要用来在推断类模板参数时提供推断指引，即可以通过构造函数实际参数进行推断；
// C++17启用设置：Properties->C / C++->Language->C++ Language Standard(ISO C++17 Standatd);
// ======================================================================
// [a] 隐式推断指南
// 隐式推断指南举例：模板类A的所有构造函数，都有一个隐式的模板参数推断机制存在；
// template<typename T>
// A(T,T)->A<T>;
// 语法说明：当表达式出现->左侧部分内容或形式时，自动推断成->右侧的类型（指南类型）；
// ->左侧部分：推断指南所对应的构造函数的函数声明，多个参数之间使用逗号分隔；
// ->右侧部分：模板类名，后接一个尖括号，尖括号中为模板参数名；
// 推断指南意义：调用模板类构造函数时，通过构造函数实参类型推断出模板类的实例化类型；
// ======================================================================
// [b] 显示推断指南（自定义）
// _nmsp3::B bobj3{ 15 }，不报错的原因：
// * 类为聚合类，可以通过初始化列表实现初始化；
// * 初始化形式正好就相当于调用了模板类带一个参数的构造函数，尽管模板类中实际并不存在构造函数；
// 显示推断指南的存在，当调用了模板类B带一个参数的构造函数时，推断出来的类型为B<T>，所以最终推断出来的类型为B<int>类型；

namespace _nmsp2
{
	template<typename T>
	struct A
	{
		A(T tv1, T tv2)
		{
			cout << "func: A(T tv1, T tv2)" << endl;
		}

		A(T tv)
		{
			cout << "func: A(T tv)" << endl;
		}
	};
	// 隐式推断指南；
	// template<typename T>
	// A(T)->A<T>;

	// template<typename T>
	// A(T,T)->A<double>;
	// 下述两个表达式等价；
	// A aobj (10, 20); 
	// A<double> aobj(10, 20);
}


namespace _nmsp3
{
	template<typename T>
	struct B
	{
		T m_b1;
		T m_b2;
	};
	// 显示推断指南（自定义）；
	template<typename T>
	B(T)->B<T>;
	// 显示推断指南（自定义）；
	template<typename T>
	B(T,T)->B<T>;
}

int main()
{	
	// 常规模板类实例化 - 普通成员函数；
	_nmsp1::vector<int> vec1;
	vec1.m_func();
	// 常规模板类实例化 - 静态成员函数；
	_nmsp1::vector<string>::static_func();
	
	// C++17，类型推断指南；
	_nmsp1::vector vec2(12);
	vec2.m_func();
	// C++17，类型推断指南 - 隐式推断；
	_nmsp2::A<int> aobj1(10, 20);	// A<int>；
	_nmsp2::A aobj2(10, 20);		// A<int>；
	_nmsp2::A aobj3(3.14);			// A<double>；
	_nmsp2::A<int> *paobj = NULL;	// A<int>；

	// C++17，类型推断指南 - 显示推断；
	_nmsp3::B<int> bobj1;      // 明确指定模板参数类型；
	_nmsp3::B<int> bobj2{10};  // 初始化列表的方式来定义对象：m_b1(15)，m_b2(0)；
	_nmsp3::B bobj3{ 10 };     // error：cannot deduce template arguments for _nmsp3::B；
	_nmsp3::B bobj4{ 10, 20 }; // error：cannot deduce template arguments for _nmsp3::B；

	return 0;
}
