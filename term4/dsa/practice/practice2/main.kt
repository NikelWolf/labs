package dsa.practice.second

fun main(args: Array<String>) {

    print("Enter your text: ")
    val text = readLine()
    print("Enter your pattern: ")
    val image = readLine()

    var imageTable: IntArray = getIndexArray(image.toString())
    println("\nTable: $image")
    for (i in imageTable) {
        print(" $i")
    }

    processString(text.toString(), image.toString(), imageTable)

    var matches = BoyerMoore.match(image!!, text!!)
    for (integer in matches) println("\nBoyer-Moore Match at: $integer")

    straightSearch(text.toString(), image.toString())

    matches = MixBoyerMoore.match(image, text)
    for (integer in matches) println("\nMix-Boyer-Moore Match at: $integer")

    // print("\n Error in search:")
    // imageTable = getWrongArray(image)
    // processWrongString(text, image, imageTable)
}
