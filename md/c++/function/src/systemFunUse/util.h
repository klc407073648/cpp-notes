/**
 * @file util.h
 * @brief 常用工具类
 * @author klc
 * @date 2020-04-30
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_UTIL_H_
#define __STIBEL_UTIL_H_

#include <vector>
#include <string>
#include<stdio.h>
#include <iostream>


/**
* @brief string工具类
*/
class ShellUtil {
public:
    static void execShell(std::string cmd);
    static std::string execShellPipe(std::string cmd);
	static std::string getParamValue(std::string key , std::string fileName);
	static void modParamValue(std::string key , std::string value, std::string fileName);
};

#endif //__STIBEL_UTIL_H_
