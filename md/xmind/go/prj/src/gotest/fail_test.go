package code11_3

import (
	"fmt"
	"testing"
)

func TestFail(t *testing.T) {
	fmt.Println("before fail")
	t.Fail()
	fmt.Println("after fail")
}
