#include <iostream>
#include <string>
#include <vector>
#include "./api.h"
#include "./randombytes.h"
#include <stdint.h>

class Dilithium
{
  public:
    Dilithium();
    Dilithium(const std::vector<uint8_t> &pk, const std::vector<uint8_t> &sk);
    virtual ~Dilithium() = default;

    std::vector<uint8_t> sign(const std::vector<uint8_t> &message);

    std::vector<uint8_t> getSK() { return _sk; }
    std::vector<uint8_t> getPK() { return _pk; }

    unsigned int getSecretKeySize() { return CRYPTO_SECRETKEYBYTES; }
    unsigned int getPublicKeySize() { return CRYPTO_PUBLICKEYBYTES; }

    static bool sign_open(std::vector<uint8_t> &message_output,
                          const std::vector<uint8_t> &message_signed,
                          const std::vector<uint8_t> &pk);

    static std::vector<uint8_t> extract_message(std::vector<uint8_t> &message_output);
    static std::vector<uint8_t> extract_signature(std::vector<uint8_t> &message_output);
    void set_values (int,int);
    int area (void) {return (x*y);}
  protected:
    std::vector<uint8_t> _pk;
    std::vector<uint8_t> _sk;
    int x,y;
};

Dilithium::Dilithium()
{
    // TODO: Initialize keys randomly (seed?)
    printf("there have no data\n");
    _pk.resize(CRYPTO_PUBLICKEYBYTES);
    _sk.resize(CRYPTO_SECRETKEYBYTES);
    crypto_sign_keypair(_pk.data(), _sk.data());
}

Dilithium::Dilithium(const std::vector<uint8_t> &pk, const std::vector<uint8_t> &sk) : _pk(pk),
                                                                                       _sk(sk)
{
    printf("data is here\n");
    // printf("hhhhh");
    // TODO: Verify sizes - CRYPTO_SECRETKEYBYTES / CRYPTO_PUBLICKEYBYTES
}

std::vector<uint8_t> Dilithium::sign(const std::vector<uint8_t> &message)
{
    unsigned long long message_signed_size_dummy;

    std::vector<unsigned char> message_signed(message.size() + CRYPTO_BYTES);

    crypto_sign(message_signed.data(),
                &message_signed_size_dummy,
                message.data(),
                message.size(),
                _sk.data());

    return message_signed;

    // TODO: Leon, return only signature?
    //    return std::vector<unsigned char>(message_signed.begin()+message.size(),
    //                                      message_signed.end());
}

bool Dilithium::sign_open(std::vector<uint8_t> &message_output,
                          const std::vector<uint8_t> &message_signed,
                          const std::vector<uint8_t> &pk)
{
    auto message_size = message_signed.size();
    message_output.resize(message_size);

    unsigned long long message_output_dummy;
    auto ret = crypto_sign_open(message_output.data(),
                                &message_output_dummy,
                                message_signed.data(),
                                message_signed.size(),
                                pk.data());

    // TODO Leon: message_out has size()+CRYPTO_BYTES. Should we return just the message?
    // if ret == 0, success and this return value = 1
    return ret == 0;
}

std::vector<uint8_t> Dilithium::extract_message(std::vector<uint8_t> &message_output)
{
    return std::vector<uint8_t>(message_output.begin(), message_output.end() - CRYPTO_BYTES);
}

std::vector<uint8_t> Dilithium::extract_signature(std::vector<uint8_t> &message_output)
{
    return std::vector<uint8_t>(message_output.end() - CRYPTO_BYTES, message_output.end());
}
void Dilithium::set_values (int a, int b) {
        x = a;
        y = b;
    }
    
int main()
{
    // std::cout << "emm";
    // std::cout << CRYPTO_SECRETKEYBYTES;
    // unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    // unsigned char sk[CRYPTO_SECRETKEYBYTES];
    // crypto_sign_keypair(pk, sk);
    Dilithium dilithium;
    
    auto pk = dilithium.getPK();
    auto sk = dilithium.getSK();
    Dilithium d(pk,sk);
    auto pk2 = d.getPK();

    std::vector<unsigned char> message{0, 1, 2, 4, 6, 9, 1};
    auto message_signed = dilithium.sign(message);
    std::vector<unsigned char> message_out(message.size());
    auto ret = Dilithium::sign_open(message_out, message_signed, pk);
    // printf("%d\n",ret);
    // printf("%s\n", pk);
    // printf("%s\n", pk2);
    
    std::cout<<"ret:";
    std::cout<<ret<<std::endl;
    dilithium.set_values (3,4);
        std::cout << "rect area: " << dilithium.area() << std::endl;
        if (pk == pk2) {
            printf("相等equal\n");
        }else{
            printf("不等not equal2\n");
            
        }
    return 0;
}