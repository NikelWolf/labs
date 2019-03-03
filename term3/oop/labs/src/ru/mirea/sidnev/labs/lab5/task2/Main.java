package ru.mirea.sidnev.labs.lab5.task2;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("usage: imageviewer pathtofile.img");
            System.exit(1);
        }

        try {
            BufferedImage image = ImageIO.read(new File(args[0]));
            ImageIcon icon = new ImageIcon(image);
            JFrame frame = new JFrame("Image Viewer");
            frame.setLayout(new FlowLayout());
            frame.setSize(image.getWidth(), image.getHeight());
            JLabel label = new JLabel();
            label.setIcon(icon);
            frame.add(label);
            frame.setVisible(true);
            frame.setResizable(false);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        } catch (IOException e) {
            System.err.println(e.getMessage());
            System.exit(2);
        }
    }
}
