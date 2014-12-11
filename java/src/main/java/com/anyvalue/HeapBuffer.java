package com.anyvalue;
import java.nio.ByteBuffer;

public class HeapBuffer {

	private byte []data = null;
	private ByteBuffer buffer = null;
	private int initSize = 0;
	private int maxSize = 0;
	private int currCapacity = 0;
	private static int DEFAULT_INIT_SIZE = 4096;
	private static int DEFAULT_MAX_SIZE = 1024*1024*100;
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HeapBuffer buffer = HeapBuffer.allocate();
		buffer.putInt(1);
		buffer.putInt(1);
		buffer.putInt(1);
		buffer.putInt(1);
		buffer.putInt(1);
		buffer.putInt(1);
		byte []data = new byte[1000000];
		buffer.put(data);
		System.out.println(buffer.currCapacity());
	}
	
	public static HeapBuffer allocate()
	{
		return new HeapBuffer(DEFAULT_INIT_SIZE, DEFAULT_MAX_SIZE);
	}
	
	public static HeapBuffer wrap(byte[] src)
	{
		return new HeapBuffer(src);
	}
	
	public static HeapBuffer wrap(byte[] src,int offset,int length)
	{
		return new HeapBuffer(src,offset,length);
	}
	
	protected HeapBuffer(byte[] src)
	{
		data = src;
		currCapacity = src.length;
		this.initSize = currCapacity;
		this.maxSize = currCapacity;
		buffer = ByteBuffer.wrap(data);
	}
	
	protected HeapBuffer(byte[] src,int offset,int length)
	{
		data = src;
		currCapacity = src.length;
		this.initSize = currCapacity;
		this.maxSize = currCapacity;
		buffer = ByteBuffer.wrap(data,offset,length);
	}
	
	protected HeapBuffer(int initSize,int maxSize)
	{
		data = new byte[initSize];
		currCapacity = initSize;
		this.initSize = initSize;
		this.maxSize = maxSize;
		buffer = ByteBuffer.wrap(data);
	}
	
	public byte get()
	{
		return buffer.get();
	}
	
	public byte get(int index)
	{
		return buffer.get(index);
	}
	
	public HeapBuffer get(byte[] dst)
	{
		buffer.get(dst);
		return this;
	}
	
	public HeapBuffer get(byte[] dst,int offset,int length)
	{
		buffer.get(dst,offset,length);
		return this;
	}
	
	public char getChar()
	{
		return buffer.getChar();
	}

	public char getChar(int index)
	{
		return buffer.getChar(index);
	}

	public double getDouble()
	{
		return buffer.getDouble();
	}
	public double getDouble(int index)
	{
		return buffer.getDouble(index);
	}
	public float getFloat()
	{
		return buffer.getFloat();
	}
	public float getFloat(int index)
	{
		return buffer.getFloat(index);
	}
	
	public int getInt()
	{
		return buffer.getInt();
	}
	public int getInt(int index)
	{
		return buffer.getInt(index);
	}
	public long getLong()
	{
		return buffer.getLong();
	}
	public long getLong(int index)
	{
		return buffer.getLong(index);
	}
	
	public short getShort()
	{
		return buffer.getShort();
	}
	public short getShort(int index)
	{
		return buffer.getShort(index);
	}
	
	private void expand(int need)
	{
		currCapacity = (currCapacity+need)*2;
		if(currCapacity > maxSize) 
		{
			currCapacity = maxSize;
		}
		byte [] preData = data;
		data = new byte[currCapacity];
		
		System.arraycopy(preData, 0, data, 0, preData.length);
		
		int position = buffer.position();
		buffer = ByteBuffer.wrap(data);
		buffer.position(position);
	}
	
	public boolean check(int offset)
	{
		if(buffer.position()+offset > currCapacity)
		{
			return false;
		}
		return true;
	}
	
	public HeapBuffer put(byte b)
	{
		if(!check(1)) 
		{
			expand(1);
		}	
		buffer.put(b);
		return this;
	}
	
	public HeapBuffer put(byte[] src)
	{
		if(!check(src.length)) 
		{
			expand(src.length);
		}
		buffer.put(src);
		return this;
	}
	
	public HeapBuffer put(int index,byte b)
	{
		buffer.put(index, b);
		return this;
	}
	
	public HeapBuffer put(byte[] src,int offset,int length)
	{
		if(!check(length)) 
		{
			expand(length);
		}
		buffer.put(src, offset, length);
		return this;
	}
	
	public HeapBuffer putChar(char value)
	{
		if(!check(2)) 
		{
			expand(2);
		}
		buffer.putChar(value);
		return this;
	}
	
	public HeapBuffer putChar(int index ,char value)
	{
		buffer.putChar(index,value);
		return this;
	}
	
	public HeapBuffer putShort(short value)
	{
		if(!check(2)) 
		{
			expand(2);
		}
		buffer.putShort(value);
		return this;
	}
	
	public HeapBuffer putShort(int index ,short value)
	{
		buffer.putShort(index,value);
		return this;
	}
	
	public HeapBuffer putInt(int value)
	{
		if(!check(4)) 
		{
			expand(4);
		}
		buffer.putInt(value);
		return this;
	}
	
	public HeapBuffer putShort(int index ,int value)
	{
		buffer.putInt(index,value);
		return this;
	}
	
	public HeapBuffer putLong(long value)
	{
		if(!check(8)) 
		{
			expand(8);
		}
		buffer.putLong(value);
		return this;
	}
	
	public HeapBuffer putLong(int index ,long value)
	{
		buffer.putLong(index,value);
		return this;
	}
	
	public HeapBuffer putFloat(float value)
	{
		if(!check(4)) 
		{
			expand(4);
		}
		buffer.putFloat(value);
		return this;
	}
	
	public HeapBuffer putFloat(int index ,float value)
	{
		buffer.putFloat(index,value);
		return this;
	}
	
	public HeapBuffer putDouble(double value)
	{
		if(!check(8)) 
		{
			expand(8);
		}
		buffer.putDouble(value);
		return this;
	}
	
	public HeapBuffer putDouble(int index ,double value)
	{
		buffer.putDouble(index,value);
		return this;
	}
	
	public int capacity()
	{
		return maxSize;
	}
	
	public int position()
	{
		return buffer.position();
	}
	
	public HeapBuffer position(int pos)
	{
		buffer.position(pos);
		return this;
	}
	
	public HeapBuffer mark()
	{
		buffer.mark();
		return this;
	}
	
	public HeapBuffer reset()
	{
		buffer.reset();
		return this;
	}
	
	public int currCapacity()
	{
		return currCapacity;
	}
	
	public byte[] array()
	{
		return buffer.array();
	}
}
