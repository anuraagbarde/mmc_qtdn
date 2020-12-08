#include<iostream>
#include<math.h>
#include<unordered_map>

using namespace std;

unordered_map<long double, long double> factorial_dp;


long double fact(long double x)
{
    if(x==0)return 1;
    if(x==1)return 1;
    if(x==2)return 2;
    if(x==3)return 6;

    if(factorial_dp.find(x) == factorial_dp.end())
    {
        long double f = x*fact(x-1);
        factorial_dp[x] = f;
        return f;
    }
    else
    {
        return factorial_dp[x];
    }
}

class mmc 
{   
    private:
        long double a, s, c;
        long double rho;
        long double p_0 = 0 , p_q = 0;
        
    public:
        bool isvalid = true;
        mmc(long double arr, long double ser, long double c_servers)
        {
            a = arr;
            s = ser;
            c = c_servers;
            rho = a/(c*s);

            if(rho < 0 || rho >= 1)
            {
                cout<<"\nThe value of arrival rate and/or service rate is invalid for:";
                isvalid = false;
            }
            
            for(long double i =0; i <= (c - 1) ; i++ )
            {
                p_0 += ((pow(c*rho,i))/(fact(i))) ;
            }
            p_0 += ((pow(c*rho,c))/(fact(c)*(1-rho)));
            
            p_0 = 1/p_0;

            p_q = (p_0*( pow(c*rho,c)))/(fact(c)*(1-rho));

        }

        long double avg_server_util()
        {
            return rho;
        }

        long double avg_cust_q()
        {

            long double n_q = p_q*(rho/(1-rho));
            return n_q;
        }

        long double avg_wait_q()
        {
            return avg_cust_q()/a;
        }

        long double avg_wait_sys()
        {
            return ( (1/s) + avg_wait_q() );
        }

        long double avg_cust_sys()
        {
            return a*avg_wait_sys() ;
        }
};

int main()
{
    // for(long double k =1;k<=6;k++)
    {
        double long arrival = 2;
        double long service = 3;
        double long servers = 2;
        mmc obj = mmc(arrival, service, servers);

        cout<<"\nArrival rate = "<<arrival<<" | Service rate = "<<service<<" | servers = "<<servers<<"\n";

        // if(obj.isvalid == false) continue;
        cout<<"Average server utilization : "<<obj.avg_server_util()*100<<" %"<<endl;

        cout<<"Average customer in queue  : "<<obj.avg_cust_q()<<endl;

        cout<<"Average wait in queue      : "<<obj.avg_wait_q()<<endl;
        
        cout<<"Average customer in system : "<<obj.avg_cust_sys()<<endl;

        cout<<"Average wait in system     : "<<obj.avg_wait_sys()<<endl<<endl;
    
    }
    return 0;
    }
