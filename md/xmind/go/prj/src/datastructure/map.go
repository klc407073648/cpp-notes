package main

import "fmt"
import "sort"

func main() {

    //基础使用
    var mapLit map[string]int
    var mapAssigned map[string]int
    mapLit = map[string]int{"one": 1, "two": 2}
    mapCreated := make(map[string]float32) //mapCreated := map[string]float32{}
    mapAssigned = mapLit //mapAssigned 是 mapList 的引用，对 mapAssigned 的修改也会影响到 mapLit 的值。
    mapCreated["key1"] = 4.5
    mapCreated["key2"] = 3.14159
    mapAssigned["two"] = 3
    fmt.Printf("Map literal at \"one\" is: %d\n", mapLit["one"])
    fmt.Printf("Map created at \"key2\" is: %f\n", mapCreated["key2"])
    fmt.Printf("Map assigned at \"two\" is: %d\n", mapLit["two"])
    fmt.Printf("Map literal at \"ten\" is: %d\n", mapLit["ten"])
    
    //用切片作为 map 的值,多值映射
    mp1 := make(map[int][]int)
    mp1[1] = []int{1, 2, 3}
    mp1[1] = append(mp1[1], []int{4,5,6}...)
    
    fmt.Printf("mp1 at 1 is: %d\n", mp1[1])
    
    //遍历map
    scene := make(map[string]int)
    scene["route"] = 66
    scene["brazil"] = 4
    scene["china"] = 960
    for k, v := range scene {
        fmt.Println(k, v)
    }
    
    //对k进行排序
    // 声明一个切片保存map数据
    var sceneList []string
    // 将map数据遍历复制到切片中
    for k := range scene {
        sceneList = append(sceneList, k)
    }
    // 对切片进行排序
    sort.Strings(sceneList)
    // 输出
    fmt.Println(sceneList)
    
    //删除元素
    delete(scene, "brazil")
    for k, v := range scene {
        fmt.Println(k, v)
    }
    capital, ok := scene["route"] /*如果确定是真实的,则存在,否则不存在 */
    fmt.Println(capital)
    fmt.Println(ok)
}
