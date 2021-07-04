package com.example.iot;

public class DHT {
    public Float hum;
    public Float tem;
    public String time;

    public DHT(Float hum, Float tem, String time) {
        this.hum = hum;
        this.tem = tem;
        this.time = time;
    }
    public DHT() {
    }
}
