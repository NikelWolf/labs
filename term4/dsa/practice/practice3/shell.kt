package dsa.practice.third

fun shellSort(o_array: Array<Int>) {
    var array: Array<Int> = o_array

    var inner: Int
    var outer: Int
    var temp: Int
    var comp: Int = 0

    var h = 1
    while (h <= array.size / 3) {
        h = h * 3 + 1
    }
    while (h > 0) {
        outer = h
        while (outer < array.size) {
            temp = array[outer]
            inner = outer

            while (inner > h - 1 && array[inner - h] >= temp) {
                array[inner] = array[inner - h]
                inner -= h
                comp++
            }
            array[inner] = temp
            outer++
        }
        h = (h - 1) / 3
    }

    print("\nShell Sort: ${array.asList()}")
    print("\nShell comparisons: $comp\n")
}
