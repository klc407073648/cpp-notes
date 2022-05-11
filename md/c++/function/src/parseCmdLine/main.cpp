#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

//解析ip, port, msg.
void testFun1(int argc, char *argv[])
{
    std::string ip = "127.0.0.1";
	int port = 8080;
	std::string msg = "Hello World";
	
	int opt;
    const char *str = "i:p:m:";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'i':
        {
            ip = optarg;
            break;
        }
        case 'p':
        {
            port = atoi(optarg);
            break;
        }
        case 'm':
        {
            msg = optarg;
            break;
        }
        default:
            break;
        }
    }
	cout<<"ip: "<<ip<<endl;
	cout<<"port: "<<port<<endl;
	cout<<"msg: "<<msg<<endl;
}

//解析2ab:c:de::
void testFun2(int argc, char *argv[])
{

	int opt;
    const char *str = "2ab:c:de::";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
            case '2':
				cout<<"HAVE option: -2"<<endl;
                break;
			case 'a':
				cout<<"HAVE option: -a"<<endl;
                break;
            case 'b':
                cout<<"HAVE option: -b"<<endl;
				cout<<"The value of -b is "<<optarg<<endl;
				break;
			case 'c':
				cout<<"HAVE option: -c"<<endl;
                cout<<"The value of -c is "<<optarg<<endl; 
                break;
            case 'd':
                cout<<"HAVE option: -d"<<endl;
				 break;
			case 'e':
				cout<<"HAVE option: -e"<<endl;
                cout<<"The value of -e is "<<optarg<<endl;
                break;
			default:
				break;
        }
    }
}

int main(int argc, char *argv[])
{
	//testFun1(argc,argv);
	testFun2(argc,argv);
    return 0;
}

