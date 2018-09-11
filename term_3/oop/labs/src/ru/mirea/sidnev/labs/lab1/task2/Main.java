package ru.mirea.sidnev.labs.lab1.task2;

public class Main {
    public static void main(String[] args) {
        if (args.length > 0) {
            for (String arg: args) {
                System.out.print(arg + " ");
            }
            System.out.println();
        } else {
            System.out.println("no arguments");
        }
    }
}
