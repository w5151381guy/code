using System;
class bmi{
  public double bmiCal(){
    string height,weight;
    Console.Write("Please input your height(cm): ");
    height = Console.ReadLine();
    Console.Write("Please input your weight(kg): ");
    weight = Console.ReadLine();
    double Height,Weight,ans;
    Height = Convert.ToDouble(height);
    Weight = Convert.ToDouble(weight);
    ans = Math.Round(Weight / Math.Pow(Height/100,2),2);
    return ans;
  }
  public void print(double bmiValue,int evaluateValue){
    Console.Write("Your BMI is: ");
    Console.WriteLine(bmiValue);
    switch(evaluateValue){
	case 1:Console.WriteLine("You should eat more!!!");break;
	case 2:Console.WriteLine("Nice! Keep maintaining!");break;
	case 3:Console.WriteLine("You should eat less!!!");break;
    }
  }
  public int evaluate(double bmiValue){
    /*1 -> thin ; 2 -> normal ; 3 -> heavy*/
    if(bmiValue < 18.5) 
	return 1;
    else{
	if(bmiValue < 24) 
	    return 2;
	else 
	    return 3;
    }
  }
  static void Main(){
    bmi b = new bmi();
    double bmiValue;
    bmiValue = b.bmiCal();
    int evaluateValue;
    evaluateValue = b.evaluate(bmiValue);
    b.print(bmiValue,evaluateValue);
  }
}
