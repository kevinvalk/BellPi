package com.omniasoft.bellpi.packets;

import struct.StructClass;

@StructClass
public class Fail extends Packet
{
	public Fail(int key, int index)
	{
		header.key = key;
		header.index = (byte)index;
		header.cmd = Command.PKT_FAIL;
	}
}