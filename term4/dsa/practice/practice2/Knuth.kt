package dsa.practice.second

fun getIndexArray(stringImage: String): IntArray {
    var table = IntArray(stringImage.length)
    table[0] = 0

    for (i in 1 until table.size) {
        var k = table[i - 1]

        while (stringImage[k] != stringImage[i] && k > 0) {
            k = table[k - 1]
        }
        if (stringImage[k] == stringImage[i]) {
            table[i] = ++k
        } else {
            table[i] = 0
        }
    }

    return table
}

fun processString(text: String, image: String, imageTable: IntArray) {
    var imageIndex = 0
    var found = false
    var position = 0
    var iter = 0

    for (i in text.indices) {
        while (text[i] != image[imageIndex] && imageIndex > 0) {
            imageIndex = imageTable[imageIndex - 1]
        }
        if (image[imageIndex] == text[i]) {
            imageIndex += 1
            if (imageIndex == image.length) {
                position = i - imageIndex + 1
                imageIndex = imageTable[imageIndex - 1]
                found = true
            }
        } else imageIndex = 0
        iter++
    }

    print("\nNumber of KNUTH Iterations: $iter")
    if (found) print("\nFound string \"$image\" in text \"$text\" at position $position")
    else print("\n\nPattern $image not found")
}
