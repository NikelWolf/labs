package ru.mirea.sidnev.labs.lab4.task1;

public class Main {
    public static void main(String[] args) {
        Nameable nameable = new Planet("Земля");
        System.out.println(nameable.getName());
        nameable = new Car("Ford Kuga");
        System.out.println(nameable.getName());
        nameable = new Animal("Блэк");
        System.out.println(nameable.getName());
    }
}
