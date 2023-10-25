#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/buffer.h>
#include <map>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <unistd.h>

enum LicenseType
{
  General,
  Special
};

// License
struct LicenseInfo
{
  std::string product;
  std::string version;
  std::string cpu;
  std::string mac;
  std::string startdate;
  std::string enddate;
  std::string company;
  int type;
};

/**
 * 解密，通过公钥解密解析json字符串
 */

// 公钥解密
std::string rsa_pub_decrypt(const std::string &cipherText, const std::string &pubKey)
{
  std::string strRet;
  RSA *rsa = RSA_new();
  BIO *keybio = BIO_new_mem_buf((unsigned char *)pubKey.c_str(), -1);
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

  int len = RSA_size(rsa);
  char *decryptedText = new char[len + 1]{};

  // 解密函数
  int ret = RSA_public_decrypt(cipherText.length(), (const unsigned char *)cipherText.c_str(), (unsigned char *)decryptedText, rsa, RSA_PKCS1_PADDING);
  if (ret >= 0)
    strRet = std::string(decryptedText, ret);

  // 释放内存
  delete[] decryptedText;
  BIO_free_all(keybio);
  RSA_free(rsa);

  return strRet;
}

// 将十六进制字符串转换为二进制数据
std::vector<char> hexToBytes(const std::string &hex)
{
  std::vector<char> bytes;
  for (size_t i = 0; i < hex.length(); i += 2)
  {
    std::string byteString = hex.substr(i, 2);
    unsigned char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
    bytes.push_back(byte);
  }
  return bytes;
}

// 删除字符串中的空格
std::string removeSpaces(const std::string &str)
{
  std::string result;
  for (char ch : str)
  {
    if (ch != ' ')
    {
      result += ch;
    }
  }
  return result;
}

// 将二进制数据转换为 Base64 字符串
std::string base64Encode(const std::vector<char> &data)
{
  std::string base64String;

  // 创建 BIO 对象
  BIO *memBio = BIO_new(BIO_s_mem());
  BIO *base64Bio = BIO_new(BIO_f_base64());
  BIO *bio = BIO_push(base64Bio, memBio);

  // 禁用换行符
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

  // 写入数据到 BIO
  BIO_write(bio, data.data(), static_cast<int>(data.size()));
  BIO_flush(bio);

  // 获取编码后的数据
  BUF_MEM *bufferPtr = nullptr;
  BIO_get_mem_ptr(bio, &bufferPtr);
  if (bufferPtr != nullptr && bufferPtr->data != nullptr && bufferPtr->length > 0)
  {
    base64String.assign(bufferPtr->data, bufferPtr->data + bufferPtr->length);
  }

  // 释放资源
  BIO_free_all(bio);

  return base64String;
}

// Base64 解码
std::string base64Decode(const std::string &encodedData)
{
  // 创建 Base64 解码的 BIO 对象
  BIO *bio = BIO_new(BIO_f_base64());
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

  // 将 BIO 对象连接到输入流中
  BIO *bmem = BIO_new_mem_buf(encodedData.data(), static_cast<int>(encodedData.length()));
  bio = BIO_push(bio, bmem);

  // 分配解码后的缓冲区
  const int bufferSize = encodedData.length();
  std::vector<char> buffer(bufferSize);

  // 执行解码操作
  int decodedLength = BIO_read(bio, buffer.data(), bufferSize);

  // 将解码后的数据转换为字符串
  std::string decodedData(buffer.data(), decodedLength);

  // 释放资源
  BIO_free_all(bio);

  return decodedData;
}

// 加载二进制解密文件
std::string loadBinaryFile(const std::string &filename)
{
  std::ifstream inputFile(filename, std::ios::binary); // 创建二进制文件输入流
  std::vector<char> fileData;

  if (inputFile)
  {
    // 获取文件大小
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // 创建足够大的向量来容纳文件数据
    fileData.resize(fileSize);

    // 从文件中读取数据到向量
    inputFile.read(fileData.data(), fileSize);

    if (!inputFile)
    {
      std::cout << "Error reading file: " << filename << std::endl;
      fileData.clear(); // 清空向量
    }
  }
  else
  {
    std::cout << "Failed to open file: " << filename << std::endl;
  }

  std::string base64String = base64Encode(fileData);

  return base64String;
}

