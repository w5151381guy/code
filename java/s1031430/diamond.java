package figureEX;
public class diamond{

  public diamond(){}

  public void diamondImage(){
    for(int i=0;i<5;i++){
      for(int j=0;j<4-i;j++){
        System.out.print(" ");
      }
      for(int j=0;j<2*i+1;j++){
        System.out.print("*");
      }
      System.out.printf("%n");
    }
    for(int i=3;i>=0;i--){
      for(int j=0;j<4-i;j++){
        System.out.print(" ");
      }
      for(int j=0;j<2*i+1;j++){
        System.out.print("*");
      }
      System.out.printf("%n");
    }
  }
}
