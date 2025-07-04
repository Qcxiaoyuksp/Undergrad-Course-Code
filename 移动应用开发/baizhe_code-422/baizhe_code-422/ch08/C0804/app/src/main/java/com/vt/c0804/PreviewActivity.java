package com.vt.c0804;

import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.widget.MediaController;
import android.widget.VideoView;
import androidx.appcompat.app.AppCompatActivity;

public class PreviewActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_preview);
        this.setTitle("视频预览");

        Uri videoUri = getIntent().getData();
        final VideoView videoView = findViewById(R.id.video_view);
        videoView.setVideoURI(videoUri);
        videoView.setMediaController(new MediaController(this));
        videoView.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
            @Override
            public void onPrepared(MediaPlayer mp) {
                videoView.start();
            }
        });
    }
}
