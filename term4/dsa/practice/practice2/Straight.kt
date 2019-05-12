package dsa.practice.second

fun straightSearch(text: String, pattern: String) {
    var i = -1
    var iter = 0
    val n = text.length
    val m = pattern.length

    do {
        i++
        var j = 0
        while ((j <m) && (text[i + j] == pattern[j])) {
            j++
        }
        iter++
    } while ((j != m) && (i <n - m))
        print("\n\n Straight search found pattern \"$pattern\" at $i, Number of Iterations: $iter")
}
