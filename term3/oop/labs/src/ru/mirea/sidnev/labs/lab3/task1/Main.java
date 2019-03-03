package ru.mirea.sidnev.labs.lab3.task1;

public class Main {
    public static void main(String[] args) {
        Dash dash;

        dash = new Dish();
        dash.PrintInformation();

        dash = new Dish(16, 3);
        dash.PrintInformation();

        dash = new Pan();
        dash.PrintInformation();

        dash = new Pan(18, 8);
        dash.PrintInformation();
    }
}
