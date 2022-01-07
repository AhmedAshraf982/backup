module com.example.chart {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;


    opens com.example.chart to javafx.fxml;
    exports com.example.chart;
}