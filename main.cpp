#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

class frac{
    public:
        int numerator, denominator;
        frac * numerator_ = 0;
        vi digits;
        int NofDigits = 0;
        int integer;
        bool is_num_frac;
        ll carry = 0;
        bool is_0 = true;
        frac(int num, int den){
            this->numerator = num;
            this->denominator = den;
            this->integer = num / den;
            this->carry = num % den;
            this->is_num_frac = false;
            this->is_0 = !this->integer;
        }

        frac(frac * num, int den){
            // cout << num << "---" << endl;
            this->numerator_ = num;
            this->denominator = den;
            this->integer = (*num).integer / den;
            this->carry = (*num).integer % den;
            this->is_num_frac = true;
            this->is_0 = !this->integer;
        }

        vi getDigits(int n, bool b = false){
            // cout << this << " " << this->numerator_ << " " << this->integer << endl;
            if(is_num_frac && (*(this->numerator_)).NofDigits < n){
                (*(this->numerator_)).getDigits(n);
                // int e = 1/0;
            }
            for(int i = this->digits.size(); this->digits.size() <= n; i++){
                ll a = this->carry * 10;
                if(is_num_frac){
                    a += (*this->numerator_).digits[i];
                }
                this->digits.push_back(a / this->denominator);
                if(this->digits[i] != 0 && is_0){
                    is_0 = false;
                }
                this->carry = a % this->denominator;
                // if(b) cout << a << " " << i << endl;
            }
            this->NofDigits = this->digits.size();
            return this->digits;
        }

        string print(){
            string res = to_string(this->integer) + ".";
            for(int i = 0; i < this->NofDigits; i++){
                res += to_string(this->digits[i]);
            }
            return res;
        }

        frac operator+=(frac a){
            this->integer += a.integer;
            int n = min(this->NofDigits, a.NofDigits);
            int c = 0;
            // cout << n << endl;
            for(int i = n - 1; i >= 0; i--){
                // cout << i << endl;
                int temp = this->digits[i] + a.digits[i] + c;
                this->digits[i] = temp % 10;
                c = temp / 10;
            }
            this->integer += c;
            return *this;
        }
        frac operator-=(frac a){
            this->integer -= a.integer;
            int n = min(this->NofDigits, a.NofDigits);
            int c = 0;
            for(int i = n - 1; i >= 0; i--){
                int temp = a.digits[i] + c;
                if(temp > this->digits[i]){
                    temp = this->digits[i] - temp + 10;
                    c = 1;
                }else{
                    temp = this->digits[i] - temp;
                    c = 0;
                }
                this->digits[i] = temp;
                // c = 0;
            }
            this->integer -= c;
            return *this;
        }
};

int main(){
    // frac a(1, 7);
    // a.getDigits(n);
    int n = 1000;
    cout << "How many digits of pi do you need: " << flush;
    cin >> n;
    int n2 = n;
    n += ceil(log10(10 * n * log2(10)));
    frac pi_(0, 1);
    pi_.getDigits(n);
    int f1 = 2, f2 = 3;
    for(int i = 0; i < 10; i++){
        // cout << pi_.print() << " " << f1 << endl;
        vector<frac> arctan_ = {frac(4, f1)};
        arctan_[0].getDigits(n);
        pi_ += arctan_[0];
        int sq = f1 * f1;
        for(int j = 0; !arctan_[j].is_0; j++){
            arctan_.push_back(frac(&(arctan_[j]), sq));
            arctan_[j + 1].numerator_ = &(arctan_[j]);
            // cout << &(arctan_[1]) << '-' << endl;
            // cout << &(arctan_[0]) << '-' << endl;
            // cout << arctan_[1].numerator_ << '-' << j<< endl;
            // cout << arctan_.size() << endl;
            if(j == 30){
                arctan_[j + 1].getDigits(n, true);
            }else{
                arctan_[j + 1].getDigits(n);
            }
            // cout << "-3" << endl;
            frac temp = frac(&(arctan_[j + 1]), 2 * j + 3);
            temp.getDigits(n);   
            if(j == 1){
                // cout << pi_.print() << endl;
                // temp.getDigits(n, true);
                // cout << f1 << " "<< arctan_[j].print() << "-" << endl;
                // cout << f1 * f1 << " "<< arctan_[j + 1].print() << "-" << endl;
                // cout << f1 << " "<< temp.print() << "-" << endl;
            }else{
                // temp.getDigits(n);
            }
            if(j % 2){
                // cout << "-2" << endl;
                pi_ += temp;
                // cout << "-2" << endl;
            }else{
                // cout << "-" << endl;
                pi_ -= temp;
                // cout << "-" << endl;
            }
        }
        f1 = f1 + f2;
        f2 = f1 + f2;
    }
    f1 = f2 - f1;
    // cout << pi_.print() << " " << f1 << endl;
    vector<frac> arctan_ = {frac(4, f1)};
    arctan_[0].getDigits(n);
    pi_ += arctan_[0];
    int sq = f1 * f1;
    for(int j = 0; !arctan_[j].is_0; j++){
        arctan_.push_back(frac(&(arctan_[j]), sq));
        arctan_[j + 1].numerator_ = &(arctan_[j]);
        arctan_[j + 1].getDigits(n);
        frac temp = frac(&(arctan_[j + 1]), 2 * j + 3);
        temp.getDigits(n);   
        if(j % 2){
            pi_ += temp;
        }else{
            pi_ -= temp;
        }
    }
    cout << pi_.print().substr(0, n2 + 2) << endl;
}