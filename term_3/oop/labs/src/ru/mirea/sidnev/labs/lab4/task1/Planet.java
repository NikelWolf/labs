package ru.mirea.sidnev.labs.lab4.task1;

public class Planet implements Nameable {
    private String planetName;

    public Planet(String planetName) {
        this.planetName = planetName;
    }

    public String getPlanetName() {
        return planetName;
    }

    public void setPlanetName(String planetName) {
        this.planetName = planetName;
    }

    @Override
    public String getName() {
        return planetName;
    }
}
