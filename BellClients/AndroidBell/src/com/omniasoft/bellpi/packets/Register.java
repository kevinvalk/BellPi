package com.omniasoft.bellpi.packets;

import struct.StructClass;

@StructClass
public class Register extends Packet
{	
	public Register(int key, int index)
	{
		header.key = key;
		header.index = (byte)index;
		header.cmd = Command.PKT_REGISTER;
	}
}