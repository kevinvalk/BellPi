package com.omniasoft.bellpi.packets;

import java.nio.ByteOrder;

import struct.JavaStruct;
import struct.StructClass;
import struct.StructException;
import struct.StructField;

@StructClass
public abstract class Packet
{
	@StructField(order = 0)
	Header header;
	
	static final ByteOrder order = ByteOrder.LITTLE_ENDIAN;
	
	@StructClass
	public class Header 
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
	    
	    public Header()
	    {
	    	key = cmd = 0;
	    	index = 0;
	    	length = 0;
	    }
	}
	
	public Packet()
	{
		header = new Header();
	}
	
	public byte[] pack()
	{
		try
		{
			return JavaStruct.pack(this, order);
		}
		catch (StructException e)
		{
			return null;
		}
	}
	
	static public Packet unpack(byte[] bytes)
	{
		try
		{
			Packet packet;
			Empty p = new Empty();
			JavaStruct.unpack(p, bytes, order);
			switch(p.header.cmd)
			{
				case Command.PKT_FAIL:
					packet = new Fail(0, 0);
					break;
				default:
					packet = new Empty();
					break;
			}
			JavaStruct.unpack(packet, bytes, order);
			return packet;
		}
		catch (StructException e)
		{
			return null;
		}
	}
}
