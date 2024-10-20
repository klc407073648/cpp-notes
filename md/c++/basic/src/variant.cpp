#include <variant>
#include <iostream>
#include <string>

int main()
{
    std::variant<int, double, std::string> value;
    
    value = 10;
    std::cout << "The value is an integer: " << std::get<int>(value) << std::endl;
    
    value = 3.14159;
    std::cout << "The value is a double: " << std::get<double>(value) << std::endl;
    
    value = "hello";
    std::cout << "The value is a string: " << std::get<std::string>(value) << std::endl;
    
    // value = true;        // Compilation error: cannot convert type bool to any of the alternative types
    // std::get<int>(value) // std::bad_variant_access exception: value holds a different type
    
    return 0;
}