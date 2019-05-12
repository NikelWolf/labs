package dsa.practice.third

fun bubbleSort(o_array: Array<Int>) {
    var array: Array<Int> = o_array
    var comp: Int = 0
    var swappedElements: Boolean
    do {
        swappedElements = false
        for (i in 0..o_array.size - 2) {
            if (o_array[i] > o_array[i + 1]) {
                swap(o_array, i, i + 1)
                swappedElements = true
            }
            comp++
        }
    } while (swappedElements)
    print("\nBubble Sort: ${array.asList()}")
    print("\nBubble comparisons: $comp\n")
}
