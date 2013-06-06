#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void say_hello();
struct is_even
{
	bool operator()(int x)
	{
		return x%2 == 0;
	}
};

int main()
{
	std::vector<int> vi{1, 2, 3, 4, 5};
	std::copy_if(std::begin(vi), std::end(vi), std::ostream_iterator<int>(std::cout, " "), is_even());	
	std::cout << std::endl;
	say_hello();
}
