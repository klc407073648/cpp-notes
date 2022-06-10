template <typename Val>
using str_map_t = std::map<std::string, Val>;

//可以统一处理以下场景
//typedef std::map<std::string, int> map_int_t;
//typedef std::map<std::string, std::string> map_str_t;

void testUsing()
{
	str_map_t<int> map1;
	str_map_t<std::string> map2;
	
	map1["age"]=27;
	map2["address"]="NJ";
	
	std::cout<<"map1[\"age\"]:"<<map1["age"]<<std::endl;
	std::cout<<"map2[\"address\"]:"<<map2["address"]<<std::endl;
}