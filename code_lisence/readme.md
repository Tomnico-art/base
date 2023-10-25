g++ -o lisence.exe general_license.cpp -lssl -lcrypto -std=c++11
g++ -o special special.cpp -lssl -lcrypto -std=c++11

g++ -o license_general license.cpp -lssl -lcrypto -std=c++11
g++ -o license_special license.cpp -lssl -lcrypto -std=c++11

g++ -o rsa rsa.cpp -lssl -lcrypto -std=c++11



# 生成公钥和私钥
openssl genrsa -out private.key 2048
openssl rsa -in private.key -outform PEM -pubout -out public.key