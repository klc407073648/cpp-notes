#ifndef _PRODUCT_H_
#define _PRODUCT_H_
class Product
{
public:
    Product();
    ~Product();
    void ProducePart();

protected:
private:
};

class ProductPart
{
public:
    ProductPart();
    ~ProductPart();
    ProductPart *BuildPart();

protected:
private:
};
#endif //~_PRODUCT_H_