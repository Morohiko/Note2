package com.example.note2;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Load the native library on application startup.
    static {
        System.loadLibrary("note2_lib");
    }

    // Declare the native method.
    public native String stringFromJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Call the native method and set its result to a TextView.
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }
}
