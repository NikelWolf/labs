package dsa.practice.third

fun swap(arr: Array<Int>, i: Int, j: Int): Array<Int> {
    val tmp: Int = arr[i]
    arr[i] = arr[j]
    arr[j] = tmp
    return arr
}