// 加载十六进制解密文件
std::string loadHexFile(const std::string &filename)
{
  std::ifstream inputFile(filename); // 创建文件输入流
  std::string base64String;

  if (inputFile.is_open())
  {
    std::string hexString;
    std::getline(inputFile, hexString); // 从文件中读取一行字符串

    // 删除空格
    std::string hexStringNoSpaces = removeSpaces(hexString);

    // 将十六进制字符串转换为二进制数据
    std::vector<char> binaryData = hexToBytes(hexStringNoSpaces);

    // 将二进制数据转换为 Base64 字符串
    base64String = base64Encode(binaryData);

    // 输出 Base64 字符串
    // std::cout << "Base64 String: " << base64String << std::endl;
  }
  else
  {
    std::cout << "Failed to open the file." << std::endl;
  }
  return base64String;
}

// 加载公钥文件
std::string loadPublicKeyAsString(const std::string &publicKeyFile)
{
  std::ifstream file(publicKeyFile);
  if (!file.is_open())
  {
    std::cerr << "Failed to open the public key file." << std::endl;
    return "";
  }

  std::ostringstream oss;
  oss << file.rdbuf();
  std::string publicKeyStr = oss.str();

  file.close();

  return publicKeyStr;
}

/**
 * 验证，校验license
 */

// 正则匹配
std::map<std::string, std::string> parseJson(const std::string &json)
{
  std::map<std::string, std::string> result;

  // 使用正则表达式匹配键值对
  std::regex pattern("\"(.*?)\":\"(.*?)\"");
  std::smatch matches;
  std::string::const_iterator searchStart(json.cbegin());

  while (std::regex_search(searchStart, json.cend(), matches, pattern))
  {
    if (matches.size() == 3)
    {
      std::string key = matches[1].str();
      std::string value = matches[2].str();

      // 存储解析结果
      result[key] = value;
    }

    searchStart = matches.suffix().first;
  }

  return result;
}

// 获取本机的 CPU ID
std::string getCpuId()
{
  std::string result;

  FILE *pipe = popen("dmidecode -t processor | grep 'ID'", "r");
  if (!pipe)
  {
    throw std::runtime_error("Failed to execute command");
  }

  char buffer[1024];
  fgets(buffer, sizeof(buffer), pipe);
  pclose(pipe);

  result = buffer;
  result.erase(remove(result.begin(), result.end(), '\t'), result.end());
  result.erase(remove(result.begin(), result.end(), ' '), result.end());
  result.erase(remove(result.begin(), result.end(), '\n'), result.end());

  if (result.empty())
  {
    throw std::runtime_error("Failed to get CPU ID");
  }

  return result;
}

// 获取本机的 MAC 地址
std::string getMacAddress()
{
  std::string result;

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock < 0)
  {
    throw std::runtime_error("Failed to create socket");
  }

  struct ifreq ifr;
  struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;

  strcpy(ifr.ifr_name, "ens33");
  if (ioctl(sock, SIOCGIFADDR, &ifr) != 0)
  {
    throw std::runtime_error("Failed to get IP address");
  }

  if (ioctl(sock, SIOCGIFHWADDR, &ifr) != 0)
  {
    throw std::runtime_error("Failed to get MAC address");
  }

  close(sock);

  char mac[18];
  sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", (unsigned char)ifr.ifr_hwaddr.sa_data[0],
          (unsigned char)ifr.ifr_hwaddr.sa_data[1], (unsigned char)ifr.ifr_hwaddr.sa_data[2],
          (unsigned char)ifr.ifr_hwaddr.sa_data[3], (unsigned char)ifr.ifr_hwaddr.sa_data[4],
          (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

  result = mac;

  if (result.empty())
  {
    throw std::runtime_error("Failed to get MAC address");
  }

  return result;
}

