package dsa.practice.third

fun findMinElements(array: Array<Int>) {
    print("\nEnter the desired number of minimal elements: ")
    val n = readLine()!!.toInt()

    if (n > array.size || n < 0) print("\nInvalid number of elements\n")

    else {
        array.sortedArray()
        for (i in 0..n) {
            print("${array.get(i)} ")
        }
    }
}
