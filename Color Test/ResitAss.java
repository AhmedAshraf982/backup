package com.company;

import javax.swing.*;
import java.awt.*;
import static java.lang.Thread.sleep;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Random;


class Circle {
    public int x;
    public int y;
    public int d;
    public int r, g, b;
    boolean enable;
    int pos;
    boolean right;

    public Circle(int x) {
        Random rand = new Random();
        this.enable = true;
        this.right = false;
        this.pos = x;
        this.x = 100*x + 65;
        this.y = rand.nextInt(30) - 100;
        this.d = 60;
        this.r = rand.nextInt(255);
        this.g = rand.nextInt(255);
        this.b = rand.nextInt(255);
    }

    public void draw(Graphics g) {
        g.setColor(Color.getHSBColor(this.r, this.g, this.b));
        g.fillOval(x + 1, y + 1, d - 1, d - 1);
        if(this.right)
            g.setColor(Color.RED);
        else
            g.setColor(Color.black);
        g.drawOval(x, y, d, d);
    }

    public void update() {
        if(this.enable)
            y++;
    }
    public void mark(){
        this.right = true;
    }
}

public class ResitAss extends JFrame implements MouseListener {
    int num;
    Circle[] circles;
    Circle match;
    int score;
    int wave;
    boolean gameover = false;
    boolean title = true;
    int rightCircle;
    ResitAss(){
        this.score = -1;
        this.wave = 0;
        addMouseListener(this);
        setSize(700, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());
        setVisible(true);
        setResizable(false);
        setTitle("Color Test!");
        num = 6;
        circles = new Circle[num];
        nextWave();
    }
    public void titlePage(Graphics g){
        Graphics2D g2d = (Graphics2D)g;
        Font font = new Font("Calibri", Font.BOLD, 40);
        g2d.setFont(font);
        g2d.setColor(Color.BLUE);
        g2d.drawString("-COLOR TEST GAME-", 170,200);
        font = new Font("Calibri", Font.BOLD, 20);
        g2d.setFont(font);
        g2d.setColor(Color.BLACK);
        g2d.drawString("Note: Click the shown circle to keep playing!", 150, 300);
        try {
            sleep(4000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.title = false;
    }
    public void makeMatch(){
        match = new Circle(0);
        Random rand = new Random();
        int pos = rand.nextInt(num);
        this.rightCircle = pos;
        match.r = circles[pos].r;
        match.g = circles[pos].g;
        match.b = circles[pos].b;
        match.x = 200;
        match.y = 570;
    }
    public static void main(String[] args){
        new ResitAss();   //running the game
    }

    public boolean checkAllDown(){
        for(int x = 0; x < num; x++){
            if(circles[x].y > 440){
                return true;
            }
        }
        return false;
    }
    public void paint(Graphics g)
    {
        g.clearRect(0, 0, (int)700, (int)700);
        if(title){
            titlePage(g);
            g.clearRect(0, 0, (int)700, (int)700);
        }
        if(checkAllDown()){
            this.gameover = true;
        }
        match.draw(g);
        for(int x = 0; x < num; x++){
            circles[x].draw(g);
            circles[x].update();
        }
        Graphics2D g2d = (Graphics2D)g;
        g2d.drawLine(0, 500, 700, 500);
        g2d.drawLine(350, 500, 350, 700);
        Font font = new Font("Calibri", Font.PLAIN, 20);
        g2d.setFont(font);
        g2d.drawString("Click this circle: ", 40,600);
        showStats(g);
        try {
            sleep(10 - this.wave);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        if(this.gameover){
            try {
                sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            gameOver(g);
        }
        if(!this.gameover){
            repaint();
        }
    }
    public void gameOver(Graphics g){
        this.gameover = true;
        System.out.println("Game Over!");
        try {
            sleep(2);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        g.clearRect(0, 0, (int)700, (int)700);
        Graphics2D g2d = (Graphics2D)g;
        Font font = new Font("Calibri", Font.BOLD, 50);
        g2d.setFont(font);
        g2d.setColor(Color.RED);
        g2d.drawString("Game Over!", 60,300);
        font = new Font("Calibri", Font.BOLD, 30);
        g2d.setFont(font);
        String Score = Integer.toString(this.score);
        g2d.setColor(Color.BLACK);
        g2d.drawString("Final Score: " + Score, 60, 400);
    }
    public void nextWave(){
        this.score++;
        if(this.score % 5 == 0){
            this.wave++;
        }
        for(int x = 0; x < num; x++){
            circles[x] = new Circle(x);
        }
        makeMatch();
    }
    public void showStats(Graphics g){Graphics2D g2d = (Graphics2D)g;
        Font font = new Font("Calibri", Font.PLAIN, 20);
        g2d.setFont(font);
        String Score = Integer.toString(this.score);
        g2d.drawString("Your Score: " + Score, 370,590);
        String level = Integer.toString(this.wave);
        g2d.drawString("Level: " + level, 370,620);
    }

    public void markRightCircle(){
        circles[rightCircle].mark();
    }
    public void mouseClicked(MouseEvent e)
    {
        int mouseX = e.getX();
        int mouseY = e.getY();
        for(int x = 0; x < num; x++){
            double dist = Math.sqrt((mouseX-this.circles[x].x)*(mouseX-this.circles[x].x) + (mouseY-this.circles[x].y)*(mouseY-this.circles[x].y));
            if(dist < (double) 40){
                if(checkColor(circles[x])){
                    nextWave();
                    return;
                }else{
                    markRightCircle();
                    this.gameover = true;
                }
            }
        }
    }

    public boolean checkColor(Circle circle){
        if(circle.r == match.r && circle.g == match.g && circle.b == match.b){
            return true;
        }
        return false;
    }
    @Override
    public void mousePressed(MouseEvent e) {
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }
}