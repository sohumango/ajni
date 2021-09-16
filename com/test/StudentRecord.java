package com.test;

public class  StudentRecord extends Object{
    public String name;
    public int rollNumber;
    public int[] scores;
    public String departement;
    public float    totalMark;
    boolean hasReservation;

    public  StudentRecord(){
        name           = new String("");
        rollNumber     = 0;
        departement    = new String("");
        totalMark      = 0;
        hasReservation = false;
    }
    public String toString() {
        return "[" + departement+ ","+ name + "," + rollNumber +"]";
    }
}
