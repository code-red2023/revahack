package com.example.code_red_09;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.content.SharedPreferences;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    Button signup;
    EditText Name, PhoneNum,Password ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Check if the user has signed up
        SharedPreferences sharedPreferences = getSharedPreferences("MyPrefs", Context.MODE_PRIVATE);
        boolean hasSignedUp = sharedPreferences.getBoolean("hasSignedUp", false);

        if (hasSignedUp) {
            // The user has signed up, navigate to the homepage or another activity
            Intent i = new Intent(getApplicationContext(), Home_page.class);
            startActivity(i);
            finish(); // Finish the current activity to prevent going back to it
        } else {
            // The user has not signed up, show the signup page
            setContentView(R.layout.activity_main);
            signup = findViewById(R.id.SignUp_Button);
            Name= findViewById(R.id.Name_edtText); // Replace with the actual EditText IDs
            PhoneNum= findViewById(R.id.PhoneNum_edtText);
            Password = findViewById(R.id.Password_edtText);

            signup.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    // Check if all three fields are filled
                    String text1 = Name.getText().toString().trim();
                    String text2 = PhoneNum.getText().toString().trim();
                    String text3 = Password.getText().toString().trim();

                    if (!text1.isEmpty() && !text2.isEmpty() && !text3.isEmpty()) {
                        // All fields are filled, set the "hasSignedUp" flag to true
                        SharedPreferences.Editor editor = sharedPreferences.edit();
                        editor.putBoolean("hasSignedUp", true);
                        editor.apply();

                        // Navigate to the homepage or another activity
                        Intent i = new Intent(getApplicationContext(), Home_page.class);
                        startActivity(i);
                        finish(); // Finish the current activity
                    } else {
                        // Display a pop-up message (Toast) to the user
                        Toast.makeText(getApplicationContext(), "Please fill in all fields.", Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }
    }
}