time_t StringToDatetime(std::string str)
{
  char *cha = (char *)str.data();               // 将string转换成char*。
  tm tm_;                                       // 定义tm结构体。
  int year, month, day, hour, minute, second;   // 定义时间的各个int临时变量。
  sscanf(cha, "%d-%d-%d", &year, &month, &day); // 将string存储的日期时间，转换为int临时变量。
  tm_.tm_year = year - 1900;                    // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
  tm_.tm_mon = month - 1;                       // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
  tm_.tm_mday = day;                            // 日。
  tm_.tm_isdst = 0;                             // 非夏令时。
  time_t t_ = mktime(&tm_);                     // 将tm结构体转换成time_t格式。
  return t_;                                    // 返回值。
}

time_t NowTime()
{
  time_t t_Now = time(0);
  struct tm *tm_Now = localtime(&t_Now);
  tm_Now->tm_hour = 0;
  tm_Now->tm_min = 0;
  tm_Now->tm_sec = 0;
  return mktime(tm_Now);
}

int main(int narg, char **args)
{
  // 加载公钥文件为字符串
  std::string publicKeyFile = "rsa_public_key.pem";
  std::string publicKeyStr = loadPublicKeyAsString(publicKeyFile);

  // 加载解密文件
  std::string filename = "20230613105540816.lic"; // 文件名
  // //从二进制文件读取
  std::string encStr = loadBinaryFile(filename);

  // 从十六进制文件读取
  //  std::string encStr = loadHexFile(filename);

  // 解密
  std::string encStr2 = base64Decode(encStr.c_str());
  std::string decStr = rsa_pub_decrypt(encStr2, publicKeyStr);
  std::cout << decStr.c_str() << std::endl;

  // 解析JSON字符串
  std::map<std::string, std::string> jsonData = parseJson(decStr.c_str());

  std::string expectedProduct = jsonData["product"];
  std::string expectedVersion = jsonData["version"];
  std::string expectedStartDate = jsonData["startdate"];
  std::string expectedEndDate = jsonData["enddate"];
  std::string expectedCompany = jsonData["company"];
  std::string expectedCpu = jsonData["cpu"];
  std::string expectedMac = jsonData["mac"];
  std::string expectedType = jsonData["type"];

  int type = atoi(expectedType.c_str());
  type = General;

  std::cout << expectedStartDate << "," << expectedEndDate << std::endl;

  // 校验数据
  LicenseInfo license;
  license.product = "高性能图数据库gStore";
  license.version = "0.9";
  license.startdate = "2023-05-28";
  license.enddate = "2023-12-31";
  license.company = "北京大学重庆大数据研究院";
  license.cpu = getCpuId();
  license.mac = getMacAddress();

  std::cout << license.product << "," << license.version << "," << license.startdate << "," << license.enddate << "," << license.company << "," << license.cpu << "," << license.mac << std::endl;

  int resStart = license.startdate.compare(expectedStartDate);
  int resEnd = license.enddate.compare(expectedEndDate);
  std::cout << resStart << "," << resEnd << std::endl;

  switch (type)
  {
  case General:
    if (license.product == expectedProduct && license.version == expectedVersion && license.company == expectedCompany && resStart == 0 && resEnd == 0)
    {
      std::cout << "License vertified successfully!" << std::endl;
    }
    else
    {
      std::cout << "License vertified failed!" << std::endl;
    }
    break;
  case Special:
    if (license.product == expectedProduct && license.version == expectedVersion && license.company == expectedCompany && resStart == 0 && resEnd == 0 && license.cpu == expectedCpu && license.mac == expectedMac)
    {
      std::cout << "License vertified successfully!" << std::endl;
    }
    else
    {
      std::cout << "License vertified failed!" << std::endl;
    }
    break;
  default:
    std::cout << "License information error!" << std::endl;
    break;
  }

  return 0;
}