package com.example.chart;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.XYChart;
import java.net.URL;
import java.util.ResourceBundle;

public class HelloController implements Initializable {
    @FXML
    private BarChart<?, ?> day_length;

    private static String cities[];
    private static int durations[];
    private static int size;
    public static void setData(String[] cities, int[] durations){
        HelloController.cities = cities;
        HelloController.durations = durations;
        HelloController.size = cities.length;
    }

    @Override
    public void initialize(URL url, ResourceBundle rb){
        XYChart.Series sets = new XYChart.Series<>();
        for(int x = 0; x < size; x++) {
            sets.getData().add(new XYChart.Data(cities[x], durations[x]));
        }
        day_length.getData().addAll(sets);
    }

}