using System;
class bmi{
  public void cal(){
    string height,weight;
    height = Console.ReadLine();
    weight = Console.ReadLine();
    double HEIGHT,WEIGHT,ans;
    HEIGHT = Convert.ToDouble(height);
    WEIGHT = Convert.ToDouble(weight);
    ans = WEIGHT / Math.Pow(HEIGHT/100,2);
    Console.Write("Your BMI is: ");
    Console.Write(ans);
  }
  static void Main(){
    bmi b = new bmi();
    b.cal();
  }
}
