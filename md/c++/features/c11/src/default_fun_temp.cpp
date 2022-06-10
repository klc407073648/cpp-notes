template <typename R = int, typename T, typename U>
R func(T v1,U v2)
{
    return v1+v2;
}

void testFunTemplate()
{
    auto r1=func(5.5,10);                    // R=int, T=double, U=int
    auto r2=func<double>(5.5,10);            // R=double, T=double, U=int
    auto r3=func<double, int, int>(5.5,10);  // R=double, T=int, U=int
	
	cout<<"r1:"<<r1<<endl;
	cout<<"r2:"<<r2<<endl;
	cout<<"r3:"<<r3<<endl;
}