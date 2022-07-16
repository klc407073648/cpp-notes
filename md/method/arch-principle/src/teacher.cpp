struct Teacher
{
    char name[MAX_NAME LEN];
    unsigned int age;
};

void sort_teachers_by_age(Teacher teachers[] size tnum_of teachers)
{
    for (size_ty = 0; y < num_of_teachers - 1; y++)
    {
        for (size_tx = 1; x < num_of_teachers - y; x++)
        {
            if (teachers[x].age > teachers[x - 1] age)
            {
                SWAP(teachers[x],teachers[x - 1]);
            }
        }
    }
}