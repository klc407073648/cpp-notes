#include "util.h"

void ShellUtil::execShell(std::string cmd)
{
	system(cmd.c_str());
}

std::string ShellUtil::execShellPipe(std::string cmd)
{
	char res[1024]={0};
	 
	FILE *fp = popen(cmd.c_str(),"r");
	
	if( fp != NULL)
	{
		//fgets( res, sizeof(res), fp ); //遇到\n终止复制
		fread( res, sizeof(char), sizeof(res), fp );
		pclose(fp);
	}
	
	return res;
}

std::string ShellUtil::getParamValue(std::string key , std::string fileName)
{
	std::string  cmd = "grep " + key + " " + fileName + " | cut -d \"=\" -f2";
	std::string  value = execShellPipe(cmd);
	return value;
}

void ShellUtil::modParamValue(std::string key , std::string value, std::string fileName)
{
	std::string relpaceline = key + "=" + value ;
	std::string cmd = "sed -i 's/^" + key + "=.*/" + relpaceline + "/g' " + fileName;
	execShell(cmd);
}

