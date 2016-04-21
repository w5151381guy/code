package figureEX;
public class square{

  public square(){}

  public void squareImage()
  {
    for(int i=0;i<6;i++){
      for(int j=0;j<6;j++){
        System.out.print("*");
      }
      System.out.printf("%n");
    }
  }

  public static void main(String[] args){
    square app = new square();
    app.squareImage();
    triangle app2 = new triangle();
    app2.triangleImage();
    diamond app3 = new diamond();
    app3.diamondImage();
  }
}
