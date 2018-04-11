#ifndef HELPBYTEARRAY_H
#define HELPBYTEARRAY_H

#include <QObject>


//全局静态方法类
class HelpByteArray : public QObject
{
    Q_OBJECT
public:


    //16进制字符串转10进制
    static int strHexToDecimal(const QString &strHex);

    //10进制字符串转10进制
    static int strDecimalToDecimal(const QString &strDecimal);

    //2进制字符串转10进制
    static int strBinToDecimal(const QString &strBin);

    //16进制字符串转2进制字符串
    static QString strHexToStrBin(const QString &strHex);

    //10进制转2进制字符串一个字节
    static QString decimalToStrBin1(int decimal);

    //10进制转2进制字符串两个字节
    static QString decimalToStrBin2(int decimal);

    //10进制转16进制字符串,补零.
    static QString decimalToStrHex(int decimal);


    //int转字节数组
    static QByteArray intToByte(int i);
    static QByteArray intToByteRec(int i);

    //字节数组转int
    static int byteToInt(const QByteArray &data);
    static int byteToIntRec(const QByteArray &data);

    //ushort转字节数组
    static QByteArray ushortToByte(ushort i);
    static QByteArray ushortToByteRec(ushort i);

    //字节数组转ushort
    static int byteToUShort(const QByteArray &data);
    static int byteToUShortRec(const QByteArray &data);

    //异或加密算法
    static QString getXorEncryptDecrypt(const QString &str, char key);

    //异或校验
    static uchar getOrCode(const QByteArray &data);

    //计算校验码
    static uchar getCheckCode(const QByteArray &data);

    //字符串补全
    static QString getValue(quint8 value);

    //CRC校验
    static quint16 getRevCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    static quint16 getCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
    static quint16 getModbus16(quint8 *data, int len);
    static QByteArray getCRCCode(const QByteArray &data);


    //字节数组转Ascii字符串
    static QString byteArrayToAsciiStr(const QByteArray &data);

    //16进制字符串转字节数组
    static QByteArray hexStrToByteArray(const QString &str);
    static char convertHexChar(char ch);

    //Ascii字符串转字节数组
    static QByteArray asciiStrToByteArray(const QString &str);

    //字节数组转16进制字符串
    static QString byteArrayToHexStr(const QByteArray &data);

    //判断IP地址及端口是否在线
    static bool ipLive(const QString &ip, int port, int timeout = 1000);

    //获取网页所有源代码
    static QString getHtml(const QString &url);

    //获取本机公网IP地址
    static QString getNetIP(const QString &webCode);

    //获取本机IP
    static QString getLocalIP();

};

#endif // HELPBYTEARRAY_H
