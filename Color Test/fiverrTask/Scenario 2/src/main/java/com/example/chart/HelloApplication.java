package com.example.chart;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;   // class to parse the time as string and find the difference
import java.util.List;
import java.util.Scanner;

class City {   //this class has fields for a city.
    String cityName;
    String countryName;
    City left;
    City right;
    String sunrise_time;
    String sunset_time;
    int day_length;

    public City(String cityName, String countryName, String sunrise_time, String sunset_time) throws ParseException { //the parameterized constructor for the class
        this.cityName = cityName;
        this.countryName = countryName;
        this.sunrise_time = sunrise_time;
        this.sunset_time = sunset_time;
        SimpleDateFormat form = new SimpleDateFormat("HH:mm");  //finding the day_length of the day
        Date date1 = form.parse(sunrise_time);
        Date date2 = form.parse(sunset_time);
        long length = date2.getTime() - date1.getTime();
        length = get_hours(length);
        this.day_length = (int) length;
    }
    public void set_left(City city){
        left = city;
    }
    public void set_right(City city){
        right = city;
    }
    public City get_left() {
        return left;
    }
    public City get_right() {
        return right;
    }
    public String get_city(){
        return cityName;
    }
    public String get_country(){
        return countryName;
    }
    public String get_sunrise(){
        return sunrise_time;
    }
    public String get_sunset(){
        return sunset_time;
    }
    public int get_day_length(){
        return day_length;
    }
    private int get_hours(long diff){   //converting from milliseconds to hours
        return (int) (((diff/1000)/60)/60);
    }

}
class BST{   //the basic Binary Search BST
    City root;
    public BST(){
        root = null;
    }
    private City insert_(City node, City city) throws ParseException {  //wrapper function to insert a city
        if(node == null){
            node = new City(city.get_city(), city.get_country(), city.get_sunrise(), city.get_sunset());
            return node;
        }
        if(city.get_country().compareTo(node.get_country()) < 0){
            node.set_left(insert_(node.get_left(), city));
        }else{
            node.set_right(insert_(node.get_right(), city));
        }
        return node;
    }
    public boolean is_empty(){  //checking if the tree is empty
        if(root == null){
            return true;
        }
        return false;
    }

    public void insert(City city) throws ParseException {
        root = insert_(root, city);
    }

    public void showAscendingCity() {
        showAscendingCity_(root);
    }

    private void showAscendingCity_(City city) {
        if(city == null){
            return;
        }
        showAscendingCity_(city.get_left());
        System.out.println("\nCity Name: " + city.get_city() + "\nCountry Name: " + city.get_country() + "\nSunrise Time: " + city.get_sunrise() + "\nSunset Time: " + city.get_sunset() + "\nDay length: " + city.get_day_length() + "\n=============");
        showAscendingCity_(city.get_right());
    }

    public void showDescendingCity(){
        showDescendingCity_(root);
    }

    private void showDescendingCity_(City city){
        if(city == null){
            return;
        }
        showDescendingCity_(city.get_right());
        System.out.println("\nCity Name: " + city.get_city() + "\nCountry Name: " + city.get_country() + "\nSunrise Time: " + city.get_sunrise() + "\nSunset Time: " + city.get_sunset() + "\nDay length: " + city.get_day_length() + "\n=============");
        showDescendingCity_(city.get_left());
    }

    private List<City> getCities_(City city, List<City> list){  // a utility function to get all the inserted cities from the tree to a list.
        if(city == null){
            return list;
        }
        list = getCities_(city.get_left(), list);
        list.add(city);
        list = getCities_(city.get_right(), list);
        return list;
    }

    private int[] bubbleSortAscending(List<City> list){
        int index[] = new int[list.size()];
        for(int x = 0; x < list.size(); x++){
            index[x] = x;
        }
        for(int x = 0; x < list.size() - 1; x++){
            for(int y = 0; y < list.size() - x - 1; y++){
                if(list.get(index[y]).get_day_length() > list.get(index[y+1]).get_day_length()){
                    int hold = index[y];
                    index[y] = index[y+1];
                    index[y+1] = hold;
                }
            }
        }
        return index;
    }
    private int[] bubbleSortDescending(List<City> list){
        int index[] = new int[list.size()];
        for(int x = 0; x < list.size(); x++){
            index[x] = x;
        }
        for(int x = 0; x < list.size() - 1; x++){
            for(int y = 0; y < list.size() - x - 1; y++){
                if(list.get(index[y]).get_day_length() < list.get(index[y+1]).get_day_length()){
                    int hold = index[y];
                    index[y] = index[y+1];
                    index[y+1] = hold;
                }
            }
        }
        return index;
    }


