package main

import (
	"fmt"
	"reflect"
)

// 定义结构体
type dummy struct {
	a int
	b string
	// 嵌入字段
	float32
	bool
	next *dummy
}

func main() {
	// 值包装结构体
	d := reflect.ValueOf(dummy{
		next: &dummy{},
	})
	// 获取字段数量
	fmt.Println("NumField", d.NumField())
	// 获取索引为2的字段(float32字段)
	floatField := d.Field(2)
	// 输出字段类型
	fmt.Println("Field", floatField.Type())
	// 根据名字查找字段
	fmt.Println("FieldByName(\"b\").Type", d.FieldByName("b").Type())
	// 根据索引查找值中, next字段的int字段的值
	fmt.Println("FieldByIndex([]int{4, 0}).Type()", d.FieldByIndex([]int{4, 0}).Type())
}
