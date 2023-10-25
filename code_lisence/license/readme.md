g++ -o license.out license.cpp -lssl -lcrypto -std=c++11

g++ -o hex_parse.out hex_parse.cpp -lssl -lcrypto -std=c++11

g++ -o json_parse.out json_parse.cpp -std=c++11 -lstdc++

g++ -o license_hex.out license_hex.cpp -lssl -lcrypto -std=c++11 




# 生成公钥和私钥
openssl genrsa -out private.key 2048
openssl rsa -in private.key -outform PEM -pubout -out public.key
