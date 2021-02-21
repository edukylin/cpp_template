#include <iostream>

using namespace std;

// 1. 基本范例
// [a] 模板（模板函数/模板类）的定义，必须以关键字template开始；
// [b] 关键字typename/calss用来修饰类型模板参数（class此处并不表示类）；
// [c] 模板参数，代表一个类型，可以换成其他任意标识符（T，只是一种习惯）；

// 2. 实例化
// 2.1 实例化基本概念
// 实例化：编译时，编译器用具体的类型代替类型模板参数的过程就叫做实例化（也叫代码生成器）；
// 2.2 实例化本质探究
// .obj文件格式为COFF（Common Object File Format，通用对象文件格式）；
// Developer Command Prompt for VS 2019 > dumpbin /all main.obj > main.txt
// int  sub<int>(int,int)
// double sub<double>(double,double)
// 实例化之后的函数名分别叫做sub<int>和sub<double>；
// 2.3 实例化注意事项
// 模板函数实例化之后的函数名包含三部分：模板名，<>，模板参数具体类型；
// 编译阶段，编译器就会查看函数模板的函数体部分，来确定能否针参数类型进行实例化；
// 编译阶段，编译器需要能够找到函数模板的函数体部分（即，函数模板必须定义在头文件中）；

// 3. 模板参数推断
// 3.1 常规的参数推断
// <>可以只指定一部分模板参数的类型，另外一部分模板参数的类型可以通过调用时给的实参来推断；
// auto，代替函数模板返回类型；
// decltype，与auto结合构成返回类型后置语法；
// 3.2 各种推断的比较以及空模板参数列表的推断
// 自动类型推断；
// 指定类型模板参数，优先级比自动类型推断高；
// 指定空模板参数列表，用于指定调用模板函数，而非普通函数；

namespace _nmsp1
{
	template <typename T>
	T sub(T tv1, T tv2)
	{
		return tv1 - tv2;
	}

	// template <typename T, typename U, typename V>
	// V add(T tv1, U tv2)
	// {
	//	return tv1 + tv2;
	// }
	// cout << _nmsp1::add<int,double,double>(7, 3.14) << endl;

	// template <typename V, typename T, typename U>
	// V add(T tv1, U tv2)
	// {
	//	return tv1 + tv2;
	// }
	// cout << _nmsp1::add<double>(7, 3.14) << endl;

	// auto，用于推导返回值类型；
	// template <typename T, typename U>
	// auto add(T tv1, U tv2) 
	// {
	//	 return tv1 + tv2;
	// }

	// 返回类型后置语法，auto只是返回类型后置语法的组成部分，并没有类型推导的含义；
	template <typename T, typename U>
	auto add(T tv1, U tv2) -> decltype(tv1 + tv2)
	{
		return tv1 + tv2;
	}

	template <typename T>
	T triple(T tv)
	{
		cout << "triple template function." << endl;
		return tv * 3;
	}

	double triple(double tv)
	{
		cout << "triple ordinary function." << endl;
		return tv * 3;
	}
}

int main()
{
	cout << _nmsp1::sub(7, 3) << endl;
	cout << _nmsp1::sub(3.14, 2.72) << endl;
	// 函数模板中所有运算，参数类型必须支持；
	// int subv1 = _nmsp1::sub(string("hello"), string("world"));
	// 编译阶段，编译器就会查看函数模板的函数体部分，来确定能否针参数类型进行实例化。
	// cout << _nmsp1::sub(string("hello"), string("world")) << endl;

	// 参数类型保持一致，不能依靠编译器推测；
	// cout << _nmsp1::sub(7, 3.14) << endl;
	// 参数类型不一致时，可以使用强制类型转换；
	// cout << _nmsp1::sub(double(7), 3.14) << endl;
	// 参数类型不一致时，可以使用显示实例化；
	cout << _nmsp1::sub<double>(7, 3.14) << endl;

	// error: '_nmsp1::add' - no matching overloaded function found;
	// cout << _nmsp1::add(7, 3,14) << endl;
	// cout << _nmsp1::add<..., ..., double>(7, 3.14) << endl;
	// cout << _nmsp1::add<int,double,double>(7, 3.14) << endl;
	// cout << _nmsp1::add<double>(7, 3.14) << endl;
	cout << _nmsp1::add(7, 3.14) << endl;

	// 类型推断； 
	cout << _nmsp1::triple(15) << endl; 
	// 指定类型（相对于类型推断，优先级更高）；
	cout << _nmsp1::triple<int>(3.14) << endl;
	// 编译器而言，模板函数和普通函数都匹配的前提下，会优先调用普通函数；
	cout << _nmsp1::triple(3.14) << endl;
	// <>，指明调用模板函数，而非普通函数（仅此意义）；
	cout << _nmsp1::triple<>(3.14) << endl; 

	return 0;
}