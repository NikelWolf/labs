package ru.mirea.sidnev.labs.lab1.task5;

public class Main {
    public static void main(String[] args) {
        System.out.println("factorial: " + calculateFactorial(5));
        System.out.println("factorial: " + calculateFactorial(10));
    }

    private static int calculateFactorial(int number) {
        if (number <= 0) {
            return 1;
        } else {
            int result = 1;
            for (int i = 1; i < number; i++) {
                result *= i;
            }
            return result;
        }
    }
}
