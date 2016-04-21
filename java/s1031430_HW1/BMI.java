import java.util.*;
import java.text.DecimalFormat;

public  class BMI
{
    private  int number;                      //學號
    private String mail;                        //e-mail
    private double weight;                //體重
    private double height;                 //身高
    private String name;                     //名字

    BMI(){}

    BMI(String a,int b,String c,float d,float e)
    {
        name = a;
        number = b;
        mail = c;
        weight = d;
        height = e;
    }

    /*getter*/
    public String getName()                                       {return name;}
    public int getNumber()                                         {return number;}
    public String getMail()                                           {return mail;}
    public double getWeight()                                  {return weight;}
    public double getHeight()                                   {return height;}
    /*setter*/
    public void setName(String a)                            {name = a;}
    public void setNumber(int b)                              {number = b;}
    public void setMail(String c)                                {mail = c;}
    public void setWeight(double d)                       {weight = d;}
    public void setHeight(double e)                        {height = e;}
    /*BMI計算*/
    public double calculation()                                {
        DecimalFormat nf = new DecimalFormat("0.00");
        double BMI = weight/(height/100)/(height/100);
        return Double.parseDouble(nf.format(BMI));
    }

    public static void main(String[] agvs)
    {
        Scanner input = new Scanner(System.in);
        BMI app = new BMI();                //初始

        System.out.print("Please enter your name: ");
        String inputName = input.next();
        app.setName(inputName);
        System.out.print("Please input your student ID: ");
        int inputNumber = input.nextInt();
        app.setNumber(inputNumber);
        System.out.print("Please input your e-mail: ");
        String inputMail = input.next();
        app.setMail(inputMail);
        System.out.print("Please input your weight(kg): ");
        double inputWeight = input.nextDouble();
        app.setWeight(inputWeight);
        System.out.print("Please input your height(cm): ");
        double inputHeight = input.nextDouble();
        app.setHeight(inputHeight);

        System.out.println(app.getNumber()+" BMI is: "+app.calculation());
    }
}
