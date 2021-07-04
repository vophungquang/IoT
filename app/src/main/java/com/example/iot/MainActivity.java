package com.example.iot;

//import androidx.annotation.NonNull;
//import androidx.annotation.Nullable;
//import androidx.appcompat.app.AppCompatActivity;
//
//import android.os.Bundle;
//import android.widget.ArrayAdapter;
//import android.widget.ListView;
//
//import com.google.firebase.database.ChildEventListener;
//import com.google.firebase.database.DataSnapshot;
//import com.google.firebase.database.DatabaseError;
//import com.google.firebase.database.DatabaseReference;
//import com.google.firebase.database.FirebaseDatabase;
//
//import java.util.ArrayList;
//
//public class MainActivity extends AppCompatActivity {
//    DatabaseReference mData;
//    ListView lv;
//    ArrayList<Float> mang;
//    ArrayAdapter adapter=null;
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//        lv=(ListView) findViewById(R.id.lvdht);
//        mang = new ArrayList<Float>();
//        adapter= new ArrayAdapter(this,android.R.layout.simple_expandable_list_item_1,mang);
//        lv.setAdapter(adapter);
//
//        mData= FirebaseDatabase.getInstance().getReference();
//        mData.child("data").addChildEventListener(new ChildEventListener() {
//            @Override
//            public void onChildAdded(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
//                DHT dht= snapshot.getValue(DHT.class);
//                mang.add(dht.hum);
//                mang.add(dht.tem);
//                adapter.notifyDataSetChanged();
//            }
//
//            @Override
//            public void onChildChanged(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
//
//            }
//
//            @Override
//            public void onChildRemoved(@NonNull DataSnapshot snapshot) {
//
//            }
//
//            @Override
//            public void onChildMoved(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {
//
//            }
//
//            @Override
//            public void onCancelled(@NonNull DatabaseError error) {
//
//            }
//        });
//    }
//}

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends Activity {
    DatabaseReference mydb;
    TextView temp,hum;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        temp=(TextView)findViewById(R.id.temp);
        hum=(TextView)findViewById(R.id.hum);
        mydb= FirebaseDatabase.getInstance().getReference().child("Sensor");
        try {

            mydb.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    String tempdata = dataSnapshot.child("temp").getValue().toString();
                    String humdata = dataSnapshot.child("hum").getValue().toString();
                    temp.setText(tempdata);
                    hum.setText(humdata);

                }

                @Override
                public void onCancelled(DatabaseError error) {
                }
            });
        } catch(Exception e)
        {


        }


    }
}