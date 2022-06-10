// C++17之前
namespace A {
namespace B {
namespace C {
void foo() {}
} // namespace C
} // namespace B
} // namespace A

// C++17
namespace A::B::C {
void foo() {}
} // namespace A::B::C
