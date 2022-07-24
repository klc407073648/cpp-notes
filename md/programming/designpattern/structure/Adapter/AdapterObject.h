#ifndef _ADAPTEROBJECT_H_
#define _ADAPTEROBJECT_H_
//对象模式的 Adapter 实现
class TargetObject
{
public:
    TargetObject();
    virtual ~TargetObject();
    virtual void Request();

protected:
private:
};

class AdapteeObject
{
public:
    AdapteeObject();
    ~AdapteeObject();
    void SpecificRequest();

protected:
private:
};
class AdapterObject : public TargetObject
{
public:
    AdapterObject(AdapteeObject *ade);
    ~AdapterObject();
    void Request();

protected:
private:
    AdapteeObject *_ade;
};

#endif //~_ADAPTEROBJECT_H_
