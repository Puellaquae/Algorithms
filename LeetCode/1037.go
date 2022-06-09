package main

func isBoomerang(points [][]int) bool {
	var v1 = []int{points[1][0] - points[0][0], points[1][1] - points[0][1]}
	var v2 = []int{points[1][0] - points[2][0], points[1][1] - points[2][1]}
	return v1[1]*v2[0]-v1[0]*v2[1] != 0
}

func main() {
	println(isBoomerang([][]int{{1, 1}, {2, 3}, {3, 2}}))
	println(isBoomerang([][]int{{1, 1}, {2, 2}, {3, 3}}))
}
