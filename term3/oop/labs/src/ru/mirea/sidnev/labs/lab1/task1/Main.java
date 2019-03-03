package ru.mirea.sidnev.labs.lab1.task1;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("elements count: ");
        int i, sum;
        int[] a = new int[Math.abs(scanner.nextInt())];
        for (i = 0; i < a.length; i++) {
            a[i] = scanner.nextInt();
        }

        for (i = 0, sum = 0; i < a.length; i++) {

            sum += a[i];
        }
        System.out.println("for: " + sum);

        i = sum = 0;
        while (i < a.length) {
            sum += a[i++];
        }
        System.out.println("while: " + sum);

        i = sum = 0;
        do {
            sum += a[i++];
        } while (i < a.length);
        System.out.println("do while: " + sum);
    }
}
