void testForLoop()
{
    char arc[] = "abcdefg";
    // for循环遍历普通数组
    for (char ch : arc)
    {
        cout << ch;
    }
    cout << endl;
    vector<char> myvector(arc, arc + 23);
    // for循环遍历 vector 容器
    for (auto ch : myvector)
    {
        cout << ch;
    }
    cout << endl;
}