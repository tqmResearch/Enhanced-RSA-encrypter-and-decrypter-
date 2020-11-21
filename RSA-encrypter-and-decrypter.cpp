#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;
typedef long long ll;

#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
string message;
typedef vector<int> BigInt;

void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());
    FORD(i,a.size()-2,0) printf("%09d", a[i]); EL;
}

BigInt Integer(string s) {
    BigInt ans;
    if (s[0] == '-') return ans;
    if (s.size() == 0) {ans.pb(0); return ans;}
    while (s.size()%9 != 0) s = '0'+s;
    for (int i=0;i<s.size();i+=9) {
        int v = 0;
        for (int j=i;j<i+9;j++) v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}

BigInt Integer(char c[]) {
    string s = "";
    FOR(i,0,strlen(c)-1) s = s + c[i];
    return Integer(s);
}

BigInt Integer(ll x) {
    string s = "";
    while (x > 0) s = char(x%10+'0') + s, x /= 10;
    return Integer(s);
}

BigInt Integer(int x) {
    return Integer((ll) x);
}

void operator >> (istream &in, BigInt &a) {
    string s;
    getline(cin, s);
    a = Integer(s);
}

void operator << (ostream &out, BigInt a) {
    Print(a);
}

bool operator < (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    FORD(i,a.size()-1,0)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return (!(a < b) && !(b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b || a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < Integer(b));
}

bool operator > (BigInt a, int b) {
    return (a > Integer(b));
}

bool operator == (BigInt a, int b) {
    return (a == Integer(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= Integer(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= Integer(b));
}

BigInt max(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}

BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,max(a.size(), b.size())-1) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.pb(carry%base);
        carry /= base;
    }
    if (carry) ans.pb(carry);
    Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + Integer(b);
}

BigInt operator ++ (BigInt &a) { // ++a
    a = a + 1;
    return a;
}

void operator += (BigInt &a, BigInt b) {
    a = a + b;
}

void operator += (BigInt &a, int b) {
    a = a + b;
}

BigInt operator - (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,a.size()-1) {
        carry += a[i] - (i < b.size() ? b[i] : 0);
        if (carry < 0) ans.pb(carry+base), carry = -1;
        else ans.pb(carry), carry = 0;
    }
    Set(ans);
    return ans;
}

BigInt operator - (BigInt a, int b) {
    return a - Integer(b);
}

void operator -- (BigInt &a) { // --a
    a = a - 1;
}

void operator -= (BigInt &a, BigInt b) {
    a = a - b;
}

void operator -= (BigInt &a, int b) {
    a = a - b;
}

BigInt operator * (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    ans.assign(a.size()+b.size(), 0);
    FOR(i,0,a.size()-1) {
        ll carry = 0ll;
        for (int j=0;j<b.size() || carry > 0;j++) {
            ll s = ans[i+j] + carry + (ll)a[i]*(j<b.size()?(ll)b[j]:0ll);
            ans[i+j] = s%base;
            carry = s/base;
        }
    }
    Set(ans);
    return ans;
}

BigInt operator * (BigInt a, int b) {
    return a * Integer(b);
}

void operator *= (BigInt &a, BigInt b) {
    a = a * b;
}

void operator *= (BigInt &a, int b) {
    a = a * b;
}



BigInt operator / (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (b == Integer(0)) return Integer("-1");
    BigInt ans, cur;
    FORD(i,a.size()-1,0) {
        cur.insert(cur.begin(), a[i]);
        int x = 0, L = 0, R = base;
        while (L <= R) {
            int mid = (L+R)>>1;
            if (b*Integer(mid) > cur) {
                x = mid;
                R = mid-1;
            }
            else
                L = mid+1;
        }
        cur = cur - Integer(x-1)*b;
        ans.insert(ans.begin(),x-1);
    }
    Set(ans);
    return ans;
}

BigInt operator / (BigInt a, int b) {
    Set(a);
    BigInt ans;
    ll cur = 0ll;
    FORD(i,a.size()-1,0) {
        cur = (cur*(ll)base + (ll)a[i]);
        ans.insert(ans.begin(),cur/b);
        cur %= b;
    }
    Set(ans);
    return ans;
}

void operator /= (BigInt &a, BigInt b) {
    a = a / b;
}

void operator /= (BigInt &a, int b) {
    a = a / b;
}

BigInt operator % (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (b == Integer(0)) return Integer("-1");
    BigInt ans;
    FORD(i,a.size()-1,0) {
        ans.insert(ans.begin(), a[i]);
        int x = 0, L = 0, R = base;
        while (L <= R) {
            int mid = (L+R)>>1;
            if (b*Integer(mid) > ans) {
                x = mid;
                R = mid-1;
            }
            else
                L = mid+1;
        }
        ans = ans - Integer(x-1)*b;
    }
    Set(ans);
    return ans;
}

int operator % (BigInt a, int b) {
    Set(a);
    if (b == 0) return -1;
    int ans = 0;
    FORD(i,a.size()-1,0)
        ans = (ans*(base%b) + a[i]%b)%b;
    return ans;
}

void operator %= (BigInt &a, BigInt b) {
    a = a % b;
}

