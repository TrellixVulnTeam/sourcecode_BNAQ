/*!
 @file		SingletonManagerCenter.h
 @author    kongxilong
 @param		Email: hzkongxilong@163.org
 @param		Copyright (c) 2016 
 @date		2016-6-5
 @brief		�������������
 */

#pragma once

#include "ISingleton.h"

class SingletonManagerCenter : public SingletonManagerBase
{

	
public:
	//����Ϊ������
    DECLARE_SINGLETON_CLASS(SingletonManagerCenter)
};