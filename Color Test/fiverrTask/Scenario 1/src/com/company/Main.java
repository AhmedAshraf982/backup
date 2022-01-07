package com.company;

import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.io.FileWriter;  // Import this class for filing purpose
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner; // Import the Scanner class to read text files

class Person{
    String firstName;
    String lastName;
    String notoriety;
    public Person(String firstName, String lastName, String notoriety){
        this.firstName = firstName;
        this.lastName = lastName;
        this.notoriety = notoriety;
    }
    public String get_first(){
        return firstName;
    }
    public String get_last(){
        return lastName;
    }
    public String get_notoriety(){
        return notoriety;
    }

}
class Queue{
    private List<Person> names;

    public Queue(){
        names = new ArrayList<Person>();
    }
    public void enqueue(Person name){
        names.add(name);
    }
    public Person dequeue(){
        Person name = names.get(0);
        names.remove(0);
        return name;
    }
    public int size(){
        return names.size();
    }
}
class Stack{
    private List<Character> binary;

    public Stack(){
        binary = new ArrayList<>();
    }
    public void push(char ch){
        binary.add(ch);
    }
    public char pop() {
        int index = binary.size() - 1;
        char tmp = binary.get(index);
        binary.remove(index);
        return tmp;
    }
}

class Convert{
    public int convertToDec(String binValue){
        int decValue = 0;
        Stack stack = new Stack();
        for(int x = 0; x < binValue.length(); x++){   //pushing the values to the stack to calculate the numeric value of the 8 bit binary code
            stack.push(binValue.charAt(x));
        }
        for(int x = 0; x < binValue.length(); x++){
            decValue += (Integer.parseInt(String.valueOf(stack.pop()))*Math.pow(2, x));   //adding the values to find the ascii value
        }
        return decValue;
    }
    public char convertToChar(int decValue){
        char letter = ' ';
        letter = (char)decValue;  //explicit type casting to find the character corresponding the ascii value
        return letter;
    }
}
class Sort{
    public int[] insertion_sort(List<Person> names){
        int i, j, n = names.size();
        int index[] = new int[n];
        for(i = 0; i < n; i++){
            index[i] = i;
        }
        for (i = 1; i < n; i++) {   //insertion sort algorithm
            int key = index[i];
            j = i - 1;
            while (j >= 0 && (names.get(index[j]).get_last().compareTo(names.get(key).get_last())) > 1) {
                index[j + 1] = index[j];
                j--;
            }
            index[j + 1] = key;
        }
        return index;
    }
}

public class Main {

