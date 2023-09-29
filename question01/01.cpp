#include <iostream>
#include <functional> 

//1)
//1. float (*f)(float, float)
//2. std::function<float(float, float)> f
//3. std::function<int(float, float)> f

//2)
float applyF1(float a, float b, float (*f)(float, float))
{
	return f(a, b);
}
float applyF2(float a, float b, std::function<float(float, float)> f)
{
	return f(a, b);
}
float applyF3(float a, float b, std::function<int(float, float)> f)
{
	return f(a, b);
}

int main(int argc, char* argv[])
{
	float fNum = 0;
	//3)
	// calculate fNum = (2 * 3) + (4 * 5) + 6
	fNum = applyF1( applyF1( 2, 3, [](float x, float y) -> float {return x * y; }), applyF1( applyF1( 4, 5, [](float x, float y) -> float {return x * y; }), 6, [](float x, float y) -> float {return x + y; }), [](float x, float y) -> float {return x + y; }); // (4 * 5) + 6
	
	// std::cout << fNum; 32 was printed
	
	return 0;
}