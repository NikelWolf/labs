package dsa.practice.second

fun getWrongArray(stringImage: String): IntArray {
    var m = stringImage.length
    var d = IntArray(m)

    var k = -1
    var j = 0

    while (j < stringImage.length) {
        while ((k >= 0) && (stringImage[k] != stringImage[k])) {
            k = d[k]
            j++
            k++
            if (stringImage[j] == stringImage[k]) {
                d[j] = d[k]
            } else d[j] = k
        }
    }
    return d
}

fun processWrongString(text: String, image: String, imageTable: IntArray) {
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

    print("\n Number of KNUTH Iterations: $iter")
    if (found) print("\nFound string \"$image\" in text \"$text\" at position $position")
    else print("\n\nPattern $image not found")
}
