package com.omniasoft.bellpi;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.widget.Button;

// Import all packages
import com.omniasoft.bellpi.packets.*;


public class MainActivity extends Activity
{
	private NetworkSocket networkSocket;
		
    @Override
	public void onCreate(Bundle savedInstanceState)
    {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		// Set action bar type
		ActionBar actionBar = getActionBar();
		actionBar.setDisplayHomeAsUpEnabled(true);
		
		// Create network task
		networkSocket = new NetworkSocket();
		networkSocket.execute();
		
        final Button button = (Button) findViewById(R.id.button1);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	
            	Register packet = new Register(0xDEADBE8B, 0);
		
				Log.d(getString(R.string.app_name), "Trying to send that shit");
				networkSocket.SendPacket(packet.pack());
            }
        });
	}

    @Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main_menu, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		switch (item.getItemId())
		{
			case android.R.id.home:
				Intent intent = new Intent(this, MainActivity.class);
				intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
				startActivity(intent);
				return true;
			case R.id.menu_exit:
				this.finish();
				return true;
			case R.id.menu_setting:
				Log.d(getString(R.string.app_name), "Settings button");
				return true;
			default:
				return super.onOptionsItemSelected(item);
		}
	}
}