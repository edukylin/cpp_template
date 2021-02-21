#include <iostream>

using namespace std;

// 6. 缺省参数
namespace _nmsp1
{			
	// 普通函数；
	int func1(int tv1, int tv2)
	{
		cout << "func: int func1(int tv1, int tv2)." << endl;
		return 1;
	}
	// 普通函数；
	int func2(int tmp1, int tmp2)
	{
		cout << "func: int func2(int tv1, int tv2)." << endl;
		return 10;
	}

	// 函数指针；
	typedef int(*FunType)(int, int);

	// 模板函数；
	template <typename T, typename F = FunType>	
	void template_func1(T tv1, T tv2, F pFunc = func1)
	{
		cout << "func: void template_func1(T tv1, T tv2, F pFunc = func1)." << endl;
		pFunc(tv1, tv2);
	}

	// 模板函数；
	template <typename T = int, typename U>
	void template_func2(U tv)
	{
		cout << "func: void template_func2(U tv)." << endl;
	}
}

// 7. 非类型模板参数
// 7.1 基本概念
// 对于模板函数，模板参数并不局限于类型，普通值也可以作为模板参数；
// 模板函数中，定义了一些具体细节未加确定的代码，直到该代码被调用时这些细节才被真正确定；
// 这里的细节可以是类型（类型模板参数，前缀使用typename/class），也可以是值（非类型模板参数）；
// 7.2 类型限制
// [a] 指定非类型模板参数的值时，必须为常量（编译阶段确定非类型模板参数的值）；
// [b] 非类型模板参数的类型有所限制（并非所有类型），可以为：整型/枚举型/指针型/左值引用等；
// [c] 非类型模板参数的类型有所限制（并非所有类型），不可为：浮点型/字符串型等；
// [d] C++17开始，支持非类型模板参数类型为auto/decltype(auto)；

// 7.3 比较奇怪的语法
// [a] 不管类型模板参数还是非类型模板参数，代码中没有用到时，参数名可以省略；
// [b] 类型前可以使用关键字typename来修饰以明确标识一个类型（却别于变量名），一般跟模板有关的类型名前面是需要typename；
namespace _nmsp2
{
	template <typename T, typename U, int val = 100>
	// template <typename T, typename U, auto val = 100>
	auto add(T tv1, U tv2)
	{
		cout << "func: auto add(T tv1,U tv2)." << endl;
		return tv1 + tv2 + val;
	}

	double g_pi = 3.14; //全局量
	// template <double p> 
	// error: floating - point template parameter is nonstandard
	template <double *p>
	void func1()
	{
		cout << "func: void func1()." << endl;
	}
	

	//-------------------
	// template <typename T,int value>
	// template <typename T, typename int value>
	template <typename, int>
	auto func2()
	{
		cout << "func: auto func2()." << endl;
	}
}

int main()
{	
	// 缺省类型参数；
	_nmsp1::template_func1(10, 20);
	_nmsp1::template_func1(10, 20, _nmsp1::func2);
	_nmsp1::template_func2(10);

	// 非类型模板参数
	cout << _nmsp2::add<float, float>(3.14f, 2.72f) << endl;
	cout << _nmsp2::add<float, float, 200>(3.14f, 2.72f) << endl;
	const int val = 300; // 不能为：int val = 300；
	cout << _nmsp2::add<float, float, val>(3.14f, 2.72f) << endl;
	_nmsp2::func1<&_nmsp2::g_pi>();
	_nmsp2::func2<int,45>();

	return 0;
}

