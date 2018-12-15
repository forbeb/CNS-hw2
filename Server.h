#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Person.h"

using namespace std;

class Server {
  private:
    int secret_key; //secret key used to make shared_keys
    int shared_key_a;//shared key between person and server
    int shared_key_b;//shared key between person and server
    int key_ab;//final key for people

    int* create_binary(int n){
      int* x = new int[12];
      int i=11;
      while(i>=0){
        x[i]=n%2;
        n/=2;
        i--;
      }
      return x;
    }

    int create_int(int* n){
      int x = 0;
      int i = 0;
      while(i<12){
        x = x + n[11-i]*pow(2,i);
        i++;
      }
      return x;
    }

    int encrypt(int message, int key){
      int* bin_mes = create_binary(message);
      int* bin_key = create_binary(key);
      int x[12];
      for(int i=0; i<12; i++){
        x[i] = bin_mes[i] ^ bin_key[i];
      }
      return create_int(x);
    }


  public:
    int public_key_a;
    int public_key_b;

    void set_secret_key(int k){secret_key = k;}
    void make_public_key_a(int root, int prime){public_key_a = (int)pow(root,secret_key)%prime;}
    void make_public_key_b(int root, int prime){public_key_b = (int)pow(root,secret_key)%prime;}
    void find_shared_key_a(int public_key, int prime){shared_key_a = abs((int)pow(public_key, secret_key)%prime);}
    void find_shared_key_b(int public_key, int prime){shared_key_b = abs((int)pow(public_key, secret_key)%prime);}

    void generate_encryptions(Person *p1, Person *p2, int n){
      key_ab=1234;
      p1->receive_encryption(encrypt(key_ab, shared_key_a), p1, p2, encrypt(n, shared_key_a), encrypt(encrypt(key_ab, shared_key_b), shared_key_a));
    }

    void print(){cout<<shared_key_a<<endl; cout<<shared_key_b<<endl;}
};
