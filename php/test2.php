<?php

class A
{

}

$obj['abc']='dasdasdsa';
$obj['bcd']=10000;
$obj['a']=new A();
$obj['name']="sssssss";
$obj['urls']=array('http://www.baidu.com','http://www.qq.com');
$obj['info']['age']=19;
$obj['info']['name']='helloworld';
$obj['info']['price']=1.5555;

var_dump($str = av_encode($obj));
var_dump(av_decode($str));
