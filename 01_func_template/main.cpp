#include <iostream>

using namespace std;

// 1. ��������
// [a] ģ�壨ģ�庯��/ģ���ࣩ�Ķ��壬�����Թؼ���template��ʼ��
// [b] �ؼ���typename/calss������������ģ�������class�˴�������ʾ�ࣩ��
// [c] ģ�����������һ�����ͣ����Ի������������ʶ����T��ֻ��һ��ϰ�ߣ���

// 2. ʵ����
// 2.1 ʵ������������
// ʵ����������ʱ���������þ�������ʹ�������ģ������Ĺ��̾ͽ���ʵ������Ҳ�д�������������
// 2.2 ʵ��������̽��
// .obj�ļ���ʽΪCOFF��Common Object File Format��ͨ�ö����ļ���ʽ����
// Developer Command Prompt for VS 2019 > dumpbin /all main.obj > main.txt
// int  sub<int>(int,int)
// double sub<double>(double,double)
// ʵ����֮��ĺ������ֱ����sub<int>��sub<double>��
// 2.3 ʵ����ע������
// ģ�庯��ʵ����֮��ĺ��������������֣�ģ������<>��ģ������������ͣ�
// ����׶Σ��������ͻ�鿴����ģ��ĺ����岿�֣���ȷ���ܷ���������ͽ���ʵ������
// ����׶Σ���������Ҫ�ܹ��ҵ�����ģ��ĺ����岿�֣���������ģ����붨����ͷ�ļ��У���

// 3. ģ������ƶ�
// 3.1 ����Ĳ����ƶ�
// <>����ָֻ��һ����ģ����������ͣ�����һ����ģ����������Ϳ���ͨ������ʱ����ʵ�����ƶϣ�
// auto�����溯��ģ�巵�����ͣ�
// decltype����auto��Ϲ��ɷ������ͺ����﷨��
// 3.2 �����ƶϵıȽ��Լ���ģ������б���ƶ�
// �Զ������ƶϣ�
// ָ������ģ����������ȼ����Զ������ƶϸߣ�
// ָ����ģ������б�����ָ������ģ�庯����������ͨ������

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

	// auto�������Ƶ�����ֵ���ͣ�
	// template <typename T, typename U>
	// auto add(T tv1, U tv2) 
	// {
	//	 return tv1 + tv2;
	// }

	// �������ͺ����﷨��autoֻ�Ƿ������ͺ����﷨����ɲ��֣���û�������Ƶ��ĺ��壻
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
	// ����ģ�����������㣬�������ͱ���֧�֣�
	// int subv1 = _nmsp1::sub(string("hello"), string("world"));
	// ����׶Σ��������ͻ�鿴����ģ��ĺ����岿�֣���ȷ���ܷ���������ͽ���ʵ������
	// cout << _nmsp1::sub(string("hello"), string("world")) << endl;

	// �������ͱ���һ�£����������������Ʋ⣻
	// cout << _nmsp1::sub(7, 3.14) << endl;
	// �������Ͳ�һ��ʱ������ʹ��ǿ������ת����
	// cout << _nmsp1::sub(double(7), 3.14) << endl;
	// �������Ͳ�һ��ʱ������ʹ����ʾʵ������
	cout << _nmsp1::sub<double>(7, 3.14) << endl;

	// error: '_nmsp1::add' - no matching overloaded function found;
	// cout << _nmsp1::add(7, 3,14) << endl;
	// cout << _nmsp1::add<..., ..., double>(7, 3.14) << endl;
	// cout << _nmsp1::add<int,double,double>(7, 3.14) << endl;
	// cout << _nmsp1::add<double>(7, 3.14) << endl;
	cout << _nmsp1::add(7, 3.14) << endl;

	// �����ƶϣ� 
	cout << _nmsp1::triple(15) << endl; 
	// ָ�����ͣ�����������ƶϣ����ȼ����ߣ���
	cout << _nmsp1::triple<int>(3.14) << endl;
	// ���������ԣ�ģ�庯������ͨ������ƥ���ǰ���£������ȵ�����ͨ������
	cout << _nmsp1::triple(3.14) << endl;
	// <>��ָ������ģ�庯����������ͨ�������������壩��
	cout << _nmsp1::triple<>(3.14) << endl; 

	return 0;
}