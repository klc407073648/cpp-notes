#include <iostream>
#include <unordered_map>
#include <cstdio>
int a() { return std::puts("a"); }
int b() { return std::puts("b"); }
int c() { return std::puts("c"); }
void z(int, int, int) {}

int main()
{
	std::unordered_map<int, int> m_map;
	m_map[0] = m_map.size(); // 此处不确定插入{0, 0}，还是{0, 1}
	std::cout << "m_map[0]:" << m_map[0] << std::endl;
	
	z(a(), b(), c());       // all 6 permutations of output are allowed
    return a() + b() + c(); // all 6 permutations of output are allowed
}
