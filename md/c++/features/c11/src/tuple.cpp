void testTuple()
{
    std::tuple<int, char> first;                             // 1)   first{}
    std::tuple<int, char> second(first);                     // 2)   second{}
    std::tuple<int, char> third(std::make_pair(20, 'b'));   // 3)   third{20,'b'}
    std::tuple<long, char> fourth(third);                    // 4)的左值方式, fourth{20,'b'}
    std::tuple<int, char> fifth(10, 'a');                    // 5)的右值方式, fifth{10.'a'}
    std::tuple<int, char,string> sixth(std::make_tuple(30, 'c',"address"));    // 6)的右值方式, sixth{30, 'c',"address"}
    
    std::cout << std::get<0>(fourth) << " " << std::get<1>(fourth) << std::endl;
    std::cout << std::get<0>(fifth) << " " << std::get<1>(fifth) << std::endl;
    std::cout << std::get<0>(sixth) << " " << std::get<1>(sixth) << " " << std::get<2>(sixth) << std::endl;
    
    int size = std::tuple_size<decltype(sixth)>::value;
    std::cout << size << std::endl;
}