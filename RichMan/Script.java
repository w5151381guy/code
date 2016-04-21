import java.io.*;
import java.util.*;

public class Script
{

 public static Vector loadTerritoryData()
 {
  Vector vector =new Vector();
  Hashtable table = null;
  ClassLoader cl = new Script().getClass().getClassLoader();
  String str=null;
  String[] array;

  try
  {
    BufferedReader read = new BufferedReader(new InputStreamReader(cl.getResource("pattern/territory_data.txt").openStream()));

    while(read.ready())
    {
     str = read.readLine();

     if(str != null && str.length() > 0)
     {
	   array=str.split(",");
	   table = new Hashtable();
	   table.put("name", array[0]);
	   table.put("price", array[1]);
       // System.out.println(array[0]+" "+array[1]);

	   vector.add(table);
     }
    }

    read.close();
  }
  catch(Exception ex)
  {
   ex.printStackTrace();
  }

  return vector;
 }

}