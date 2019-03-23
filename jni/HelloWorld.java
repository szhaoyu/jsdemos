import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Iterator;
import java.util.Vector;
import java.util.Scanner;

public class HelloWorld {  
    public native void displayHelloWorld();// java native方法申明  
    public native void unmapMemory(long address, long len);
  
    static {  
        //System.out.println(System.getProperty("java.library.path"));
        System.setProperty("java.library.path", ".");
        System.loadLibrary("hello");// 装入动态链接库，"HelloWorldImpl"是要装入的动态链接库名称。  
        System.loadLibrary("util");// 装入动态链接库，"HelloWorldImpl"是要装入的动态链接库名称。  
    }  
  
    public static void main(String[] args) throws Exception {  
Scanner s = new Scanner(System.in);
        // TODO Auto-generated method stub  
        HelloWorld helloWorld = new HelloWorld();  
        System.out.println("before out-heap malloc ...");
	System.in.read();
        helloWorld.displayHelloWorld();  
	
	/*
        System.out.println("before java new ...");
	System.in.read();
	byte[] data = new byte[1024*1024*128];
	
        System.out.println("after java new ...");
	System.in.read();
        */
        freeDll("hello.so");
        System.out.println("after unload...");
	System.in.read();

        System.out.println("input memory address & length: ");
	Long address = s.nextLong();
	Long len = s.nextLong();
        System.out.println("ready to unmap...");
	System.in.read();
	helloWorld.unmapMemory(address, len);	
        System.out.println("after unmap...");
	System.in.read();
	/*
        System.loadLibrary("hello");
        System.out.println("reload...");
        helloWorld.displayHelloWorld();  
        freeDll("hello.so");
        System.out.println("after unload...");
	System.in.read();
        System.loadLibrary("hello");
        System.out.println("reload...");
        helloWorld.displayHelloWorld();  
	System.in.read();
	*/
    }  

private static synchronized void freeDll(String dllName) {  
  try {  
   ClassLoader classLoader = HelloWorld.class.getClassLoader();  
   Field field = ClassLoader.class.getDeclaredField("nativeLibraries");  
   field.setAccessible(true);  
   Vector<Object> libs = (Vector<Object>) field.get(classLoader);  
   Iterator<Object> it = libs.iterator();  
   Object o;  
   while (it.hasNext()) {  
    o = it.next();  
    Field[] fs = o.getClass().getDeclaredFields();  
    boolean hasInit = false;  
    for (int k = 0; k < fs.length; k++) {  
     if (fs[k].getName().equals("name")) {  
      fs[k].setAccessible(true);  
      String dllPath = fs[k].get(o).toString();  
      if (dllPath.endsWith(dllName)) {  
       hasInit = true;  
      }  
     }  
    }  
    if (hasInit) {  
     Method finalize = o.getClass().getDeclaredMethod(  
       "finalize", new Class[0]);  
     finalize.setAccessible(true);  
     finalize.invoke(o, new Object[0]);  
     it.remove();          
     libs.remove(o);  
    }  
   }  
  
  } catch (Exception e) {  
   e.printStackTrace();  
  }  
 }  
}

