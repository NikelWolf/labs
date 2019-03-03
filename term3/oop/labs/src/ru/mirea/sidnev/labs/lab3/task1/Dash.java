package ru.mirea.sidnev.labs.lab3.task1;

public abstract class Dash {
    protected double cost;

    public Dash() {
        cost = 0;
    }

    public Dash(double cost) {
        this.cost = cost;
    }

    public double getCost() {
        return cost;
    }

    public void setCost(double cost) {
        this.cost = cost;
    }

    public abstract void PrintInformation();
}
