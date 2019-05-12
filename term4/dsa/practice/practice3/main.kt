package dsa.practice.third

import kotlin.system.measureNanoTime

fun main(args: Array<String>) {

    var originArray = Array<Int>(14) { _ -> 0 }

    for (i in 0..originArray.size - 1) {
        var item = (Math.random() * 10).toInt()
        if (i % 2 == 0) item--
        else item++
        originArray.set(i, item)
    }

    print("Original array: ${originArray.asList()}\n")

    shellSort(originArray)

    var time = measureNanoTime {
        selectionSort(originArray)
    }
    print("Time NS: $time\n")

    time = measureNanoTime {
        bubbleSort(originArray)
    }
    print("Time NS: $time\n")

    time = measureNanoTime {
        insertionSort(originArray)
    }
    print("Time NS: $time\n")

    time = measureNanoTime {
        findMinElements(originArray)
    }
    print("Time NS: $time\n")
}

// Insertion sort is da best
