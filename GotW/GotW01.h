/*************************************************************************
	>    File Name: GotW01.h
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:38:38 PM CST
 ************************************************************************/

#ifndef GOTW01_H
#define GOTW01_H

#include <initializer_list>

namespace CodeMood {
	struct Widget
	{
		Widget() = default;
		Widget(const Widget&) = default;
		Widget& operator=(const Widget&) = default;
		/*Widget(const std::initializer_list& x)
		{

		}*/
	};
}

#endif //!GOTW01_H
