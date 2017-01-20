using System;
class bmi{
  public void cal(){
    string height,weight;
    height = System.Console.ReadLine();
    weight = System.Console.ReadLine();
    double HEIGHT,WEIGHT,ans;
    HEIGHT = Convert.ToDouble(height);
    WEIGHT = Convert.ToDouble(weight);
    ans = WEIGHT / Math.Pow(HEIGHT/100,2);
    System.Console.Write("Your BMI is: ");
    System.Console.Write(ans);
  }
  static void Main(){
    bmi b = new bmi();
    b.cal();
  }
}
