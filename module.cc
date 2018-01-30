extern "C" {
#include "./api.h"
}

#include <nan.h>
#include <iostream>
#include <cstdint>
using namespace v8;
using namespace std;

NAN_METHOD(GenKeypair){

  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char sk[CRYPTO_SECRETKEYBYTES];
  crypto_sign_keypair(pk, sk);

  char convertedPk[CRYPTO_PUBLICKEYBYTES*2 + 1];
  int i;

  for(i=0;i<CRYPTO_PUBLICKEYBYTES;i++) {
    sprintf(&convertedPk[i*2], "%02X", pk[i]);
  }

  char convertedSk[CRYPTO_SECRETKEYBYTES*2 + 1];

  for(i=0;i<CRYPTO_SECRETKEYBYTES;i++) {
    sprintf(&convertedSk[i*2], "%02X", sk[i]);
  }
   v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Nan::Set(obj, Nan::New("pubKey").ToLocalChecked(), Nan::New(convertedPk).ToLocalChecked());
    Nan::Set(obj, Nan::New("priKey").ToLocalChecked(), Nan::New(convertedSk).ToLocalChecked());
        int length2;
  length2 = sizeof(sk)/sizeof(sk[0]);

  cout<<length2<<endl;
    
    info.GetReturnValue().Set(obj);

}

NAN_MODULE_INIT(Init)
{
  Nan::Set(target, Nan::New("genKeypair").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(GenKeypair)).ToLocalChecked());
}

NODE_MODULE(myaddon, Init)
