package com.omniasoft.bellpi;

import java.nio.ByteOrder;

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

import struct.JavaStruct;
// Add structs support
import struct.StructClass;
import struct.StructException;
import struct.StructField;

public class MainActivity extends Activity
{
	private NetworkSocket networkSocket;
	
	@StructClass
	public class EmptyPacket 
	{
	    @StructField(order = 0)
	    public int key;
	    @StructField(order = 1)
	    public byte index;
	    @StructField(order = 2)
	    public int cmd;
	    @StructField(order = 3)
	    public short length;
	    // Data...
	}
	
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
            	
            	EmptyPacket packet = new EmptyPacket();
            	packet.key = 0xDEADBE8B;
            	packet.index = 0;
            	packet.cmd = 2;
            	packet.length = 0;				
				
				Log.d(getString(R.string.app_name), "Trying to send that shit");

				try
				{
					networkSocket.SendPacket(JavaStruct.pack(packet, ByteOrder.LITTLE_ENDIAN));
				}
				catch (StructException e)
				{
					Log.d(getString(R.string.app_name), "ERRORS!");
				}

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