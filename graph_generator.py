from random import *
import argparse

    
def main():
    parser = argparse.ArgumentParser(description='Calculate the sum of two numbers')
    parser.add_argument('number1', type=int, help='First number')
    parser.add_argument('number2', type=int, help='Second number')
    parser.add_argument('input', type=str, help='Second number')

    
    args = parser.parse_args()
    
    n=int(args.number1)
    m=int(args.number2)
    fh = open(args.input, "w")
    
    fh.write(str(n)+" " +str(m)+"\n")
        
    def fn_connected(n,m):
        for i in range(1,n):
            v=randint(0,i-1)
            v=int(v)
            fh.write(str(i)+" " +str(v)+"\n")
            
        
        for i in range(m-n+1):
            a=0
            b=0
            while(a==b):
                a=randint(0,n-1)
                b=randint(0,n-1)
            fh.write(str(a)+" " +str(b)+"\n")
        
        
    def fn_normal(n,m):
        if(m>n*(n-1)/2):
            return -1
        edges=[]
        for i in range(m):
            a=0
            b=0
            while(a==b):
                a=randint(0,n-1)
                b=randint(0,n-1)
            fh.write(str(a)+" " +str(b)+"\n")
        
    fn_connected(n,m)
        
    fh.close()
    
if __name__ == "__main__":
    main()