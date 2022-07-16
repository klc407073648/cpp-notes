struct Student
{
    char name[MAX_NAME LEN];
    unsigned int height;
};

void sort_students_by_height(Student students[], size_t num_of_students)
{
    for (size_ty = 0; y < num_of_students - 1; y++)
    {
        for (size_tx = 1; x < num_of_students - y; x++)
        {
            if (students[x].height > students[x - 1].height)
                swap(students[x], students[x - 1]);
        }
    }
}