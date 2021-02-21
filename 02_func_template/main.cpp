#include <iostream>

using namespace std;

// 4. 模板函数重载（对比普通函数重载）
// 4.1 不同模板函数之间构成重载：模板函数名称相同，但是模板参数数量或者类型不同;
// 4.2 模板函数和普通函数构成重载：条件都符合时，优先匹配普通函数；
// 4.3 如何匹配最优的模板函数/普通函数，编译器内部有比较复杂的排序规则，且在不断更新；
namespace _nmsp1
{
	// 模板函数：普通版本；
	template<typename T>
	void func(T tv)
	{
		std::cout << "func: void func(T tv)." << std::endl;
	}
	// 模板函数：指针版本；
	template<typename T>
	void func(T* tv)
	{
		std::cout << "func: void func(T* tv)." << std::endl;
	}
	// 普通函数；
	void func(int tv)
	{
		std::cout << "func: void func(int tv)." << std::endl;
	}
}

// 5. 特化（任何针对模板参数进一步进行条件限制设计的特化版本）
// 5.1 泛化与特化；
// 泛化：通用的模板函数，所有模板参数类型都未定义，直到到使用时才明确；
// 特化：针对模板参数进一步的进行条件限制所设计的特化版本（某一特定类型，进行特别的声明或定义）；
// 特化版本往往是泛化版本的一个子集，特化分为全特化和偏特化；
// 5.2 全特化，就是全部特化，即针对所有的模板参数进行特化（所有的模板参数都用具体的类型来代替），所构成的一个特殊的版本；
// 全特化，实际上等价于实例化一个函数模板，但是并不等价于一个函数重载；
// 全特化范例：void func<int ,double>(int& tv1, double& tv2) {......}；
// 重载范例：void func(int& tv1, double& tv2) {......}；
// 编译器匹配顺序：普通函数->模板函数特化版本->模板函数泛化版本；
// 5.3 偏特化，就啊是局部特化，即针对部分模板参数进行特化（仍然具有模板参数的特化）；
// 偏特化应用范围：偏特化机制仅能适用于模板类，不能适用于模板函数（成员函数/普通函数）；
// 偏特化实现类型：一种是模板参数数量的偏特化，另一种是模板参数范围上的偏特化；
// [a] 基于模板参数数量的偏特化：
// 例如：模板函数func<>，，第一个模板参数类型特化为int，第二个模板参数不特化；
// 实际上，从模板参数数量上来讲，函数模板不能偏特化。否则会导致编译错误。
// [b] 基于模板参数范围的偏特化：
// 缩小特化类型范围，例如：int->const int，T->T*，T->T&，T->T&&；
// [c] 模板函数类型的偏特化时，基于模板参数数量的偏特化会导致编译错误（可通过重载实现），而基于模板参数范围的偏特化则构成重载；
namespace _nmsp2
{
	// 泛化版本；
	template <typename T,typename U>	// T = int, U = int;
	void func(T& tv1, U& tv2)			// tv1 = int &, tv2 = int &;
	{
		cout << "func: void func(T& tv1, U& tv2)." << endl;
	}

	// 全特化版本；
	template <> // <>中里面为空
	void func<int, double>(int& tv1, double& tv2)
	// void tfunc(int& tv1, double& tv2)：可以省略<int, double>，因为根据实参类型可以完全推导出T和U的类型；
	{
		cout << "func: void func<int, double>(int& tv1, double& tv2)." << endl;
	}

	// 重载函数;
	void func(int& tv1, double& t2)
	{
		cout << "func: void func(int& tv1, double& tv2)." << endl;
	}

	// 模板函数 - 基于模板参数数量的偏特化（编译报错）；
	// template <typename U> 
	// void tfunc<double, U>(double& tmprv, U& tmprv2)
	// {
	//		cout << "func: void func(int& tmprv, double& tmprv2)" << endl;
	// }

	// 模板函数重载 - 类似于基于模板参数数量的偏特化；
	template <typename U>
	void func(int& tv1, U& tv2)
	{
		cout << "func: void func(int& tv1, U& tv2)." << endl;
	}

	// 模板函数 - 基于模板参数范围的偏特化（构成重载）；
	template <typename T, typename U>
	void func(const T& tv1, U& tv2)
	{
		cout << "func: void func(const T& tv1, U& t2)." << endl;
	}
}


int main()
{
	int iNum1, * pNum1 = &iNum1;
	double dNum1 = 3.14;

	// 模板函数重载；
	_nmsp1::func(iNum1); // 普通函数重载；
	_nmsp1::func(pNum1); // 模板函数重载（指针）；
	_nmsp1::func(dNum1); // 模板函数（基础）；
	
	// 模板函数泛化与特化；
	_nmsp2::func(iNum1, iNum1);					// 模板函数泛化版本；
	_nmsp2::func<int, double>(iNum1, dNum1);	// 模板函数全特化版本(与重载版本冲突)；
	_nmsp2::func(iNum1, dNum1);					// 普通函数重载版本（参数数量）；
	_nmsp2::func("Hello,World.", iNum1);		// 模板函数重载版本（参数范围）；

	return 0;
}
