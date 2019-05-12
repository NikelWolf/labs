package dsa.practice.second

import java.util.ArrayList
import java.util.HashMap

object BoyerMoore {
    fun match(pattern: String, text: String): List<Int> {
        val matches = ArrayList<Int>()
        val m = text.length
        val n = pattern.length

        var iter = 0

        val rightMostIndexes = preprocessForBadCharacterShift(pattern)
        var alignedAt = 0
        while (alignedAt + (n - 1) < m) {
            for (indexInPattern in n - 1 downTo 0) {
                val indexInText = alignedAt + indexInPattern
                val x = text[indexInText]
                val y = pattern[indexInPattern]
                if (indexInText >= m) break
                if (x != y) {
                    val r = rightMostIndexes[x]
                    if (r == null) {
                        alignedAt = indexInText + 1
                    } else {
                        val shift = indexInText - (alignedAt + r)
                        alignedAt += if (shift > 0) shift else 1
                    }
                    break
                } else if (indexInPattern == 0) {
                    matches.add(alignedAt)
                    alignedAt++
                }
            }
            iter++
        }

        print("\nNumber of BOYER Iterations: $iter")
        return matches
    }

    private fun preprocessForBadCharacterShift(pattern: String): Map<Char, Int> {
        val map = HashMap<Char, Int>()
        for (i in pattern.length - 1 downTo 0) {
            val c = pattern[i]
            if (!map.containsKey(c)) map[c] = i
        }
        return map
    }
}
