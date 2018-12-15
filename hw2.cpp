#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Server.h"

using namespace std;

int main(){

  Person Alice;
  Person Bob;
  Server Serve;

  Alice.name= "Alice";
  Bob.name = "Bob";

  //Alice and servers agreed upon numbers
  int prime_1 = 7727;
  int root_1 = 31;
  //Bob and servers agreed upon numbers
  int prime_2 = 6143;
  int root_2 = 61;

  //Alice makes her secret key and public key
  Alice.set_secret_key(33);
  Alice.make_public_key(root_1, prime_1);

  //Bob makes his secret key and public key
  Bob.set_secret_key(46);
  Bob.make_public_key(root_2, prime_2);

  //Server makes its secret key and public keys
  Serve.set_secret_key(91);
  Serve.make_public_key_a(root_1, prime_1);
  Serve.make_public_key_b(root_2, prime_2);

  //Establish shared keys between Bob/Server and Alice/Server
  Alice.find_shared_key(Serve.public_key_a, prime_1);
  Bob.find_shared_key(Serve.public_key_b, prime_2);
  Serve.find_shared_key_a(Alice.public_key, prime_1);
  Serve.find_shared_key_b(Bob.public_key, prime_2);

  Serve.generate_encryptions(&Alice, &Bob, 1111);


}
