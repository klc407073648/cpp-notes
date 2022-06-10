void isnull(void *c){
    cout << "void*c" << endl;
}
void isnull(int n){
    cout << "int n" << endl;
}

void testNullptr()
{
    cout<<"testNullptr:"<<endl;

    isnull(0); 
    //isnull(NULL); // C++ 98/03 标准中 输出 int n
    isnull(nullptr);
}