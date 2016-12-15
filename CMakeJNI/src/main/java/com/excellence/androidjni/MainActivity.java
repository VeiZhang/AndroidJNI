package com.excellence.androidjni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'android-jni' library on application startup.
    static {
        System.loadLibrary("android-jni");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        //JNI ERROR (app bug): local reference table overflow (max=512)
        //向JNI传递大量的数据，或new出大量对象时，如果不及时释放，则会造成上述错误，比如输入1000
        Info[] infos = infoFromJNI(150);
        for (Info info : infos)
        {
            System.out.println(info.toString());
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native Info[] infoFromJNI(int num);
}