void operator %= (BigInt &a, int b) {
    a = a % Integer(b);
}

BigInt gcd(BigInt a, BigInt b) {
    Set(a);
    Set(b);
    while (b > Integer(0)) {
        BigInt r = a%b;
        a = b;
        b = r;
    }
    Set(a);
    return a;
}

BigInt pow(BigInt a, BigInt b, BigInt N) {
    //cout<<1<<" ";
    //cout<<b;
    //cout<<endl;
    BigInt ans;
    if (b == Integer(0)) return Integer(1);
    BigInt tmp = pow(a, b/2,N);
    if (b%2 == 0)  ans = (tmp * tmp)%N;
    else ans = ((tmp * tmp)%N * a)%N;
    //cout<<ans;
    //cout<<endl;
    return ans;
}

/*BigInt pow(BigInt a, int b) {
    return pow(a,(Integer(b)));
}*/

BigInt getPrime(){
    string primes[]={
		"1772629573679152589335751",
        "9996834795542799325379081",
        "8076737514959871909661591",
        "9184713383182455436877249",
        "5248856571818397095667017",
        "3316361718074381133015827",
        "6612394226173762040335063",
        "8418082864875619721401463",
        "2875808158322221473148513",
        "61920572513383563943782839",
        "65320483338614522331739967",
        "94473552408568888084488047",
    };
    return Integer(primes[rand()%12]);
}

BigInt strToNum(string s){
    string ans = "126";
    for(int i=0;i<s.length();i++){
        int temp = int(s[i]);
        if(temp/10 == 0) ans= ans + "00" ;
        else if(temp/100 == 0) ans = ans + "0" ;
        std::string a = std::to_string(temp);
        ans = ans + a;
    }
    //cout<<ans<<" ";
    //cout<<Integer(ans);
    return Integer(ans);
}
void numToStr(BigInt n)
{
    //cout<<n;
    //cout<<endl;
    string temp = "";
    //Set(n);
    temp += to_string((n.size() == 0) ? 0 : n.back());
    FORD(i,n.size()-2,0){
        char temp2[50];
        sprintf(temp2,"%09d",n[i]);
        temp = temp + temp2;
    }
    //cout<<temp<<endl;
    for(int i=3;i<temp.length(); ){
        int asciiValue = (temp[i]-'0')*100 + (temp[i+1]-'0')*10 + (temp[i+2]-'0');
        cout<<(char)asciiValue;
        i=i+3;
    }
    return ;
}


class company
{
    private:
        BigInt p;
        BigInt q;
        BigInt phiN;
        BigInt d;
    public:
        BigInt N;
        BigInt e;
		void getPQ();
		void getN();
		void getphiN();
		void getE();
		void getD();
		BigInt ENCRYPT(string m , company n);
		void DECRYPT(BigInt m);
		void signup();
};

void company::getPQ()
{
    p=getPrime();
    q=getPrime();
}

void company::getN()
{
    N=p*q;
}

void company::getphiN()
{
    phiN=((p-1)*(q-1));
}

void company::getE()
{
    e=Integer(3);
   while(1)
    {
        if(gcd(e,phiN)==1)
			break;
        e = e+2;
    }
}

void company::getD()
{
    BigInt k=Integer(1);
    while(1)
    {
        if((((k*phiN)+1)%e)==0)
        {
            d=((k*phiN)+1)/e;
            break;
        }
        k= k+1;
    }
    //cout<<d;
    //cout<<endl;
    //cout<<k;
}

BigInt company::ENCRYPT(string message,company recipient)
{
    cout<<"Encrypting.......    ";
    BigInt mnum,c,r_e,r_N;
    mnum=strToNum(message);
    //cout<<mnum;
    r_e=recipient.e;
    r_N=recipient.N;
    c=(pow(mnum,r_e,r_N)%r_N);
    cout<<"Encrypted."<<endl;
    return c;
}

void company::DECRYPT(BigInt EncryptedMessage)
{
    cout<<endl<<"Decrypting.......     ";
    BigInt mesage;
    cout<<"Decrypted."<<endl;
    //cout<<message;
    BigInt te = EncryptedMessage%N;
    //cout<<te;
    //cout<<endl;
    //cout<<d;
    //cout<<pow(Integer(2),Integer(5));
    mesage =(pow((te),d,N))%N;
    //cout<<message;
    //cout<<endl;
    numToStr(mesage);
    return ;
}

char x='A';

void company::signup()
{

	cout<<"Establishing company "<<x<<endl;
    getPQ();
    getN();
    getphiN();
    getE();
    getD();
    cout<<x<<" established."<<endl;
    x++;
    if(x=='C')
    {
    	cout<<"Message from company A to B is : "<<endl;
	}
}

int main(){
    company A;
    company B;
    A.signup();
    B.signup();
    cout<<"Enter the message to be sent by A : ";
    getline(cin,message);
    cout<<"Message from company A to B is : "<<message<<endl;
    BigInt EncryptedMessage=A.ENCRYPT(message,B);
    cout<<"the encrypted message sent is : ";
    cout<<EncryptedMessage;
    cout<<"the Decrypted message received by B from A is : ";
    B.DECRYPT(EncryptedMessage);
	return 0;
}
