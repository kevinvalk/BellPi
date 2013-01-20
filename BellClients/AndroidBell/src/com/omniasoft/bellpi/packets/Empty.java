package com.omniasoft.bellpi.packets;

import struct.StructClass;

@StructClass
public class Empty extends Packet
{
	public Empty()
	{
		header.key = 0;
		header.index = 0;
		header.cmd = 0;
	}
}
