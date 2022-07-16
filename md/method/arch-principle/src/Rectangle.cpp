struct Rectangle
{
  int width;
  int height;
};

Rectangle r;
r.width = 2;
r.height = 1;

int area = r.width * r.height;

struct Rectangle
{
  Rectangle(int width, int height) : width(width), height(height)
  {
  }
  int calcArea() { return width * height; }

private:
  int width;
  int height;
};

Rectangle r(2, 1);
int area = r.calcArea();