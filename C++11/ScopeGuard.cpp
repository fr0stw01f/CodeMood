/*************************************************************************
	>    File Name: ScopeGuard.cpp
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:21:41 PM CST
 ************************************************************************/

#include "ScopeGuard.h"

CodeMood::ScopeGuard::ScopeGuard(function<void()> onScopeExit)
	:onScopeExit_(onScopeExit), dismissed_(false)
{
}


CodeMood::ScopeGuard::~ScopeGuard()
{
	if (!dismissed_)
		onScopeExit_();
}

void CodeMood::ScopeGuard::Dismiss()
{
	dismissed_ = true;
}

