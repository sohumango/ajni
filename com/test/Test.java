package com.test;

public class Test {
    public native static void getStudentDetails(StudentRecord[] records);
    public static void main(String[] args) {
        System.loadLibrary("Sample");
        //int a= 10;
        StudentRecord[] records = new StudentRecord[2];
        getStudentDetails(records);
        for(StudentRecord record:records){
            System.out.println("Name:"+record.name);
            System.out.println("Roll Number:"+record.rollNumber);
            System.out.println("*** scores len:"+record.scores.length);
            for (int s : record.scores) {
                System.out.print("   "+s);
            }
            System.out.println();
            System.out.println("Departement:"+record.departement);
            System.out.println("Total Marks:"+record.totalMark);
            System.out.println("Has Reservation:"+record.hasReservation);
            System.out.println("--------------------------------");
        }
    }
}