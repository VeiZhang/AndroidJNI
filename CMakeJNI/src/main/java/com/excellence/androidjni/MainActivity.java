package com.excellence.androidjni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity
{
	private LinearLayout mLayout = null;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mLayout = (LinearLayout) findViewById(R.id.main_layout);

		// Example of a call to a native method
		getStringFormJNI();

		getArrayFromJNI();

		getListFromJNI();
	}

	private TextView addTextView(String str)
	{
		TextView textView = new TextView(this);
		textView.setTextSize(25);
		textView.setText(str);
		mLayout.addView(textView);
		return textView;
	}

	private TextView addTextView(String str, boolean bold)
	{
		TextView textView = addTextView(str);
		// textView.setTypeface(Typeface.defaultFromStyle(Typeface.BOLD));
		textView.getPaint().setFakeBoldText(bold);
		return textView;
	}

	private void getStringFormJNI()
	{
		addTextView("StringJNI", true);
		addTextView(stringFromJNI());
	}

	private void getArrayFromJNI()
	{
		// JNI ERROR (app bug): local reference table overflow (max=512)
		// 向JNI传递大量的数据，或new出大量对象时，如果不及时释放，则会造成上述错误，比如输入1000
		addTextView("ArrayJNI", true);
		Info[] infos = infoArrayFromJNI(2);
		for (Info info : infos)
		{
			addTextView(info.toString());
		}
	}

	private void getListFromJNI()
	{
		List<Info> infoList = infoListFromJNI(3);
		addTextView("ListJNI", true);
		for (Info info : infoList)
		{
			addTextView(info.toString());
		}
	}

	/**
	 * A native method that is implemented by the 'native-lib' native library,
	 * which is packaged with this application.
	 */
	public native String stringFromJNI();

	public native Info[] infoArrayFromJNI(int num);

	public native List<Info> infoListFromJNI(int num);

	// Used to load the 'android-jni' library on application startup.
	static
	{
		System.loadLibrary("android-jni");
	}

}
