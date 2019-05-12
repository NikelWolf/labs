package dsa.practice.third

fun selectionSort(o_array: Array<Int>) {
    var array: Array<Int> = o_array

    var comp: Int = 0
    for (unsortedPartFirstIndex in 0..array.size - 1) {
        var minNumberIndex = unsortedPartFirstIndex
        comp++

        for (unsortedPartCurrentIndex in unsortedPartFirstIndex..array.size - 1) {
            if (array[unsortedPartCurrentIndex] < array[minNumberIndex]) {
                minNumberIndex = unsortedPartCurrentIndex
            }
        }
        if (minNumberIndex != unsortedPartFirstIndex) {
            swap(array, unsortedPartFirstIndex, minNumberIndex)
        }
        comp++
    }
    print("\nSelection Sort: ${array.asList()}")
    print("\nSelection comparisons: $comp\n")
}
