#include <iostream>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <memory>

RSA *createPrivateRSA(std::string key) {
  RSA *rsa = NULL;
  const char *c_string = key.c_str();
  BIO *keybio = BIO_new_mem_buf((void *)c_string, -1);
  if (keybio == NULL) {
    return 0;
  }
  rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
  return rsa;
}

void Base64Encode( const unsigned char* buffer, 
                   size_t length, 
                   char** base64Text) { 
  BIO *bio, *b64;
  BUF_MEM *bufferPtr;
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);
  BIO_write(bio, buffer, length);
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPtr);
  BIO_set_close(bio, BIO_NOCLOSE);
  BIO_free_all(bio);
  *base64Text=(*bufferPtr).data;
}

bool RSASign(RSA *rsa, const unsigned char *Msg, size_t MsgLen,
             unsigned char **EncMsg, size_t *MsgLenEnc) {
  EVP_MD_CTX *m_RSASignCtx = EVP_MD_CTX_create();
  EVP_PKEY *priKey = EVP_PKEY_new();
  EVP_PKEY_assign_RSA(priKey, rsa);
  if (EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_sha256(), NULL, priKey) <= 0) {
    return false;
  }
  if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0) {
    return false;
  }
  if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <= 0) {
    return false;
  }
  *EncMsg = (unsigned char *)malloc(*MsgLenEnc);
  if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0) {
    return false;
  }
  EVP_MD_CTX_free(m_RSASignCtx);
  return true;
}

char *signMessage(std::string privateKey, std::string plainText) {
  RSA *privateRSA = createPrivateRSA(privateKey);
  unsigned char *encMessage;
  char *base64Text;
  size_t encMessageLength;
  RSASign(privateRSA, (unsigned char *)plainText.c_str(), plainText.length(),
          &encMessage, &encMessageLength);
  Base64Encode(encMessage, encMessageLength, &base64Text);
  free(encMessage);
  return base64Text;
}