package ru.mirea.sidnev.labs.lab4.task1;

public class Car implements Nameable {
    private String carType;

    public Car(String carType) {
        this.carType= carType;
    }

    public String getCarType() {
        return carType;
    }

    public void setCarType(String carType) {
        this.carType = carType;
    }

    @Override
    public String getName() {
        return carType;
    }
}
