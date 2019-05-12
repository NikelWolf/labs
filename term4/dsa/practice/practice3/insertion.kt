package dsa.practice.third

fun insertionSort(o_array: Array<Int>) {
    var array: Array<Int> = o_array
    var comp: Int = 0
    for (j in 1..array.size - 1) {
        var i = j - 1
        val processedValue = array[j]
        while ((i >= 0) && (array[i] > processedValue)) {
            array[i + 1] = array[i]
            i--
        }
        comp++
        array[i + 1] = processedValue
    }
    print("\nInsertion Sort: ${array.asList()}")
    print("\nInsertion comparisons: $comp\n")
}
