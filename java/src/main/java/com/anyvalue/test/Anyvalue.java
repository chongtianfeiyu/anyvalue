/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.anyvalue.test;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;

import com.anyvalue.CAnyValue;
import com.anyvalue.HeapBuffer;

/**
 *
 * @author starjiang
 */
public class Anyvalue {

	/**
	 * @param args the command line arguments
	 */
	public static void main(String[] args) {
		// TODO code application logic here
		CAnyValue oValue = new CAnyValue();
		oValue.put("ABC");
		oValue.put(-100000000);
		oValue.put(-1);
		oValue.put(true);
		oValue.put(false);
		oValue.put(1.55555555);
		oValue.put(null);
		oValue.put(new CAnyValue());
		CAnyValue oValue1 = new CAnyValue();
		oValue1.put("name", "starjiang");
		byte[] bytes = new byte[1];
		bytes[0]=15;
		String s = new String(bytes);
		oValue1.put("desc1",s);
		oValue1.put("desc", "我爱北京天安门\n");
		oValue1.put("age", 30);
		oValue1.put("age2", 0);
		oValue.put(oValue1);
		oValue.put("starjiang\n");
		oValue.put("");
		String sBuf = oValue.encodeJSON();
		System.out.println(sBuf);
		HeapBuffer sBuf2 = oValue.encode();
		CAnyValue oValue2 = new CAnyValue();
		
		oValue2.decode(sBuf2.position(0));
		String sBuf3 = oValue2.encodeJSON();
		
		System.out.println("sbuf3="+sBuf3);
		String sBuf5 =oValue1.encodeJSON();
		System.out.println(sBuf5);
		CAnyValue oValue3 = new CAnyValue();
		oValue3.decodeJSON(sBuf3);
		
		String sBuf4 = oValue3.encodeJSON();
		System.out.println(sBuf4);
		
		oValue3.clear();
		String s1 = "    {\"name\"  :\"starjiang\"  ,\"age\":-129111111,\"score\":1.5,\"info\":{\"nick\":\"\\u6211\\u662f\\u4e00\\u4e2a\\u5175\\u6765\\u81ea\\u8001\\u767e\\u59d3\",\"age\":12},\"items\":[123,\"addasdsa\"]}";
		oValue3.decodeJSON(s1);
		System.out.println(oValue3.get("age").asLong());
		
		String sBuf6 = oValue3.encodeJSON();
		System.out.println(sBuf6);
		
		System.out.println(oValue2.get(8).get("desc").asString());
		
		/*
		File file = new File("d:\\a.txt");
		
		try
		{
			InputStream	in = new FileInputStream(file);
			byte[] bytes1 = new byte[1024];
			int len = in.read(bytes1);
			ByteBuffer buffer1 = ByteBuffer.wrap(bytes1);
			oValue3.clear();
			oValue3.decode(buffer1);
			StringBuffer sBuf9 = new StringBuffer();
			oValue3.encodeJSON(sBuf9);
			System.out.println(sBuf9);
		}
		catch (IOException e) 
		{
            e.printStackTrace();
		}
		*/
	}

}
