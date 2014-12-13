anyvalue
========

高性能数据序列化库，支持C++ java python php objectc 语言，兼容json数据格试，可以互相转换

php
========

$obj['abc']='dasdasdsa';
$obj['bcd']=10000;
$obj['name']="sssssss";
$obj['urls']=array('http://www.baidu.com','http://www.qq.com');
$obj['info']['age']=19;
$obj['info']['name']='helloworld';
$obj['info']['price']=1.5555;

$str = av_encode($obj);
var_dump(av_decode($str));

python
========
import anyvalue

obj=[1,2,3,4,-111,-1,-11111,1.5555,-1.11111,"dsadsdsdsads","dsdsadsadsds",{"a":1}]
str = anyvalue.encode(obj)
obj = anyvalue.decode(str)

c++
=========
CAnyValue oValue;
oValue["abc"]=1;
oValue["bcd"]="中国人helloaaa{}]\"'/\\*&^%$#@!><;:''''...,,中国人民大ddd";
oValue["aa"].push_back("aaa{}]\"'/\\*&^%$#@!><;:''''...,,");
oValue["aa"].push_back(-1001);
oValue["aa"].push_back(-123);
oValue["aa"].push_back(-123);
oValue["aa"].push_back(ddwInt);
oValue["aa"].push_back(CAnyValue());
oValue["xbv"]["xx"]=1.51111111;
oValue["xbv"]["xx2"] = -123455553234442444444444444444.111113334;
oValue["xbv"]["ms"]="xxxx";
oValue["xbv"]["xxxx"] =true;
oValue["xbv"]["x"];
string sBuf;
oValue.encode(sBuf);
CAnyValue oValue2;
oValue2.decode(sBuf.data(),sBuf.size());
uint32_t dwValue = oValue2["abc"].asUInt();