    public static void main(String[] args) {
        String inputFilename = "input_.csv";  //change the input file name here
        String outputFilename = "output_.csv";
        Queue queue = new Queue();
        List<Person> persons_ = new ArrayList<>();
        while(true) {
            System.out.println("Enter your choice number:\n1. Enter '1' to read data from the file.\n2. Enter '2' to process the data.\n3. Enter '3' to save the data to the file.\n4. Enter '4' to show output.\n5. Enter any other key to exit.");
            Scanner scan = new Scanner(System.in);
            int choice = scan.nextInt();
            switch (choice) {
                case 1:   //to read the input file
                {
                    try {
                        File file = new File("C:\\Users\\Hp\\IdeaProjects\\Part 1\\src\\com\\company\\" + inputFilename); //absolute path to avoid ambiguity
                        Scanner read = new Scanner(file);
                        Person person;
                        while (read.hasNextLine()) {
                            String line = read.nextLine();
                            String[] fields = line.split(",", 3);
                            person = new Person(fields[0], fields[1], fields[2]);
                            queue.enqueue(person);
                        }
                        read.close();
                        System.out.println("Records have been read successfully!");
                    } catch (FileNotFoundException e) {
                        System.out.println("An error occurred while opening file!");
                        e.printStackTrace();
                    }
                    break;
                }
                case 2:  //to convert the 8 bit patterns to characters
                {
                    Person person;
                    Convert convert = new Convert();
                    int size = queue.size();
                    for(int x = 0; x < size; x++){
                        String first = "", last = "", notoriety = "";
                        person = queue.dequeue();
                        String[] firstName = person.get_first().split(";", 100);
                        String[] lastName = person.get_last().split(";", 100);
                        for(int y = 0; y < firstName.length; y++){
                            int dec = convert.convertToDec(firstName[y]);
                            char hold = convert.convertToChar(dec);
                            first += hold;
                        }
                        for(int y = 0; y < lastName.length; y++){
                            int dec = convert.convertToDec(lastName[y]);
                            char hold = convert.convertToChar(dec);
                            last += hold;
                        }
                        notoriety = person.get_notoriety();
                        Person mod_name = new Person(first, last, notoriety);
                        persons_.add(mod_name);
                    }
                    System.out.println("Records have been processed successfully!");
                    break;
                }
                case 3: {  //to write to output file
                    try {
                        FileWriter myWriter = new FileWriter(outputFilename);
                        for(int x = 0; x < persons_.size(); x++){
                            myWriter.write(persons_.get(x).get_first() + ", " + persons_.get(x).get_last() + ", " +   persons_.get(x).get_notoriety() + "\n");
                        }
                        myWriter.close();
                        System.out.println("Successfully wrote to the file.");
                    } catch (IOException e) {
                        System.out.println("An error occurred.");
                        e.printStackTrace();
                    }
                    break;
                }
                case 4:  //to display the formatted output on screens
                {
                    Sort sort = new Sort();
                    int index[] = sort.insertion_sort(persons_);
                    String firstPerson = "Firstname", lastPerson = "Lastname", notoriety = "Notoriety";
                    int firstMax = firstPerson.length();
                    int lastMax = lastPerson.length();
                    int notMax = notoriety.length();
                    for(int x = 0; x < persons_.size(); x++){
                        if(persons_.get(x).get_first().length() > firstMax){
                           firstMax = persons_.get(x).get_first().length();
                        }
                        if(persons_.get(x).get_last().length() > lastMax){
                            lastMax = persons_.get(x).get_last().length();
                        }
                        if(persons_.get(x).get_notoriety().length() > notMax){
                            notMax = persons_.get(x).get_notoriety().length();
                        }
                    }

                    //printing the formatted output
                    int numDash = firstMax + lastMax + notMax + 3 + 3 + 3 + 4;
                    for(int x = 0; x < numDash; x++){
                        System.out.print("-");
                    }
                    System.out.print("\n");
                    System.out.print("| Firstname");
                    for(int x = 0; x < firstMax - 9 + 2; x++){
                        System.out.print(" ");
                    }
                    System.out.print("| Lastname");
                    for(int x = 0; x < lastMax - 8 + 2; x++){
                        System.out.print(" ");
                    }
                    System.out.print("| Notoriety");
                    for(int x = 0; x < notMax - 9 + 2; x++){
                        System.out.print(" ");
                    }
                    System.out.print("|\n");
                    for(int x = 0; x < numDash; x++){
                        System.out.print("-");
                    }
                    System.out.print("\n");
                    for(int x = 0; x < index.length; x++){
                        System.out.print("| " + persons_.get(index[x]).get_first());
                        for(int y = 0; y < firstMax - persons_.get(index[x]).get_first().length() + 2; y++){
                            System.out.print(" ");
                        }
                        System.out.print("| " + persons_.get(index[x]).get_last());
                        for(int y = 0; y < lastMax - persons_.get(index[x]).get_last().length() + 2; y++){
                            System.out.print(" ");
                        }
                        System.out.print("| " + persons_.get(index[x]).get_notoriety());
                        for(int y = 0; y < notMax - persons_.get(index[x]).get_notoriety().length() + 2; y++){
                            System.out.print(" ");
                        }
                        System.out.print("|\n");
                    }
                    for(int x = 0; x < numDash; x++){
                        System.out.print("-");
                    }
                    System.out.println("\n");
                    break;
                }
                default:
                    System.exit(0);
            }
        }
    }
}
