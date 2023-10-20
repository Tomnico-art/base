OpenSSL 库是一个广泛使用的开源库，用于通过计算机网络进行安全通信。它提供了一组加密函数，可用于C++应用程序中执行加密、解密、数字签名和密钥生成等任务。



## 1 初始化OpenSSL

在使用 OpenSSL 库之前，您需要使用 OPENSSL_init_crypto（） 函数对其进行初始化。此函数初始化 OpenSSL 库并设置错误处理系统。您应该在程序开始时调用此函数一次。

```c
#include <openssl/rand.h>

int main() {
    // Initialize OpenSSL
    OPENSSL_init_crypto(0, NULL);

    // Use OpenSSL functions here

    return 0;
}
```

## 2 生成密钥对

### 密钥对

在公钥密码学中，密钥对由两个相关的密钥组成：公钥和私钥。 这两个密钥在数学上是相关联的，但是从一个密钥派生另一个密钥在计算上是不可行的。 公钥用于加密数据，而私钥用于解密数据或签名消息。

公钥密码学的安全性基于某些数学问题的难度，例如分解大质数或计算离散对数。 公钥可以自由分发给任何想要发送加密消息或验证数字签名的人，而私钥必须由所有者保密。

对于 RSA 算法，密钥对由一个 RSA 结构组成，其中包含模数 n 和两个相关指数 e 和 d。 公钥是 (n, e) 对，而私钥是 (n, d) 对。

要使用 RSA 加密数据，发件人使用收件人的公钥来执行加密。 发件人使用收件人的公钥加密数据，收件人使用他们的私钥解密数据。

要使用 RSA 签署消息，发件人使用他们的私钥来执行签名。 发件人计算消息的哈希值，然后使用他们的私钥加密哈希值。 收件人可以通过计算消息的哈希值并使用发件人的公钥解密签名来验证签名。 如果解密的哈希与计算的哈希相匹配，则签名有效。

总之，密钥对是公钥密码学中的一个基本概念，允许安全通信和数字签名。 RSA 算法是一种广泛使用的公钥加密算法，它依赖于使用 RSA 密钥对。

### RSA加密算法

在密码学中，RSA（Rivest-Shamir-Adleman）是一种广泛使用的公钥加密算法。 RSA 算法使用由公钥和私钥组成的非对称密钥对。 公钥可以自由分发，私钥保密。

在 OpenSSL 库中，RSA 密钥对由 RSA 结构表示。 该结构包含以下字段：

```
BIGNUM *n：模数，是两个大质数的乘积。
BIGNUM *e：公共指数，通常是一个小质数，例如 3 或 65537。
BIGNUM *d：私有指数，它是公共指数模 (p-1)(q-1) 的倒数，其中 p 和 q 是模数的质因数。
BIGNUM *p：模数的第一个质因数。
BIGNUM *q：模数的第二个质因数。
BIGNUM *dmp1：值 d 模 p-1。
BIGNUM *dmq1：值 d 模 q-1。
BIGNUM *iqmp：q 模 p 的倒数。
RSA 结构的 n 和 e 字段定义公钥，而 n、d、p、q、dmp1、dmq1 和 iqmp 字段一起定义私钥。
```

您可以使用 RSA_generate_key_ex() 函数生成 RSA 密钥对，传入所需的密钥长度和公共指数。 此函数将生成一个随机密钥对并将其存储在 RSA 结构中。

一旦您拥有了RSA 密钥对，您就可以使用它来执行加密、解密、数字签名和验证操作。 OpenSSL 库提供了广泛的函数来使用 RSA 执行这些操作。

### 生成密钥对

要使用 RSA 执行加密或数字签名操作，您需要先生成密钥对。您可以使用 RSA_generate_key_ex（） 函数生成指定长度的密钥对。密钥对存储在 RSA 结构中，您可以在以后的操作中使用该结构。

```c
#include <openssl/rand.h>

RSA *generateKeyPair(int keyLength) {
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, keyLength, bn, NULL);
    return rsa;
}
```

### 3 加密和解密数据

要使用 RSA 加密或解密数据，您可以分别使用 RSA_public_encrypt() 和 RSA_private_decrypt() 函数。 这些函数获取要加密或解密的数据、数据的长度、RSA 密钥结构和指示要使用的填充模式的标志。







