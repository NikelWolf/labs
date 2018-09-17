package ru.mirea.sidnev.labs.lab8.task2;

import java.io.*;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("usage: fileprinter filename");
            System.exit(1);
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(args[0]))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(2);
        }
    }
}
