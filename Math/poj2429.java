// GCD & LCM Inverse
// This Problem is favouring the JAVA
// It runs FIVE THOUSAND MILLISECOND
// while it has been Successfully Accepted.
import java.util.Scanner;
public class Main{
    private static long gcd,lcm;
    public static void main(String[] args){
        Scanner in=new Scanner(System.in);
        while(in.hasNext()){
            gcd=in.nextLong();
            lcm=in.nextLong();
            solve();
        }
    }
    private static long GCD(long a,long b){
        return b==0?a:GCD(b,a%b);
    }
    private static void solve(){
        long prod=lcm/gcd;
        for(long i=(long)Math.floor(Math.sqrt(prod));i>0;i--){
            if(prod%i==0&&GCD(i,prod/i)==1){
                System.out.printf("%d %d\n",i*gcd,prod/i*gcd);
                return;
            }
        }
    }
}