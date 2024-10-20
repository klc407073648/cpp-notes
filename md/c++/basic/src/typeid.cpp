if(Derived *dp = dynamic_cast<Derived*>(bp)){
    // 使用dp指向的 Derived 对象
}
else{
    // 使用bp指向的 Base 对象
}

if(typeid(*bp) == typeid(*dp)){
    //bp 和 dp指向同一类型对象
}

if(typeid(*bp) == typeid(Derived)){
    //bp 实际指向Derived对象
}

if(typeid(bp) == typeid(Derived)){
    //永远不被指向，bp是指向Base的指针
}