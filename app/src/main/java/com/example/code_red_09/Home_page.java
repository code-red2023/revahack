package com.example.code_red_09;
import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import androidx.cardview.widget.CardView;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

public class Home_page extends AppCompatActivity {

    CardView fieldTabCardView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_page);



        fieldTabCardView = findViewById(R.id.FiedTab_1);

        fieldTabCardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Home_page.this, Dashboard_page.class);
                startActivity(intent);
            }
        });
    }
}

