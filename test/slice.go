package main

import "fmt"

func main() {
	arr := [...]int{0, 1, 2, 3, 4, 5, 6, 7}
	fmt.Println("arr: ", arr) // output：arr:  [0 1 2 3 4 5 6 7]
	s1 := arr[2:6]
	s2 := s1[3:5] //其实s1的index只有0 1 2 3, 这里的3:5是3和4, 引用的是原始arr
	fmt.Println("s1: ", s1) // output：s1:  [2 3 4 5]
	fmt.Println("s2: ", s2, len(s2)) // output：s2:  [5 6]
	s3 := append(s2, 10)
	s4 := append(s3, 11)
	s5 := append(s4, 12)
	fmt.Println("s3: ", s3)   // output：s3:  [5 6 10]
	fmt.Println("s4: ", s4)   // output：s4:  [5 6 10 11]
	fmt.Println("s5: ", s5)   // output：s5:  [5 6 10 11 12]
	fmt.Println("arr: ", arr) // output：arr:  [0 1 2 3 4 5 6 10]
    s := make(chan int)
    s <- 1
}

