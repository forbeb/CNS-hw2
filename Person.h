#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Person {
  private:
    int shared_key;//shared key between person and server
    int secret_key;//secret key used to make shared_key
    int final_key;//final key with other person

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

    int decrypt(int message, int key){
      int* bin_mes = create_binary(message);
      int* bin_key = create_binary(key);
      int x[12];
      for(int i=0; i<12; i++){
        x[i] = bin_mes[i] ^ bin_key[i];
      }
      return create_int(x);
    }

  public:
    string name;
    int public_key;

    void set_secret_key(int k){secret_key = k;}
    void make_public_key(int root, int prime){public_key = (int)pow(root,secret_key)%prime;}
    void find_shared_key(int public_key, int prime){shared_key = abs((int)pow(public_key, secret_key)%prime);}

    void receive_encryption(int key_1, Person *p1, Person *p2, int n, int key_2){
      final_key = decrypt(key_1, shared_key);
      cout<<final_key<<endl;
      p2->receive_key(p1, p2, decrypt(key_2, shared_key));
    }
    void receive_key(Person *p1, Person *p2, int key_ab){
      final_key = decrypt(key_ab, shared_key);
      p1->receive_nonce(encrypt(322, final_key), p2);
    }
    void receive_nonce(int n, Person *p2){
      cout<<final_key<<endl;
      p2->receive_new_nonce(encrypt(decrypt(n,final_key)-1, final_key));
    }
    void receive_new_nonce(int n){
      cout<<decrypt(n, final_key)<<endl;
    }
};
