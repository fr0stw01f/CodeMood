/*************************************************************************
	>    File Name: GotW.cpp
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:38:15 PM CST
 ************************************************************************/

#include "GotW01.h"
#include "GotW02.h"

void GotW01();
void GotW02();

int main(int argc, char* argv[])
{
	GotW01();
	GotW02();

	return 0;
}

void GotW01()
{
	using namespace CodeMood;
	Widget wa;						// (a)

	Widget wb();					// (b)
	Widget wc{};					// (c)

	Widget wd(wa);					// (d)
	Widget we{wa};					// (e)

	Widget wf = wa;					// (f)
	Widget wg = {wa};				// (g)

	auto wh = wa;					// (h)
	auto wi = Widget{wa};			// (i)
}

void GotW02()
{
	using namespace CodeMood;
	{
		vector<Employee> emps;
		emps.reserve(EMPS);
		for (int i = 0; i < EMPS; ++i) {
			//stringstream ssname, ssaddr;
			//ssname << "name" << i;
			//ssaddr << "addr" << i;
			// no long need stringstream to concatenate a string with a basic type
			// use to_string() from C++11
			emps.push_back(Employee("name" + to_string(i), "addr" + to_string(i)));
		}
		//srand(0);
		//random_shuffle(begin(emps), end(emps));

		TIME(test_average(emps, find_addr_01));
		TIME(test_average(emps, find_addr_02));
		TIME(test_average(emps, find_addr_03));
		TIME(test_average(emps, find_addr_04));
		TIME(test_average(emps, find_addr_05));
		TIME(test_average(emps, find_addr_06));
	}

	cout << Employee::count_ << endl;
}