    public void showAscendingDayLength(){
        List<City> list = new ArrayList<>();
        list = getCities_(root, list);
        int index[] = bubbleSortAscending(list);
        for(int x = 0; x < index.length; x++){
            System.out.println("\nCity Name: " + list.get(index[x]).get_city() + "\nCountry Name: " + list.get(index[x]).get_country() + "\nSunrise Time: " + list.get(index[x]).get_sunrise() + "\nSunset Time: " + list.get(index[x]).get_sunset() + "\nDay length: " + list.get(index[x]).get_day_length() + "\n=============");
        }
    }

    public void showDescendingDayLength(){
        List<City> list = new ArrayList<>();
        list = getCities_(root, list);
        int index[] = bubbleSortDescending(list);
        for(int x = 0; x < index.length; x++){
            System.out.println("\nCity Name: " + list.get(index[x]).get_city() + "\nCountry Name: " + list.get(index[x]).get_country() + "\nSunrise Time: " + list.get(index[x]).get_sunrise() + "\nSunset Time: " + list.get(index[x]).get_sunset() + "\nDay length: " + list.get(index[x]).get_day_length() + "\n=============");
        }
    }
    public void showChart(){  //function to set the data for the chart
        List<City> list = new ArrayList<>();
        list = getCities_(root, list);
        String[] cities = new String[list.size()];
        int[] day_lengths = new int[list.size()];
        for(int x = 0; x < list.size(); x++){
            cities[x] = list.get(x).get_city();
            day_lengths[x] = list.get(x).get_day_length();
        }
        HelloController.setData(cities, day_lengths);
    }
}
public class HelloApplication extends Application {  //pre defined class for javafx
    @Override
    public void start(Stage stage) throws IOException, ParseException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml") );
        Scene scene = new Scene(fxmlLoader.load(), 400, 400);
        stage.setTitle("Chart Comparison");
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) throws ParseException {
        BST tree = new BST();
        while(true) {
            System.out.println("Enter Your Choice:\n1. Enter '1' to read records from the file.\n2. Enter '2' to show the records in ascending order of City.\n3. Enter '3' to show the records in descending order of City.\n4. Enter '4' to show the records in ascending order of day length.\n5. Enter '5' to show the records in descending order of day length.\n6. Enter '6' to display bar chart and close the program.\n7. Enter any other key to exit.");
            Scanner scan = new Scanner(System.in);
            int option = scan.nextInt();
            switch(option){
                case 1:
                {
                    try {
                        File file = new File("C:\\Users\\Hp\\IdeaProjects\\chart\\" + "input.txt"); //absolute path to avoid ambiguity
                        Scanner read = new Scanner(file);
                        City city;
                        while (read.hasNextLine()) {
                            String line = read.nextLine();
                            String[] fields = line.split(",", 4);
                            city = new City(fields[0], fields[1], fields[2], fields[3]);
                            tree.insert(city);
                        }
                        read.close();
                        System.out.println("Records have been read successfully!");
                    } catch (FileNotFoundException e) {
                        System.out.println("An error occurred while opening file!");
                        e.printStackTrace();
                    }
                    break;
                }
                case 2:
                {
                    if(tree.is_empty()){
                        System.out.println("Sorry! Record list is empty!");
                    }else{
                        tree.showAscendingCity();
                    }
                    break;
                }
                case 3:
                {
                    if(tree.is_empty()){
                        System.out.println("Sorry! Record list is empty!");
                    }else{
                        tree.showDescendingCity();
                    }
                    break;
                }
                case 4:
                {
                    if(tree.is_empty()){
                        System.out.println("Sorry! Record list is empty!");
                    }else{
                        tree.showAscendingDayLength();
                    }
                    break;
                }
                case 5:
                {
                    if(tree.is_empty()){
                        System.out.println("Sorry! Record list is empty!");
                    }else{
                        tree.showDescendingDayLength();
                    }
                    break;
                }
                case 6:
                {
                    if(tree.is_empty()){
                        System.out.println("Sorry! Record list is empty!");
                    }else{
                        tree.showChart();
                        launch();
                        System.exit(0);
                    }
                    break;
                }
                default:
                    System.exit(0);
            }
        }

    }
}